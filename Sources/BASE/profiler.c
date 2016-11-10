/*
 * profiler.c
 *
 *  Created on: Nov 1, 2016
 *      Author: Vikhyat
 */


#include "main.h"
volatile uint32_t overflow_count=0;

void init_profiler(void)
{
	//Step 1: Clock config
    MCG_C1 |= MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;		// Internal Clock and Enable it(MCGIRCLK)
    MCG_C2 |= MCG_C2_IRCS_MASK;								// Fast internal clock mode
    SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;						// CLock gate enable for timer1
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(3);						// MCGIRCLK as timer source clock

    //Step 3: Disable timer counter  and set CPWMS=0 (up counter mode)
    TPM1_SC =0;

    //Step 4: Timer1 config
    TPM1_MOD = MOD_VAL;				//Set MOD value for timer1 (max value)
    TPM1_SC |= TPM_SC_PS(0);		//prescaler to divide by 1

	NVIC_EnableIRQ(TPM1_IRQn); 		//Enable at NVIC
	TPM1_SC |= TPM_SC_TOIE_MASK;	//Enable timer overflow interrupt
}

void calculate_time(void)
{
	uint32_t counter_val=0;
	float clk_time = 0;
	counter_val = TPM1_CNT;
	clk_time = counter_val/T1CLK; //clock

	if(overflow_count !=0)
	{
		clk_time = clk_time + ((MOD_VAL/T1CLK)*overflow_count);
	}

	char arr1[] = {"\r\nTime = "};
	LOG_2(arr1,clk_time);
/*	char arr2[] = {"\r\nClock cycles:"};
	LOG_1(arr2,counter_val);*/
/*	char arr3[] = {"\r\noverflow count:"};
	LOG_1(arr3,overflow_count);*/
	overflow_count = 0;
}
