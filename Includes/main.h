/*
 * main.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_HSW_MAIN_H_
#define INCLUDES_HSW_MAIN_H_

#include "HSW/uart.h"
#include "BASE/buffer.h"
#include "HSW/nvic.h"

#include "COM/msg.h"
#include "COM/frdm_msg.h"
#include "ASW/led.h"

#include "MKL25Z4.h"
#include "stdint.h"
#include "BASE/logger.h"
#include "HSW/dma.h"
#include "BASE/profiler.h"
#include "BASE/memory.h"
#include "HSW/spi.h"
#include "ASW/NRF24L01.h"

//#define LOG			//to enable uart logging
//#define MSG
#define DMA_test
//#define BBB

#endif /* INCLUDES_HSW_MAIN_H_ */
