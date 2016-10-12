/*
 * nvic.c
 *
 *  Created on: Oct 10, 2016
 *      Author: vikhyat
 */



#include "main.h"

/*--------------------------------------------------------------------------------
 * void UART0_IRQHandler (void)
 * The UART0 ISR handler receives the character fro the serial terminal and increments
 * the variable 'next' and 'b_color' accordingly when any of the characters
 * 'a' , 'w', 's' or 'd' are pressed and ignores any other character inputs.
 *
 * b_ color - 	Brightness control for the leds
 * 				ranges from 0 to 1 with resolution of 0.1
 *
 --------------------------------------------------------------------------------*/
uint8_t LED_control_word;
uint8_t LED_Control_Flag;



uint8_t rec_char,rec_length=0,i=0;

void UART0_IRQHandler (void)
{
  if (UART0_S1&UART_S1_RDRF_MASK)
  	{
		UART0_C2 &= ~UART0_C2_RIE_MASK; 		//Peripheral interrupt enable (RX)
		rec_char = UART0_D;
		// First string is a command
      if(LEDControlRequested){
       // copy data into a global variable
		LED_control_word = rec_char;
	   // set flag to enable LED code processing
		LED_Control_Flag = 1;
      }
      else if(ECOReqested){
											//add receiving character to the rx circular buffer
		Circular_Push(&RXBUFF,rec_char);
		rec_length++;						//length of input string
		if(rec_length==10 + 1)			//set TransferState after receiving complete string
		{
			TransferState=1;
			LOG_4("\r\n");
			rec_length=0;
		}
		else
			TransferState=0;
      }
      else{ //command capture
    	  Circular_Push(&RXBUFF,rec_char);
      }
  	}
/*--------------------------------------------------------------------------------------------
 * TX interrupt service for UART0
 --------------------------------------------------------------------------------------------*/

  if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
    {
	if(ECOReqested){
	  if(TransferState == 0)
		  UART0_D = rec_char;
	  if(TransferState==2)							//transmit when data is copied from rxbuff to txbuff
	  {
		  i=0;
		  while(i<10)
		  {
			  Circular_Pop(&TXBUFF,&rec_char);			//output from tx buff
			  while(!((UART0_S1&UART_S1_TDRE_MASK)|(UART0_S1&UART_S1_TC_MASK)));
			  UART0_D = rec_char;
			  i++;
		  }

		  if(Is_buffer_full(&TXBUFF))
		  {
			  UART0_C2 &= ~UART0_C2_TIE_MASK; 	//Disable Interrupt Enable for TDRE if buffer is empty
			  TransferState=3;
		  }
	  }
	}
	  UART0_C2 |=  UART0_C2_RIE_MASK;		//Peripheral interrupt enable (RX)
	  UART0_C2 &= ~UART0_C2_TIE_MASK; 		//Peripheral interrupt enable (TX)
    }
}

void TPM1_IRQHandler(void)
{
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
		//overflow_count++;					//keep count of oveflow
		TPM1_SC |= TPM_SC_TOF_MASK;			//clear the tof bit by writing 1
	}
}


