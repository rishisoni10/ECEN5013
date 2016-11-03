/*
 * spi.h
 *
 *  Created on: Oct 31, 2016
 *      Author: Rishi
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

void spi_init(void);

uint8_t spi_tx_byte(uint8_t*, uint32_t);

uint8_t spi_rx_byte (uint8_t*, uint32_t);


#endif /* INCLUDES_SPI_H_ */
