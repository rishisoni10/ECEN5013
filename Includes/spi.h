/*
 * spi.h
 *
 *  Created on: Oct 31, 2016
 *      Author: Rishi
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

void spi_init(void);

<<<<<<< Upstream, based on origin/Project_3
uint8_t spi_tx_byte(uint8_t);
=======
uint8_t spi_tx_byte(volatile uint8_t);
>>>>>>> 8d6f30e Integrated all the Project_3 components together

void spi_rx_byte (uint8_t);


#endif /* INCLUDES_SPI_H_ */
