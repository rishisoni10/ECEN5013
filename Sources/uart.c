/*
 * uart.c
 *
 *  Created on: Oct 10, 2016
 *      Author: vikhyat
 */



#include<stdio.h>
#include<stdint.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "Project2_settings.h"


void UART_print_string_noBuffer(const char *str)
{
   while( *str != '\0' )
   {
      TXREG = *str++;
      while( TXIF == 0 || TRMT == 0 )
      {
      }
   }
}

void UART_print_charlen_no_buffer(uint8_t *data, uint32_t len )
{
   while( len )
   {
      TXREG = *data++;
      while( TXIF == 0 || TRMT == 0 )
      {
      }
      len--;
   }
}

void initialize_UART(uint32_t baud)
{
	uint32_t divisor;

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		//Clock gate enable for PORTA
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;		//Clock gate enable for UART0
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);  	//MCGFLLCLK as UART0


	PORTA_PCR1 |= PORT_PCR_MUX(2); 			//ALT2 mode for UART0_Rx
	PORTA_PCR2 |= PORT_PCR_MUX(2);			//ALT2 mode for UART0_Tx


	UART0_C2&= ~(UART0_C2_TE_MASK|UART0_C2_RE_MASK);


	UART0_BDH |= UART_BDH_SBNS(0);			// 1 STOP bit
	UART0_C1  |= UART_C1_M(0);				// 8 BIT mode
	UART0_C1  |= UART_C1_PE(0);				// NO PARITY

	divisor = (SystemCoreClock/16)/baud ;
	UART0_BDH = ((divisor >> 8) & UART_BDH_SBR_MASK);
	UART0_BDL = (divisor & UART_BDL_SBR_MASK);

	 __enable_irq();						//Global interrupt enable
	 NVIC_EnableIRQ(UART0_IRQn); 			//Enable at NVIC
	 UART0_C2 |= UART0_C2_RIE_MASK;			//Peripheral interrupt enable (RX)

	 UART0_C2 |= UART0_C2_TE_MASK ;
	 UART0_C2 |= UART0_C2_RE_MASK ;

}

