/*
 * spiBBB.h
 *
 *  Created on: 09-Nov-2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_HSW_SPIBBB_H_
#define INCLUDES_HSW_SPIBBB_H_

#include "main.h"

#ifdef BBB

#include <string>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class SPI {
public:

	SPI();
	uint8_t transfer(uint8_t tx_);
	virtual ~SPI();

private:

	// Default SPI device
	string device;
	// SPI Mode set
	uint8_t mode;
	// word size
	uint8_t bits;
	// Set SPI speed
	uint32_t speed;
	int fd;

	void init();
};
#endif

#endif /* INCLUDES_HSW_SPIBBB_H_ */
