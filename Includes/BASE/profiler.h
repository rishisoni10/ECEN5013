/*
 * profiler.h
 *
 *  Created on: Nov 1, 2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_HSW_PROFILER_H_
#define INCLUDES_HSW_PROFILER_H_

#define MOD_VAL 40			//to get time period of 10Us
#define T1CLK  	4

void calculate_time(void);
void init_profiler(void);

#define start_time() TPM1_SC |= TPM_SC_CMOD(1)			//run counter
#define end_time()	 TPM1_SC &= ~TPM_SC_CMOD(1)		//stop counter

#endif /* INCLUDES_HSW_PROFILER_H_ */
