/*
 * led.h
 *
 *  Created on: Oct 10, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_LED_H_
#define INCLUDES_LED_H_


#define Red(x) TPM2_C0V=TPM2_MOD *(x)		// Red with brightness x
#define Green(x) TPM2_C1V=TPM2_MOD *(x)		// Green with brightness x
#define Blue(x) TPM0_C1V=TPM0_MOD *(x)		// Blue with brightness x

typedef enum {
	 Red=0,
	 Green,
	 Blue,
	 RedGreen,
	 RedBlue,
	 GreenBlue,
	 RedGreenBlue,
	 alloff
}ledcolor_e;

ledcolor_e currentled;
float currentbritness;

void led_init(void);
void Control_LED(void);
void Change2PreviousColor(ledcolor_e ,float );
void Change2NextsColor(ledcolor_e ,float );
void IncreaseBritness(ledcolor_e ,float );
void DecreaseBritness(ledcolor_e ,float );
void changeLED(void);



#endif /* INCLUDES_LED_H_ */
