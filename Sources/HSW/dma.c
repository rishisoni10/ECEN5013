/*
 * dma.c
 *
 *  Created on: Nov 1, 2016
 *      Author: vikhyat
 */

#include "main.h"


extern uint8_t dma_complete;

void dma_init(void)
{
	//Step 1: Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;		//clock gate enable to DMA MUX
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;		//clock gate enable to DMA

	// Disable DMA Mux channel first
	DMAMUX0_CHCFG0 = 0;

	DMA_DCR0 |= (DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SINC_MASK);

	// Enable DMA channel and source
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(60); // Enable DMA channel

	// Enable interrupt
	NVIC_EnableIRQ(DMA0_IRQn);
}




void enable_dma(uint8_t* add_src, uint8_t* add_dest, uint32_t len)
{
	uint32_t main_len;

	DMA_SAR0 = (uint32_t)add_src;
	DMA_DAR0 = (uint32_t)add_dest;

#ifndef DMA_OPT
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(len); 	//bytes to transfer

	DMA_DCR0 |= (DMA_DCR_SSIZE(1) |		// Set source size to 8 bits
				 DMA_DCR_DSIZE(1));		// Set destination size of 8 bits

	DMA_DCR0 |= DMA_DCR_START_MASK;


#else
	main_len = len % 4;
	if(main_len == 0)	//move in 32 bit
	{
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(len); 	//bytes to transfer

		DMA_DCR0 |= (DMA_DCR_SSIZE(0) |		// Set source size to 32 bits
					 DMA_DCR_DSIZE(0));		// Set destination size of 32 bits

		DMA_DCR0 |= DMA_DCR_START_MASK;
	}
	else
	{
		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR((len - main_len)); 	//bytes to transfer

		DMA_DCR0 |= (DMA_DCR_SSIZE(0) |		// Set source size to 32 bits
					 DMA_DCR_DSIZE(0));		// Set destination size of 32 bits

		DMA_DCR0 |= DMA_DCR_START_MASK;

	//	while(!dma_complete);
	//	dma_complete = 0;


		DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(main_len); 	//bytes to transfer

		DMA_DCR0 |= (DMA_DCR_SSIZE(1) |		// Set source size to 8 bits
					 DMA_DCR_DSIZE(1));		// Set destination size of 8 bits

		DMA_DCR0 |= DMA_DCR_START_MASK;
	}
#endif

}

