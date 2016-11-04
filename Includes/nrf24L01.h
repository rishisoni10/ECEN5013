/*
 * nrf24L01.h
 *
 *  Created on: Nov 1, 2016
 *      Author: Rishi Soni
 *      Description: Register-definition file for the nrf24L01 wireless module
 */

#ifndef INCLUDES_NRF24L01_H_
#define INCLUDES_NRF24L01_H_
#include <stdint.h>

#define __IO volatile
#define   __I     volatile const

//nrf24L01 register layout typedef
typedef struct {
	__IO uint8_t CONFIG;			//config register, offset: 0x00//
	__IO uint8_t EN_AA;				//Enhanced ShockBurst, offset: 0x01
	__IO uint8_t EN_RXADDR;			//Enabled RX addresses, offset: 0x02
	__IO uint8_t SETUP_AW;			//Setup address widths, offset: 0x03
	__IO uint8_t SETUP_RETR;		//Setup of automatic Retransmission, offset: 0x04
	__IO uint8_t RF_CH; 			//RF Channel, offset: 0x05
	__IO uint8_t RF_SETUP; 			//RF Setup Register, offset: 0x06
	__IO uint8_t STATUS;			//Status register, offset: 0x07
	__I  uint8_t OBSERVE_TX;		//Transmit observe register, offset: 0x08
	__I  uint8_t CD;				//Carrier Detect, offset: 0x09
	__IO uint8_t RX_ADDR_P0;		//Receive address data pipe 0, offset: 0x0A
	__IO uint8_t RX_ADDR_P1;		//Receive address data pipe 1, offset: 0x0B
	__IO uint8_t RX_ADDR_P2;		//Receive address data pipe 2, offset: 0x0C
	__IO uint8_t RX_ADDR_P3;		//Receive address data pipe 3, offset: 0x0D
	__IO uint8_t RX_ADDR_P4;		//Receive address data pipe 4, offset: 0x0E
	__IO uint8_t RX_ADDR_P5;		//Receive address data pipe 5, offset: 0x0F
	__IO uint8_t TX_ADDR;			//Transmit address, offset: 0x10
	__IO uint8_t RX_PW_P0;			//offset: 0x11
	__IO uint8_t RX_PW_P1;			//offset: 0x12
	__IO uint8_t RX_PW_P2;			//offset: 0x13
	__IO uint8_t RX_PW_P3;			//offset: 0x14
	__IO uint8_t RX_PW_P4;			//offset: 0x15
	__IO uint8_t RX_PW_P5;			//offset: 0x16
	__IO uint8_t FIFO_STATUS;		//FIFO Status Register, offset: 0x17
		 uint8_t RESERVED_0[32];	//ACK_PLD
		 uint8_t RESERVED_1[32];	//TX_PLD
		 uint8_t RESERVED_2[32];	//RX_PLD
	__IO uint8_t DYNPD;				//Enable Dyanamic Payload
	__IO uint8_t FEATURE;			//Feature Register
} NORDIC_Type, *NORDIC_MemMapPtr;


// nrf24L01 base addresses
#define NORDIC_BASE						(0x00)
#define NORDIC							((NORDIC_TYPE *)NORDIC_BASE)
#define NORDIC_BASE_PTR					(NORDIC)


//nrf24L01 - Register accessors
#define NORDIC_CONFIG_REG(base)				((base)->CONFIG)
#define NORDIC_EN_AA_REG(base)				((base)->EN_AA)
#define NORDIC_EN_RXADDR_REG(base)			((base)->EN_RXADDR)
#define NORDIC_SETUP_AW_REG(base)			((base)->SETUP_AW)
#define NORDIC_SETUP_RETR_REG(base)			((base)->SETUP_RETR)
#define NORDIC_RF_CH_REG(base)				((base)->RF_CH)
#define NORDIC_RF_SETUP_REG(base)			((base)->RF_SETUP)
#define NORDIC_STATUS_REG(base)				((base)->STATUS)
#define NORDIC_OBSERVE_TX_REG(base)			((base)->OBSERVE_TX)
#define NORDIC_CD_REG(base)					((base)->CD)
#define NORDIC_RX_ADDR_P0_REG(base)			((base)->RX_ADDR_P0)
#define NORDIC_RX_ADDR_P1_REG(base)			((base)->RX_ADDR_P1)
#define NORDIC_RX_ADDR_P2_REG(base)			((base)->RX_ADDR_P2)
#define NORDIC_RX_ADDR_P3_REG(base)			((base)->RX_ADDR_P3)
#define NORDIC_RX_ADDR_P4_REG(base)			((base)->RX_ADDR_P4)
#define NORDIC_RX_ADDR_P5_REG(base)			((base)->RX_ADDR_P5)
#define NORDIC_TX_ADDR_REG(base)			((base)->TX_ADDR)
#define NORDIC_RX_PW_P0_REG(base)			((base)->RX_PW_P0)
#define NORDIC_RX_PW_P1_REG(base)			((base)->RX_PW_P1)
#define NORDIC_RX_PW_P2_REG(base)			((base)->RX_PW_P2)
#define NORDIC_RX_PW_P3_REG(base)			((base)->RX_PW_P3)
#define NORDIC_RX_PW_P4_REG(base)			((base)->RX_PW_P4)
#define NORDIC_RX_PW_P5_REG(base)			((base)->RX_PW_P5)
#define NORDIC_FIFO_STATUS_REG(base)		((base)->FIFO_STATUS)
#define NORDIC_DYNPD_REG(base)				((base)->DYNPD)
#define NORDIC_FEATURE_REG(base)			((base)->FEATURE)


//nrf24L01 Register Masks

/*CONFIG bit fields*/
#define NORDIC_CONFIG_MASK_RX_DR(x)			((uint8_t)(((uint8_t)(x))<<6))	//Mask interrupt caused by RX_DR
#define NORDIC_CONFIG_MASK_TX_DS(X)			((uint8_t)(((uint8_t)(x))<<5))	//Mask interrupt caused by TX_DS
#define NORDIC_MASK_MAX_RT(x)				((uint8_t)(((uint8_t)(x))<<4))	//Mask interrupt caused by MAX_RT
#define NORDIC_EN_CRC(x)					((uint8_t)(((uint8_t)(x))<<3))	//Enable CRC
#define NORDIC_CRCO(x)						((uint8_t)(((uint8_t)(x))<<2))	//CRC encoding scheme
#define NORDIC_PWR_UP(x)					((uint8_t)(((uint8_t)(x))<<1))	//Power modes
#define NORDIC_PRIM_RX(x)					((uint8_t)(((uint8_t)(x))<<0))	//RX/TX control

/*EN_AA bit fields*/
#define NORDIC_ENAA_P5(x)					((uint8_t)(((uint8_t)(x))<<5))	//Enable auto acknowledgement data pipe 5
#define NORDIC_ENAA_P4(x)					((uint8_t)(((uint8_t)(x))<<4))	//Enable auto acknowledgement data pipe 4
#define NORDIC_ENAA_P3(x)					((uint8_t)(((uint8_t)(x))<<3))	//Enable auto acknowledgement data pipe 3
#define NORDIC_ENAA_P2(x)					((uint8_t)(((uint8_t)(x))<<2))	//Enable auto acknowledgement data pipe 2
#define NORDIC_ENAA_P1(x)					((uint8_t)(((uint8_t)(x))<<1))	//Enable auto acknowledgement data pipe 1
#define NORDIC_ENAA_P0(x)					((uint8_t)(((uint8_t)(x))<<0))	//Enable auto acknowledgement data pipe 0

/*EN_RXADDR bit fields*/
#define NORDIC_ERX_P5(x)					((uint8_t)(((uint8_t)(x))<<5))	//Enable data pipe 5
#define NORDIC_ERX_P4(x)					((uint8_t)(((uint8_t)(x))<<4))	//Enable data pipe 4
#define NORDIC_ERX_P3(x)					((uint8_t)(((uint8_t)(x))<<3))	//Enable data pipe 3
#define NORDIC_ERX_P2(x)					((uint8_t)(((uint8_t)(x))<<2))	//Enable data pipe 2
#define NORDIC_ERX_P1(x)					((uint8_t)(((uint8_t)(x))<<1))	//Enable data pipe 1
#define NORDIC_ERX_P0(x)					((uint8_t)(((uint8_t)(x))<<0))	//Enable data pipe 0

/*SETUP_AW bit fields*/
#define NORDIC_SETUP_AW_ILLEGAL_MASK		(00)	//illegal RX/TX address width
#define NORDIC_SETUP_AW_THREE_BYTES			(01)	//3 bytes RX/TX address width
#define NORDIC_SETUP_AW_FOUR_BYTES			(10)	//4 bytes RX/TX address width
#define NORDIC_SETUP_AW_FIVE_BYTES			(11)	//5 bytes RX/TX address width

/*SETUP_RETR bit widths*/
//Auto retransmit delay fields
#define NORDIC_ARD_250us					(0000)	//wait 250us
#define NORDIC_ARD_500us					(0001)	//wait 500us
#define NORDIC_ARD_750us					(0010)	//wait 750us
#define NORDIC_ARD_1000us					(0011)	//wait 1000us
#define NORDIC_ARD_1250us					(0100)	//wait 1250us
#define NORDIC_ARD_1500us					(0101)	//wait 1500us
#define NORDIC_ARD_1750us					(0110)	//wait 1750us
#define NORDIC_ARD_2000us					(0111)	//wait 2000us
#define NORDIC_ARD_2250us					(1000)	//wait 2250us
#define NORDIC_ARD_2500us					(1001)	//wait 2500us
#define NORDIC_ARD_2750us					(1010)	//wait 2750us
#define NORDIC_ARD_3000us					(1011)	//wait 3000us
#define NORDIC_ARD_3250us					(1100)	//wait 3250us
#define NORDIC_ARD_3500us					(1101)	//wait 3500us
#define NORDIC_ARD_3750us					(1110)	//wait 3750us
#define NORDIC_ARD_4000us					(1111)	//wait 4000us

//Auto Re-transmit Count bit fields
#define NORDIC_ARC_1						(0000)	//retransmit disabled
#define NORDIC_ARC_2						(0001)	//upto 1 retransmit on fail of AA
#define NORDIC_ARC_3						(0010)	//upto 2 retransmit on fail of AA
#define NORDIC_ARC_3						(0011)	//upto 3 retransmit on fail of AA
#define NORDIC_ARC_4						(0100)	//upto 4 retransmit on fail of AA
#define NORDIC_ARC_5						(0101)	//upto 5 retransmit on fail of AA
#define NORDIC_ARC_6						(0110)	//upto 6 retransmit on fail of AA
#define NORDIC_ARC_7						(0111)	//upto 7 retransmit on fail of AA
#define NORDIC_ARC_8						(1000)	//upto 8 retransmit on fail of AA
#define NORDIC_ARC_9						(1001)	//upto 9 retransmit on fail of AA
#define NORDIC_ARC_10						(1010)	//upto 10 retransmit on fail of AA
#define NORDIC_ARC_11						(1011)	//upto 11 retransmit on fail of AA
#define NORDIC_ARC_12						(1100)	//upto 12 retransmit on fail of AA
#define NORDIC_ARC_13						(1101)	//upto 13 retransmit on fail of AA
#define NORDIC_ARC_14						(1110)	//upto 14 retransmit on fail of AA
#define NORDIC_ARC_15						(1111)	//upto 15 retransmit on fail of AA

/*RF_SETUP bit fields */
#define NORDIC_PLL_LOCK_MASK				(0x10)	//Force PLL lock signal
#define NORDIC_RF_DR_1Mbps_MASK				(0x00)	//1Mbps air data rate
#define NORDIC_RF_DR_2Mbps_MASK				(0x08)	//2Mbps air data rate
#define NORDIC_RF_PWR_18dBm_MASK			(0x00)	//-18dBm RF output power in TX mode
#define NORDIC_RF_PWR_12dBm_MASK			(0x02)	//-12dBm RF output power in TX mode
#define NORDIC_RF_PWR_6dBm_MASK				(0x04)	//-6dBm RF output power in TX mode
#define NORDIC_RF_PWR_0dBm_MASK				(0x06)	//0dBm RF output power in TX mode
#define NORDIC_LNA_HCURR_MASK				(0x01)	//Setup LNA gain.

/*STATUS bit fields */
#define NORDIC_RX_DR_MASK					(0x40) 	//Data ready RX FIFO interrupt
#define NORDIC_TX_DS_MASK					(0x20)	//Data sent TX FIFO interrupt
#define NORDIC_MAX_RT_MASK					(0x10)	//Max number of TX retransmits interrupts (write 1 to clear bit)
//Data pipe number for the payload avaliable for reading from RX_FIFO
#define NORDIC_RX_P_NO_0_MASK				(000)	//Data pipe number 0
#define NORDIC_RX_P_NO_1_MASK				(001)	//Data pipe number 1
#define NORDIC_RX_P_NO_2_MASK				(010)	//Data pipe number 2
#define NORDIC_RX_P_NO_3_MASK				(011)	//Data pipe number 3
#define NORDIC_RX_P_NO_4_MASK				(100)	//Data pipe number 4
#define NORDIC_RX_P_NO_5_MASK				(101)	//Data pipe number 5
#define NORDIC_RX_P_NO_7_MASK				(111)	//RX FIFO empty

#define NORDIC_TX_FULL_FLAG_MASK			(0x01)	//TX FIFO status(1:full, 0:available locations in TX FIFO)

/*CD bit fields*/
#define NORDIC_CD_MASK						(0x01)	//Carrier detect

/*DYNPD bit fields*/
#define NORDIC_DPL_P5_MASK					(0x20)	//Enable dyn. payload length data pipe 5
#define NORDIC_DPL_P4_MASK					(0x10)	//Enable dyn. payload length data pipe 4
#define NORDIC_DPL_P3_MASK					(0x08)	//Enable dyn. payload length data pipe 3
#define NORDIC_DPL_P2_MASK					(0x04)	//Enable dyn. payload length data pipe 2
#define NORDIC_DPL_P1_MASK					(0x02)	//Enable dyn. payload length data pipe 1
#define NORDIC_DPL_P0_MASK					(0x01)	//Enable dyn. payload length data pipe 0

/*FEATURE bit fields*/
#define NORDIC_EN_DPL_MASK					(0x04)	//Enables dynamic payload length
#define NORDIC_EN_ACK_PAY_MASK				(0x02)	//Enables payload with ACK
#define NORDIC_EN_DYN_ACK_MASK				(0x01)	//Enables the W_TX_PAYLOAD_NOACK command


/* Register Instance Definitions*/

#define NORDIC_CONFIG						NORDIC_CONFIG_REG(NORDIC)
#define NORDIC_EN_AA						NORDIC_EN_AA_REG(NORDIC)
#define NORDIC_EN_RXADDR					NORDIC_EN_RXADDR_REG(NORDIC)
#define NORDIC_SETUP_AW						NORDIC_SETUP_AW_REG(NORDIC)
#define NORDIC_SETUP_RETR					NORDIC_SETUP_RETR_REG(NORDIC)
#define NORDIC_RF_CH						NORDIC_RF_CH_REG(NORDIC)
#define NORDIC_RF_SETUP						NORDIC_RF_SETUP_REG(NORDIC)
#define NORDIC_STATUS						NORDIC_STATUS_REG(NORDIC)
#define NORDIC_OBSERVE_TX					NORDIC_OBSERVE_TX_REG(NORDIC)
#define NORDIC_CD							NORDIC_CD_REG(NORDIC)
#define NORDIC_RX_ADDR_P0					NORDIC_RX_ADDR_P0_REG(NORDIC)
#define NORDIC_RX_ADDR_P1					NORDIC_RX_ADDR_P1_REG(NORDIC)
#define NORDIC_RX_ADDR_P2					NORDIC_RX_ADDR_P2_REG(NORDIC)
#define NORDIC_RX_ADDR_P3					NORDIC_RX_ADDR_P3_REG(NORDIC)
#define NORDIC_RX_ADDR_P4					NORDIC_RX_ADDR_P4_REG(NORDIC)
#define NORDIC_RX_ADDR_P5					NORDIC_RX_ADDR_P5_REG(NORDIC)
#define NORDIC_TX_ADDR						NORDIC_TX_ADDR_REG(NORDIC)
#define NORDIC_RX_PW_P0						NORDIC_RX_PW_P0_REG(NORDIC)
#define NORDIC_RX_PW_P1						NORDIC_RX_PW_P1_REG(NORDIC)
#define NORDIC_RX_PW_P2						NORDIC_RX_PW_P2_REG(NORDIC)
#define NORDIC_RX_PW_P3						NORDIC_RX_PW_P3_REG(NORDIC)
#define NORDIC_RX_PW_P4						NORDIC_RX_PW_P4_REG(NORDIC)
#define NORDIC_RX_PW_P5						NORDIC_RX_PW_P0_REG(NORDIC)
#define NORDIC_FIFO_STATUS					NORDIC_FIFO_STATUS_REG(NORDIC)
#define NORDIC_DYNPD						NORDIC_DYNPD_REG(NORDIC)
#define NORDIC_FEATURE						NORDIC_FEATURE_REG(NORDIC)


#endif /* INCLUDES_NRF24L01_H_ */
