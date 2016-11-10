/*
 * frdm_msg.c
 *
 *  Created on: Oct 30, 2016
 *      Author: vikhyat
 */

/* This fn is called when packet_complete flag is set
 * Load the buffer elements into the msg struct
 * Compute checksum
 * Raise error flag and send nack packet to terminal (via tx ISR)
 *
 * if no error
 * Send ack packet
 * call led,brightness,blink or dance functions
 */
#include "main.h"

uint8_t  led_stat = 8;
uint8_t exit_loop;
float level = 1;

void decode_packet (void)
{
		uint8_t chk_msb,chk_lsb,payload;

		MSG_PACK.command = del_cbuff(&RXBUFF);

		MSG_PACK.length = del_cbuff(&RXBUFF);

		//loop to take in all data
		//check if data exists
		for(int i=0;i<(MSG_PACK.length)-HEAD_PACK_SIZE;i++)
		{
			MSG_PACK.data[i] = del_cbuff(&RXBUFF);
			payload = MSG_PACK.data[i];
		}

		chk_msb = del_cbuff(&RXBUFF);			//read from rx buff
		chk_lsb = del_cbuff(&RXBUFF);
		MSG_PACK.checksum = ((uint16_t)(chk_msb) << 8) | chk_lsb;

												//call checksum validate
		if(checksum_validate()==CHKSUM_FAIL)
		{
												//send NACK
			ack_nack_transmit(NACK_PACKET);
			LOG_0("\r\nNACK\r\n");
		}
		else
		{
												//read command byte and call functions
			if(MSG_PACK.command == LED_ON)
				led_control(payload);

			else if(MSG_PACK.command == BLINK_SLOW)
				blink(BLINK_SLOW);
			else if(MSG_PACK.command == BLINK_FAST)
				blink(BLINK_FAST);

			else if(MSG_PACK.command == DANCE_OFF)
				dance(DANCE_OFF);
			else if(MSG_PACK.command == DANCE_ON)
				dance(DANCE_ON);

			else if(MSG_PACK.command == BRIGHTNESS_SET)
				brightness_control(payload);

												//send ACK
			ack_nack_transmit(ACK_PACKET);
			LOG_0("\r\nACK\r\n");
		}
}

/* Send ack or nack packet on checksum success or fail
 */
void ack_nack_transmit (Cmds packet)
{
	uint8_t chk_msb,chk_lsb;

	MSG_PACK.command = packet;
	MSG_PACK.length = ACK_NACK_LEN;
	MSG_PACK.checksum = packet + ACK_NACK_LEN;

	chk_msb = (uint8_t)(MSG_PACK.checksum >> 8);
	chk_lsb = MSG_PACK.checksum;
}

/* Calculate addition checksum
 * add all valid byte elements
 * return error or success
 */
MSG_ERR_t checksum_validate (void)
{
	uint16_t check_sum;

	check_sum = MSG_PACK.command + MSG_PACK.length;
	for(int i=0;i<((MSG_PACK.length)-HEAD_PACK_SIZE);i++)
	{
		check_sum += MSG_PACK.data[i];
	}
	if(check_sum == MSG_PACK.checksum)
		return CHKSUM_PASS;
	else
		return CHKSUM_FAIL;
}

/* Turn ON/OFF led based on enum parameter
 */
void led_control (uint8_t payload)
{
	if (payload == RED_ON)
	{
		R_ON; G_OFF; B_OFF;
		led_stat = 1;
	}
	else if (payload == GREEN_ON)
	{
		R_OFF; G_ON; B_OFF;
		led_stat = 2;
	}
	else if (payload == BLUE_ON)
	{
		R_OFF; G_OFF; B_ON;
		led_stat = 3;
	}
	else if (payload == YELLOW_ON)
	{
		R_ON; G_ON; B_OFF;
		led_stat = 4;
	}
	else if (payload == CYAN_ON)
	{
		R_OFF; G_ON; B_ON;
		led_stat = 5;
	}
	else if (payload == MAGENTA_ON)
	{
		R_ON; G_OFF; B_ON;
		led_stat = 6;
	}
	else if (payload == WHITE_ON)
	{
		R_ON; G_ON; B_ON;
		led_stat = 7;
	}
	else
	{
		R_OFF; G_OFF; B_OFF;
		led_stat = 8;
	}
}

/* Control led brightness based on enum parameter
 */
void brightness_control (uint8_t payload)
{
	if(payload == TEN_PERCENT)
		level = TEN;
	else if(payload == TWENTY_PERCENT)
		level = TWENTY;
	else if(payload == THIRTY_PERCENT)
		level = THIRTY;
	else if(payload == FORTY_PERCENT)
		level = FORTY;
	else if(payload == FIFTY_PERCENT)
		level = FIFTY;
	else if(payload == SIXTY_PERCENT)
		level = SIXTY;
	else if(payload == SEVENTY_PERCENT)
		level = SEVENTY;
	else if(payload == EIGHTY_PERCENT)
		level = EIGHTY;
	else if(payload == NINTY_PERCENT)
		level = NINTY;
	else
		level = CENT;

	if(led_stat == 1)
		R(level);
	else if(led_stat == 2)
		G(level);
	else if(led_stat == 3)
		B(level);
	else if(led_stat == 4)
	{
		R(level);
		G(level);
	}
	else if(led_stat == 5)
	{
		G(level);
		B(level);
	}
	else if(led_stat == 6)
	{
		R(level);
		B(level);
	}
	else
	{
		R(level);
		G(level);
		B(level);
	}
}

void blink (Cmds blink_cmd)
{
/*
	if(blink_cmd == BLINK_SLOW)
	{
		while(1)
		{

			if(exit_loop == 1)
				break;
		}
	}
	else
	{

	}
*/
}

void dance (Cmds dance_cmd)
{
	/*
	if(dance_cmd == DANCE_ON)
	{

	}
	else
	{

	}
	*/
}
