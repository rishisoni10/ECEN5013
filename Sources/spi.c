/*
 * spi.c
 *
 *  Created on: Oct 30, 2016
 *      Author: Rishi Soni
 *      Description: SPI driver for FRDM-KL25z
 */

#define SPI0_C1_MASK				01010100
//#define SPI0_C2_MASK				00010000
#define SPI0_BR_MASK				00000001
#define PORTC_ALT2_MOSI_MASK		0x200
#define PORTC_ALT2_MISO_MASK		0x200
#define PORTC_GPIO_CS_MASK			0x100
#define PORTC_GPIO_OUT_MASK			0x01
#define PORTC_GPIO_SET				0x01
#define SPI0_DISABLE_MASK			0x10

void spi_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;  //enable clock to Port C
	PORTC_PCR6 |= PORTC_ALT2_MOSI_MASK; //PTC6 pin as SPI MOSI
	PORTC_PCR7 |= PORTC_ALT2_MISO_MASK; //PTC7 pin as SPI MISO
	PORTC_PCR4 |= PORTC_GPIO_CS_MASK;	//PTC4 pin as GPIO
	GPIOC_PDDR |= PORTC_GPIO_OUT_MASK;	//PTC4 pin set as output
	GPIOC_PSOR |= PORTC_GPIO_SET;		//set PTC4 pin high
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;   //Clock enable for SPI0
	SPI0_C1 |= SPI0_DISABLE_MASTER; 	//disable SPI0 and set as master
	SPI0_BR |= SPI0_BR_MASK;			//set baud rate as
	//SPI0_C2 |= SPI0_C2_MASK;
	SPI0_C1 |= SPI0_C1_MASK;			//enable SPI0 and set as master
}


uint8_t spi_tx_byte(uint8_t *data, uint32_t length)
{
	volatile uint8_t clear_reg;
	while(length--)
	{
		GPIOC_PSOR = 0;				//select the slave device
		//if buffer empty, write byte(char)
		while(!(SPI0_S & SPI_S_SPTEF_MASK))	{}	//wait for tx to get ready
		if(SPI0_S & SPI_S_SPTEF_MASK) 				//if SPTEF==1
		{
			SPI0_D = *data;
			data++;
		}

		while (!(SPI0_S & SPI_S_SPRF_MASK))	{}	//wait until tx is complete
		if(SPI0_S & SPI_S_SPRF_MASK)
		{
			clear_reg = SPI0_D;			//clear SPRF
		}
	}
	GPIOC_PSOR |= PORTC_GPIO_SET;		//deselect slave device
	return 0;
}


uint8_t spi_rx_byte (uint8_t *data, uint32_t length)
{
	volatile uint8_t clear_reg;
	while(length--)
	{
		GPIOC_PSOR = 0;							//select the slave device
		while(!(SPI0_S & SPI_S_SPRF_MASK))	{}	//wait for rx to get ready
		//if data buffer is full, data can be read
		if(SPI0_S & SPI_S_SPRF_MASK)		//SPRF==1
		{
			*data = SPI0_D;
			data++;
		}

	}
	GPIOC_PSOR |= PORTC_GPIO_SET;
	return 0;
}


