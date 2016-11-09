
/*
 * spi.c
 *
 *  Created on: 08-11-2016
 *      Author: Vikhyat and Rishi
 */

#include "main.h"
#include "MKL25Z4.h"

#ifndef BBB

#define WordByteMask(x)    ((0xF000) >> (x*8))
#define WordByteOffset(x)  (x*8)

uint8_t spi_write_byte(uint8_t data)
{
	uint8_t result = 0;
	while(WAIT_SPTEF);
	SPI_D_REG(SPI0) = data;
	while(WAIT_SPRF);
	result = SPI_D_REG(SPI0);
	return(result);
}

uint8_t spi_read_byte(void)
{
	uint8_t result = 0;
	while(WAIT_SPTEF);
	SPI_D_REG(SPI0) = SPI_DUMMY;
	while(WAIT_SPRF);
	result = SPI_D_REG(SPI0);
	return(result);
}


uint32_t spi_write_word(uint32_t data)
{
	uint8_t result = 0;
	uint8_t word = 4, i = 0;
	uint8_t temp;
	while(word){
		// send msb first
		temp = (uint8_t)((data & WordByteMask(word-1)) >> WordByteOffset(i++));
		result |= spi_write_byte(temp);
		result << 8;
		word--;
	}
}

uint32_t spi_read_word(void)
{
	uint8_t result = 0;
	uint8_t word = 4;
	uint8_t temp = SPI_DUMMY;
	while(word){
		result |= spi_write_byte(temp);
		result << 8;
		word--;
	}
}


void spi_flush(void)
{
	SPI0_C1&=0xBF;
	spi_init();
}


void spi0_init(void)
{
	// Turn on port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	// Turn on SPI0 clock
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	// Set up ports for SPI0
	PORTC->PCR[4] |= PORT_PCR_MUX(1); // ss as gpio pin
	PORTC->PCR[5] |= PORT_PCR_MUX(2);
	PORTC->PCR[6] |= PORT_PCR_MUX(2);
	PORTC->PCR[7] |= PORT_PCR_MUX(2);

	// Set port C, pin 8 data direction to output
	PTC_BASE_PTR->PDDR |= 1<<4;

	SPI_C1_REG(SPI0) = SPI_C1_SPE_MASK;
	SPI_C2_REG(SPI0) = 0x00;

	SPI_C1_REG(SPI0) = SPI_C1_MSTR_MASK |SPI_C1_SPE_MASK;
	// prescaler=1, divisor=4 , 24MHz/4 = 6MHz
	SPI0_BR = SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x08) ;
}

#endif


