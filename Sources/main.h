/*
 * main.h
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

/*----------------------------------------------------------------------------
 * include headers of the files you are using in this file
 -----------------------------------------------------------------------------*/

#include "nvic.h"
#include "uart.h"
#include "led.h"
#include "MKL25Z4.h"
#include "log.h"
#include "cirbuf.h"
#include "Project2_settings.h"
#include "com.h"
#include "data.h"
#include "profile.h"
#include "memory.h"

#include <stdint.h>
#include<stdint.h>
#include <math.h>

extern uint8_t TransferState;
extern uint8_t LEDControlRequested;
extern uint8_t ECOReqested;
extern uint8_t MENUprinted;
extern uint8_t CmdProcessingDone;

#endif /* SOURCES_MAIN_H_ */
