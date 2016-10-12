/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mcg.h"

#define data 		10

void start_profiler(void);
void stop_profiler(void);

volatile uint32_t count = 0;

uint32_t main(void)
{
	uint8_t i = 0;
	pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT);

	uint32_t avg_clock_cycles;
	uint32_t avg_time;
	uint32_t sum1=0, sum2=0;
	float a [10];
	double b[10];


	while(i<10)
{
	uint8_t src[data];
	uint32_t length;
	length = data;
	uint8_t dst[data];

	start_profiler();
	my_memmove(dst, src, length);
	stop_profiler();

	a[i] = count*480 + TPM0_CNT;
	sum1 += a[i];
	b[i] = (a[i] / 48000000.00)*1000000.00;
	sum2 += b[i];

	i++;
}
	avg_clock_cycles = sum1/(10*i);
	avg_time = sum2/(i*10);

	return 0;
}

void start_profiler()
{
	// PLL clock select
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);

	// Select MCGPLLCLK/2
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

	// Enable TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Nullify the control registers to ensure counter is not running

	TPM0_SC = 0;
	TPM0_CONF = 0;

	//Set prescalar to 1 when counter is disabled
	TPM0_SC = TPM_SC_PS(0);

	//Enable Interrupts for the Timer Overflow
	TPM0_SC |= TPM_SC_TOIE_MASK;

	// Setting modulo value to set 10us as the execution timer
	TPM0_MOD = 480;

	//Enable the TPM COunter
	TPM0_SC |= TPM_SC_CMOD(1);

	//NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
	//enable_irq(INT_TPM0 - 16);

}

void stop_profiler()
{
	NVIC_DisableIRQ(TPM0_IRQn);
	//Disabling the counter
	TPM0_SC = 0;
	TPM0_CONF = 0;
}

void TPM0_IRQHandler()
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		TPM0_SC |= TPM_SC_TOF_MASK;
		count++;
	}
}
