/*
 * led.c
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#include "main.h"

extern uint8_t received_byte,rx_flag,dma_complete;

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
void Handle_msg(void){
	uint8_t str[2],byte_length=0,byte_process=0;
	uint8_t current_length=0,packet_length=0,packet_complete=0;
while(1)
	{
		if(rx_flag == 1)
		{
					str[byte_length] = received_byte;
					byte_length++;
					if(byte_length == 2)
					{
						received_byte = myAtoi(str);
						byte_process = 1;
						byte_length = 0;
						LOG_0("-");
					}

					if(byte_process == 1)
					{
						byte_process = 0;
						add_cbuff(&RXBUFF,received_byte);

						current_length ++;
						if(current_length == 2)					//length byte from the second byte
						{
							packet_length = received_byte;
							if(packet_length == 0)
							{
								current_length = 0;
								byte_length = 0;
								LOG_0("\r\npacket has error\r");
							}
						}

						if(current_length == packet_length)
						{
							packet_complete = 1;
							current_length = 0;
						}
					}
					UART0_C2 |= UART0_C2_RIE_MASK; 			//Peripheral interrupt enable (RX)
					rx_flag = 0;
		}

		if(packet_complete == 1) {
			decode_packet();
			packet_complete = 0;
		}
	}
}
