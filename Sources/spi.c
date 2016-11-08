/*
 * spi.c
 *
 *  Created on: Oct 30, 2016
 *      Author: Rishi Soni
 *      Description: SPI driver for FRDM-KL25z
 */
#include "MKL25Z4.h"
#include<stdio.h>
#include<stdint.h>
#include "uart.h"
#include "Project2_settings.h"


#define SPI0_C1_MASK				01010100
//#define SPI0_C2_MASK				00010000
#define SPI0_BR_MASK				00000001
#define PORTC4_ALT2_MOSI_MASK		0x200
#define PORTC4_ALT2_MISO_MASK		0x200
#define PORTC4_GPIO_CS_MASK			0x00000100
#define PORTC4_GPIO_OUT_MASK		0x00000010
#define PORTC4_GPIO_SET				0x00000010
#define SPI0_DISABLE_MASK			0x14



void spi_init()
{
	//Turn on port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//Turn on SPI0 clock
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	//Setup ports for SPI0
	PORTC_PCR8 |= PORT_PCR_MUX(1);	//SS as GPIO pin
	PORTC_PCR5 |= PORT_PCR_MUX(2);	//SPI clock
	PORTC_PCR6 |= PORT_PCR_MUX(2);	//SPI MOSI
	PORTC_PCR7 |= PORT_PCR_MUX(2);	//SPI MISO

	//Set port C, pin 8 data direction to output
	PTC_BASE_PTR->PDDR |= 1<<8;

	SPI0_C1 = SPI_C1_SPE_MASK;
	SPI0_C2 = 0x00;

	SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SPE_MASK | SPI_C1_CPHA_MASK;

	//prescaler = 1, divisor = 4, 24MHz/4 = 6MHz
	SPI0_BR = 0x01;
}

/*void spi_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;  //enable clock to Port C
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;   //Clock enable for SPI0
	PORTC_PCR6 |= PORTC4_ALT2_MOSI_MASK; //PTC6 pin as SPI MOSI
	PORTC_PCR7 |= PORTC4_ALT2_MISO_MASK; //PTC7 pin as SPI MISO
	PORTC_PCR4 |= PORTC4_GPIO_CS_MASK;	//PTC4 pin as GPIO
	GPIOC_PDDR |= PORTC4_GPIO_OUT_MASK;	//PTC4 pin set as output
	GPIOC_PDOR |= PORTC4_GPIO_SET;		//set PTC4 pin high
	SPI0_C1 |= SPI0_DISABLE_MASK; 		//disable SPI0 and set as master
	SPI0_BR |= SPI0_BR_MASK;			//set baud rate as
	//SPI0_C2 |= SPI0_C2_MASK;
	SPI0_C1 |= SPI0_C1_MASK;			//enable SPI0 and set as master
}*/


uint8_t spi_tx_byte(uint8_t data)
{
	volatile uint8_t clear_reg;

		GPIOC_PDOR &= ~(PORTC4_GPIO_SET) ;				//select the slave device
		//if buffer empty, write byte(char)
		while(!(SPI0_S & SPI_S_SPTEF_MASK))	{}	//wait for tx to get ready
		if(SPI0_S & SPI_S_SPTEF_MASK) 				//if SPTEF==1
		{
			SPI0_D = data;
		}

		while (!(SPI0_S & SPI_S_SPRF_MASK))	{}	//wait until tx is complete
		if(SPI0_S & SPI_S_SPRF_MASK)
		{
			clear_reg = SPI0_D;			//clear SPRF
		}
	GPIOC_PSOR |= PORTC4_GPIO_SET;		//deselect slave device
	return clear_reg;
}


void spi_rx_byte (uint8_t data)
{
	volatile uint8_t clear_reg;
		GPIOC_PDOR &= ~(PORTC4_GPIO_SET) ;				//select the slave device
		while(!(SPI0_S & SPI_S_SPRF_MASK))	{}	//wait for rx to get ready
		//if data buffer is full, data can be read
		if(SPI0_S & SPI_S_SPRF_MASK)		//SPRF==1
		{
			data = SPI0_D;
		}

	GPIOC_PSOR |= PORTC4_GPIO_SET;		//deselect slave device
	//return 0;
}


