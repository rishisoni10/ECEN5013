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

extern uint8_t dma_complete;

void Read_Status(void){
	    LOG_0("\r\nReading Status Register");
		uint8_t statusVal = nrf_status_read();
		LOG_1("\r\nThe status register value =",statusVal);
}

void Read_write_register(void){
	LOG_0("\r\nWriting value=5 in register:CONFIG\r\n");
	nrf_write_register(NRF_REG_00_CONFIG, 0x03);
	LOG_0("\rWrite to register successful");
	uint8_t regVal = nrf_read_register(NRF_REG_00_CONFIG);
	LOG_1("\r\nValue read from register:CONFIG = ",regVal);
}

void check_fifo(void){
	unsigned char a[32];
	uint8_t len = 32;
	while(len--){
		a[len]=0xAA;
	}
	nrf_flush_tx_fifo();
	LOG_0("\r\nTesting Tx_FIFO");
	uint8_t regVal = nrf_read_register(NRF_REG_17_FIFO_STATUS);
	LOG_1("\r\nValue at FIFO_STATUS =  ",regVal);
	LOG_0("\r\nWriting 96 bytes into tx FIFO");
	nrf_write_Tx_Payload(a, 32);
	regVal = nrf_read_register(NRF_REG_17_FIFO_STATUS);
	nrf_write_Tx_Payload(a, 32);
	nrf_write_Tx_Payload(a, 32);
	LOG_0("\r\nTx_FIFO has 96 bytes");
	regVal = nrf_read_register(NRF_REG_17_FIFO_STATUS);
	LOG_1("\r\nnew value at FIFO_STATUS  ",regVal);
	LOG_0("\r\nFlushing TX_FIFO");
	LOG_0("\r\nTx_FIFO has 0 bytes");
	nrf_flush_tx_fifo();
	regVal = nrf_read_register(NRF_REG_17_FIFO_STATUS);
	LOG_1("\r\nnew value at FIFO_STatus =  ",regVal);
}


int main(void)
{
	uart_init(BAUD_RATE);
	init_profiler();
	dma_init();
	led_init();

#ifdef MSG
	init_cbuff(&RXBUFF,25);
	Handle_msg();
	}
#endif

#ifdef CHECK_WRITE_READ
	Read_write_register();
#endif

#ifdef CHECK_STATUS
   Read_Status();
#endif

#ifdef CHECK_FIFO
   check_fifo();
#endif

#ifdef DMA_test
	 uint8_t src[100];
	 uint8_t des[100];

	for(int i=0;i<100;i++)
		des[i] = 0;
	for(int i=0;i<100;i++)
		src[i] = 55;
	 __enable_irq();
	LOG_0("\r\nInitiating DMA transfer of 100 bytes");
	start_time();
	enable_dma(src,des,100);
	while(!dma_complete);
	//my_memmove(s,d,500);
	//my_memzero(s,500);
	calculate_time();

	while(1);
#endif

    return 0;
}
