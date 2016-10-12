/*
 * profile.c
 *
 *  Created on: 12-Oct-2016
 *      Author: Vikhyat
 */


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

