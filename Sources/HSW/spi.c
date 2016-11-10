
/*
 * spi.c
 *
 *  Created on: 08-11-2016
 *      Author: Vikhyat and Rishi
 */

#include "main.h"
#include "MKL25Z4.h"


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
	 //SPI0 module initialization
	  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK; // Turn on clock to SPI0 module
	  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; // Turn on clock to Port D module
	  GPIOC_PSOR |= GPIO_PSOR_PTSO(0x10); // PTD0 = 1 (CS inactive)
	    GPIOC_PDDR |= GPIO_PDDR_PDD(0x10); // PTD0 pin is GPIO output
	    PORTC_PCR4 = PORT_PCR_MUX(0x1);    //Set PTD0 to mux 1 [SPI0_PCS0]
	    PORTC_PCR5 = PORT_PCR_MUX(0x2);    //Set PTD1 to mux 2 [SPI0_SCK]
	    PORTC_PCR6 = PORT_PCR_MUX(0x2);    //Set PTD2 to mux 2 [SPI0_MOSI]
	    PORTC_PCR7 = PORT_PCR_MUX(0x2);    //Set PTD3 to mux 2 [SPIO_MISO]


	  //SETUP SPI0 PERIPHERAL

	  SPI0_C1 = SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK; // Enable SPI0 module, master mode //SETS SPI ENABLE AND SPI MASTER BITS
	  //SPI0_C2 = 0x19;
	  SPI0_BR = SPI_BR_SPPR(0x03) | SPI_BR_SPR(0x08) ; // BaudRate = BusClock / ((SPPR+1) * 2^(SPR+1)) = 20970000 / ((4+1) * 2^(2+1)) = 524.25 kHz
}


