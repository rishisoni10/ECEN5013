/*
 * nrf24L01.c
 *
 *  Created on: Nov 5, 2016
 *      Author: Rishi Soni
 *      Decription: nrf24L01 driver for interfacing with the FRDM-KL25z board
 *
 */

#include "nrf24L01.h"
#include "MKL25Z4.h"
#include "spi.h"
#include <stdint.h>

#define PORTC12_GPIO_CE_MASK				(0x00000100)
#define PORTC12_GPIO_OUT_MASK				(0x00001000)
#define PORTC12_GPIO_SET					(0x00001000)
#define PORTC4_GPIO_SET						(0x00000010)
#define NRF_CONFIG_INIT						(0x71)


void nrf_init()
{
	//CE pin intialization
	PORTC_PCR12 |= PORTC12_GPIO_CE_MASK;		//PTC12 pin as GPIO (CE)
	GPIOC_PDDR |= PORTC12_GPIO_OUT_MASK;		//PTC12 pin set as output
	//GPIOC_PDOR |= PORTC12_GPIO_SET;			//set PTC12 pin high
	uint8_t condition = 1;						//write to nrf
	nrf_receive(NORDIC_CONFIG,NRF_CONFIG_INIT,condition);	//configure the config register

	GPIOC_PDOR &= ~(PORTC4_GPIO_SET) ;				//select the slave device
}


uint8_t nrf_status()
{
	uint8_t data = 0;
	uint8_t dummy = 0xFF;
	uint8_t command = (R_REGISTER | (REGISTER_MASK & NORDIC_STATUS));			//send R_REGISTER command
	spi_tx_byte(command);
	spi_tx_byte(dummy);
	spi_rx_byte(data);
	return data;

}

void nrf_receive(uint8_t reg, uint8_t data, uint8_t condition)				//reg: selected register, data: data to be written
{
	uint8_t r_w_command;
	GPIOC_PDOR &= ~(PORTC4_GPIO_SET) ;		//select the slave device (CSN)
	uint8_t DATA = data;
	if (condition==1)
		r_w_command = W_REGISTER;
	else if(condition==0)
		r_w_command = R_REGISTER;

	uint8_t command = (r_w_command | (REGISTER_MASK & reg));
	spi_tx_byte(command);
	spi_tx_byte(DATA);
	GPIOC_PDOR |= (PORTC4_GPIO_SET) ;			//de-select slave device
}
