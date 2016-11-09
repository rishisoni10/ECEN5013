#include "main.h"

uint8_t nrf_status_read()
{
	uint8_t statusValue = SPI_Transfer(NRF_COMMAND_NOP);
}

uint8_t nrf_read_register(unsigned char reg) //read command
{
	NRF_CS_ENABLE();
	SPI_Transfer((reg)|NRF_COMMAND_R_REGISTER);
	uint8_t regValue = nrf_status_read();
	NRF_CS_DISABLE();
	return regValue;
}

void nrf_write_register(unsigned char reg, unsigned char val) //write command
{
	NRF_CS_ENABLE();
	SPI_Transfer((reg)|NRF_COMMAND_W_REGISTER);
	SPI_Transfer(val);
	NRF_CS_DISABLE();
}


void nrf_flush_tx_fifo(){
	NRF_CS_ENABLE();
	SPI_Transfer(NRF_COMMAND_FLUSH_TX);
	NRF_CS_DISABLE();
}

void nrf_flush_rx_fifo(){
	NRF_CS_ENABLE();
	SPI_Transfer(NRF_COMMAND_FLUSH_RX);
	NRF_CS_DISABLE();
}

void nrf_transmit_data(){
	NRF_CS_ENABLE();
	SPI_Transfer(NRF_COMMAND_W_TX_PAYLOAD);
	SPI_Transfer(0xff); //Random data, loop for multiple
	NRF_CS_DISABLE();
}
