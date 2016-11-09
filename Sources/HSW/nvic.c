/*
 * nvic.c
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#include "main.h"
uint8_t packet_byte,rx_byte=0,dma_complete=0;
extern uint32_t overflow_count;

#ifndef BBB

void UART0_IRQHandler (void)
{
/* When rx_byte =1:
 * Incoming packet is stored into the circular buffer
 * length from the second byte is checked to ensure packet completion
 * Packet complete flag is checked to enable processing of packet
 */
  if (UART0_S1&UART_S1_RDRF_MASK)
  	{
	  	packet_byte = UART0_D;
	  	UART0_D = packet_byte;
		UART0_C2 &= ~UART0_C2_RIE_MASK; 		//Peripheral interrupt disable (RX)
		rx_byte = 1;
  	}

  if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
    {

    }
}

void DMA0_IRQHandler(void)
{
	LOG_0("\r\nDMA complete !!!\r\n");
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	//end_time();
	dma_complete = 1;
}

void TPM1_IRQHandler(void)
{
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
		overflow_count++;					//keep count of oveflow
		TPM1_SC |= TPM_SC_TOF_MASK;			//clear the tof bit by writing 1
	}
}

#endif
