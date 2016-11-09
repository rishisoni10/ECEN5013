/*
 * led.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_ASW_LED_H_
#define INCLUDES_ASW_LED_H_

void led_init(void);

#define R(level) TPM2_C0V = TPM2_MOD *(level)		// Red with brightness b_color
#define G(level) TPM2_C1V = TPM2_MOD *(level)		// Green with brightness b_color
#define B(level) TPM0_C1V = TPM0_MOD *(level)		// Blue with brightness b_color

//led on with full brightness
#define R_ON	TPM2_C0V = TPM2_MOD
#define R_OFF	TPM2_C0V = 0

#define G_ON	TPM2_C1V = TPM2_MOD
#define G_OFF	TPM2_C1V = 0

#define B_ON	TPM0_C1V = TPM0_MOD
#define B_OFF	TPM0_C1V = 0

#endif /* INCLUDES_ASW_LED_H_ */
