/*
 * spi.h
 *
 *  Created on: Nov 7, 2016
 *      Author: vikhyat
 */
#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#include "main.h"

#ifndef BBB

#include<stdint.h>

void spi_init(void);
uint8_t spi_write_byte(uint8_t data);
uint8_t spi_read_byte(void);
uint32_t spi_write_word(uint32_t data);
uint32_t spi_read_word(void);
void spi_flush(void);

#define NRF_CS_ENABLE() (PTC_BASE_PTR->PCOR |= 1<<4)
#define NRF_CS_DISABLE() (PTC_BASE_PTR->PSOR |= 1<<4)
#define WAIT_SPTEF ( !(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
#define WAIT_SPRF ( !(SPI_S_REG(SPI0) & SPI_S_SPRF_MASK))

#define SPI_DUMMY 0xFF

#endif

#endif /* INCLUDES_SPI_H_ */
