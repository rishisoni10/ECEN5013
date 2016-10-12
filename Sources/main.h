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

/*------------------------------------------------------------------------------*/
 // SWITCHES
  #define DEBUG 			// uncomment this to enable log function (FRDM/BBB)
  #define FRDM	 			// uncomment this for serial debug (FRDM)
 // #define BBB   			// uncomment this for printf debug (BBB)
 // #define RGB_INTERACT   	// uncomment this to enable RGB LED Control from terminal
 // #define BUFFER_INERACT	// uncomment this to attach circular buffers to uart
 // #define UNIT_TEST       // uncomment this to perform circular buffer test log
 // #define LOGGER_TEST		// uncomment this to enaable log test samples
 // #define PROFILE			// uncomment this to enable profile samples
/*-------------------------------------------------------------------------------*/


#endif /* SOURCES_MAIN_H_ */
