/*
 * Project2_settings.h
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_PROJECT2_SETTINGS_H_
#define SOURCES_PROJECT2_SETTINGS_H_

#define RX_BUFF_LEN 10
#define TX_BUFF_LEN 100

#define PR_BUFFERECHO_OFF 0
#define PR_BUFFERECHO_ON  1

#define PR_BUFFERECHO PR_BUFFERECHO_OFF

#define PR_LEDCONTROL_OFF 0
#define PR_LEDCONTROL_ON  1
#define PR_LEDCONTROL PR_LEDCONTROL_OFF

#define PR_LOGGER_OFF 0
#define PR_LOGGER_ON  1
#define PR_LOGGER PR_LOGGER_OFF



  #define DEBUG 			// uncomment this to enable log function (FRDM/BBB)
  #define FRDM	 			// uncomment this for serial debug (FRDM)
 // #define BBB   			// uncomment this for printf debug (BBB)



#endif /* SOURCES_PROJECT2_SETTINGS_H_ */
