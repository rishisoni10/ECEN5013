/*

 * led.c
 *
 *  Created on: Oct 10, 2016
 *      Author: vikhyat
 */

#include "main.h"


typedef void(*ledfunctionlist)(ledcolor_e ,float );

void led_init(void)
{
	//Step 1: Clock config
    MCG_C1 |= MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;		// Internal Clock and Enable it(MCGIRCLK)
    MCG_C2 |= MCG_C2_IRCS_MASK;								// Fast internal clock mode
    SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK|SIM_SCGC6_TPM0_MASK;	// CLock gate enable for timer0 and 2
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(3);						// MCGIRCLK as timer source clock
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK; // Clock gate enable for Port B and D

    //Step 2: Port config
    PORTB_PCR18 |= PORT_PCR_MUX(3);	// Alt 3 mode -TPM2_CH0
    PORTB_PCR19 |= PORT_PCR_MUX(3);	// Alt 3 mode -TPM2_CH1
    PORTD_PCR1  |= PORT_PCR_MUX(4);	// Alt 4 mode -TPM0_CH1

    PTB_BASE_PTR->PDDR = 1 << 18;	// PTB18 as output
    PTB_BASE_PTR->PDDR = 1 << 19;	// PTB19 as output
    PTD_BASE_PTR->PDDR = 1 << 1;  	// PTD1 as output

    //Step 3: Disable timer counter  and set CPWMS=0 (up counter mode)
    TPM2_SC =0;
    TPM0_SC =0;

    //Step 4: Timer 0 and 2 config
    TPM2_MOD = 65535;				//Set MOD value for timer2 (max value)
    TPM0_MOD = 65535;				//Set MOD vlaue for timer0 (max value)

    //edge aligned with MSB and set on match with ELSA
    TPM2_C0SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM2_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM0_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

    //Step 5: Re-enable timers
    TPM2_SC |= TPM_SC_CMOD(1) | TPM_SC_PS(0);
    TPM0_SC |= TPM_SC_CMOD(1) | TPM_SC_PS(0);
}

void Change2PreviousColor(ledcolor_e color,float brigtness){

	if(color != Red){
		color--;
	}
	else {
		color = alloff;
	}
	 currentbritness = brigtness;
	 currentled = color;
}

void Change2NextsColor(ledcolor_e color,float brigtness){

	if(color != alloff){
		color++;
	}
	else {
		color = Red;
	}
	currentbritness = brigtness;
	currentled = color;
}

void IncreaseBritness(ledcolor_e color,float brigtness){

	if(brigtness < 1){
		brigtness += 0.1;
	}
	currentled = color;
	currentbritness = brigtness;
}

void DecreaseBritness(ledcolor_e color,float brigtness){

	if(brigtness > 0){
		brigtness -= 0.1;
	}
	else{
		brigtness = 0;
	}
	currentled = color;
	currentbritness = brigtness;
}


void changeLED(void){

	switch(currentled)
	{
	case Red:
		Red(currentbritness);
		Green(0);
		Blue(0);
		break;
	case Green:
		Red(0);
		Green(currentbritness);
		Blue(0);
		break;
	case Blue:
		Red(0);
		Green(0);
		Blue(currentbritness);
		break;
	case RedGreen:
		Red(currentbritness);
		Green(currentbritness);
		Blue(0);
		break;
	case RedBlue:
		break;
		Red(currentbritness);
		Green(0);
		Blue(currentbritness);
	case GreenBlue:
		Red(0);
		Green(currentbritness);
		Blue(currentbritness);
		break;
	case RedGreenBlue:
		Red(currentbritness);
		Green(currentbritness);
		Blue(currentbritness);
		break;
	case alloff:
		Red(0);
		Green(0);
		Blue(0);
		break;
	}

}

void Control_LED(void)
{
	ledfunctionlist ledFunction;

	if(LED_Control_Flag)
	{
		switch(LED_control_word)
		{
		case 'A':
			LOG_4("\r\nPREVIOUS COLOR\r\n");
			ledFunction = &Change2PreviousColor;
			break;

		case 'D':
			LOG_4("\r\nNEXT COLOR\r\n");
			ledFunction = &Change2NextsColor;
			break;

		case 'W':
			LOG_4("\r\nINCREASE BRIGTNESS\r\n");
			ledFunction = &IncreaseBritness;
			break;

		case 'S':
			LOG_4("\r\nDECREASE BRIGTNESS\r\n");
			ledFunction = &DecreaseBritness;
			break;
		case 'B':
			LOG_4("\r\nComming out of LED control\r\n");
			ledFunction = &IncreaseBritness;
			CmdProcessingDone = 0;
			MENUprinted = 0;
			break;
		default:
			//LOG_4("\r\nINVALID CAMMAND\r\n");
			ledFunction = &IncreaseBritness;
			break;
		}

		ledFunction(currentled,currentbritness);
		changeLED();

		LED_Control_Flag = 0;
	}
}


