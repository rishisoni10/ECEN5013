/*
 * dma.h
 *
 *  Created on: Nov 1, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_BASE_DMA_H_
#define INCLUDES_BASE_DMA_H_

#include "main.h"


void dma_init(void);	//8 bit transfer
void enable_dma(uint8_t* add_src, uint8_t* add_dest, uint32_t len);
void DMA0_IRQHandler(void);

#endif /* INCLUDES_BASE_DMA_H_ */
