/*
 * SPI_Wrapper.h
 *
 *  Created on: 09-Nov-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_HSW_SPI_WRAPPER_H_
#define SOURCES_HSW_SPI_WRAPPER_H_

#include "main.h"

#ifdef BBB
#include "spiBBB.h"
spi* spi;
#endif

#ifndef BBB
#include "spi.h"
#endif

inline uint8_t SPI_Transfer(uint8_t data){
uint8_t result;
#ifdef BBB
result = spi->transfer(data);
#endif

#ifndef BBB
result = spi_write_byte(data);
#endif

return (result);
}


#endif /* SOURCES_HSW_SPI_WRAPPER_H_ */
