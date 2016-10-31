/*
 * spi.c
 *
 *  Created on: Oct 30, 2016
 *      Author: Rishi
 */

#define SPI0_C1_MASK				01010100
#define SPI0_C2_MASK				00010000
#define SPI0_BR_MASK				00000000

void spi_init()
{
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;					//Clock gate enable for SPI

	SPI0_C1 |= SPI0_C1_MASK;
	SPI0_C2 |= SPI0_C2_MASK;
	SPI0_BR |= SPI0_BR_MASK;
}


