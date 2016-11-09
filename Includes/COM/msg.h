/*
 * msg.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_ASW_MSG_H_
#define INCLUDES_ASW_MSG_H_

#define ACK_NACK_LEN 4			//packet length for ack/nack packet
#define MAX_DATA_SIZE 10

typedef enum CMD {					//commands set
	LED_ON = 0xC1,
	BLINK_SLOW = 0xC2,
	BLINK_FAST = 0xC3,
	DANCE_OFF = 0xC4,
	DANCE_ON = 0xC5,
	BRIGHTNESS_SET = 0xC6,
	ACK_PACKET = 0xA1,
	NACK_PACKET = 0xA0
}Cmds;

typedef struct CI_Msg {
	Cmds command; 					// Command operation
	uint8_t length; 				// Size of message
	uint8_t data[MAX_DATA_SIZE]; 	// Generic data payload
	uint16_t checksum; 				// Error detection checksum
}CI_Msg_t;

CI_Msg_t MSG_PACK;

typedef enum LED_brightness {		//brightness control
	TEN_PERCENT = 0x10,
	TWENTY_PERCENT = 0x20,
	THIRTY_PERCENT = 0x30,
	FORTY_PERCENT = 0x40,
	FIFTY_PERCENT = 0x50,
	SIXTY_PERCENT = 0x60,
	SEVENTY_PERCENT = 0x70,
	EIGHTY_PERCENT = 0x80,
	NINTY_PERCENT = 0x90,
	CENT_PERCENT = 0xFF
}LED_bright_t;

#define TEN 0.1						//brightness levels
#define TWENTY 0.2
#define THIRTY 0.3
#define FORTY 0.4
#define FIFTY 0.5
#define SIXTY 0.6
#define SEVENTY 0.7
#define EIGHTY 0.8
#define NINTY 0.9
#define CENT 1.0

typedef enum LED_CNTRL {			//led on off
	RED_ON = 0x01,
	GREEN_ON = 0x02,
	BLUE_ON = 0x04,
	YELLOW_ON = 0x03,
	CYAN_ON = 0x06,
	MAGENTA_ON = 0x05,
	WHITE_ON = 0x07,
	ALL_OFF = 0x00
}LED_control_t;

#endif /* INCLUDES_ASW_MSG_H_ */
