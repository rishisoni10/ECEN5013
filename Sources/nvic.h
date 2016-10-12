/*
 * nvic.h
 *
 *  Created on: Oct 10, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_NVIC_H_
#define INCLUDES_NVIC_H_

#include<stdint.h>

#define INT_BITS    2

#define EnableInterrupts __asm(" CPSIE i");
#define DisableInterrupts __asm(" CPSID i");

extern uint8_t LED_control_word;
extern uint8_t LED_Control_Flag;


void enable_irq (int);
void disable_irq (int);
void UART0_IRQHandler (void);


#endif /* INCLUDES_NVIC_H_ */
