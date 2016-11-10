/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"

extern uint8_t packet_byte,rx_byte,dma_complete;

int main(void)
{
	uint8_t str[2],byte_length=0,byte_process=0;
	uint8_t current_length=0,packet_length=0,packet_complete=0;

	uart_init(BAUD_RATE);
	init_profiler();

#ifdef DMA_test
	 uint8_t s[500];
	 uint8_t d[500];

	for(int i=0;i<500;i++)
		d[i] = 0;
	for(int i=0;i<500;i++)
		s[i] = 55;

	 __enable_irq();						//Global interrupt enable
	 	 	 	 	 	 	 	 	 	    //system - init peripheral
	dma_init();

	start_time();
	enable_dma(s,d,500);
		while(!dma_complete);
	//my_memmove(s,d,500);
	//my_memzero(s,500);
	calculate_time();

	while(1);
#endif

#ifdef MSG
	led_init();
	init_cbuff(&RXBUFF,25);
	while(1)
	{
		if(rx_byte == 1)
		{
			//atoi
					str[byte_length] = packet_byte;				//byte processing for terminal input
					byte_length++;
					if(byte_length == 2)
					{
						packet_byte = myAtoi(str);
						byte_process = 1;
						byte_length = 0;
						LOG_0("-");
					}

					if(byte_process == 1)
					{
						byte_process = 0;
						add_cbuff(&RXBUFF,packet_byte);

						current_length ++;
						if(current_length == 2)					//length byte from the second byte
						{
							packet_length = packet_byte;
							if(packet_length == 0)
							{
								current_length = 0;
								byte_length = 0;
								LOG_0("\r\npacket_error\r");
							}
						}

						if(current_length == packet_length)
						{
							packet_complete = 1;
							current_length = 0;
						}
					}
					UART0_C2 |= UART0_C2_RIE_MASK; 			//Peripheral interrupt enable (RX)
					rx_byte = 0;
		}

		if(packet_complete == 1) {
			decode_packet();
			packet_complete = 0;
		}
	}
#endif

    return 0;
}

