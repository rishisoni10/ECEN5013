/*
 * uart.h
 *
 *  Created on: Oct 10, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_

#include <stdint.h>

#define OERR (UART0->S1 & UARTLP_S1_OR_MASK)   // Overrun Error bit
#define CREN (UART0->C2 & UARTLP_C2_RE_MASK)   // continuous receive enable bit
#define RCREG UART0->D                        // Receive Data Register
#define FERR (UART0->S1 & UARTLP_S1_FE_MASK)   // Framing Error bit
#define RCIF (UART0->S1 & UARTLP_S1_RDRF_MASK) // Receive Interrupt Flag (full)
#define TXIF (UART0->S1 & UARTLP_S1_TDRE_MASK) // Transmit Interrupt Flag (empty)
#define TXREG UART0->D                        // Transmit Data Register
#define TRMT (UART0->S1 & UARTLP_S1_TC_MASK)   // Transmit Shift Register Empty

void uart_init(uint32_t baud);
void UART0_IRQHandler (void);
void UART_print_string_noBuffer(const char* );
void UART_print_charlen_no_buffer(uint8_t*, uint32_t  );


#define BAUD_RATE       38400

#endif /* INCLUDES_UART_H_ */
