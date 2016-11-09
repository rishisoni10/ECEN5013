/*
 * NRFL01.h
 *
 *  Created on: 08-Nov-2016
 *      Author: Vikhyat
 */

#ifndef _NRF24L01_H_
#define _NRF24L01_H_

// SPI Commands
#define NRF_COMMAND_R_REGISTER                        0x00
#define NRF_COMMAND_W_REGISTER                        0x20
#define NRF_COMMAND_R_RX_PAYLOAD                      0x61
#define NRF_COMMAND_W_TX_PAYLOAD                      0xa0
#define NRF_COMMAND_FLUSH_TX                          0xe1
#define NRF_COMMAND_FLUSH_RX                          0xe2
#define NRF_COMMAND_REUSE_TX_PL                       0xe3
#define NRF_COMMAND_R_RX_PL_WID                       0x60
#define NRF_COMMAND_W_ACK_PAYLOAD(pipe)               (0xa8|(pipe&0x7))
#define NRF_COMMAND_W_TX_PAYLOAD_NOACK                0xb0
#define NRF_COMMAND_NOP                               0xff

// Registers
#define NRF_REGISTER_MASK                             0x1f
#define NRF_REG_00_CONFIG                             0x00
#define NRF_REG_01_EN_AA                              0x01
#define NRF_REG_02_EN_RXADDR                          0x02
#define NRF_REG_03_SETUP_AW                           0x03
#define NRF_REG_04_SETUP_RETR                         0x04
#define NRF_REG_05_RF_CH                              0x05
#define NRF_REG_06_RF_SETUP                           0x06
#define NRF_REG_07_STATUS                             0x07
#define NRF_REG_08_OBSERVE_TX                         0x08
#define NRF_REG_09_RPD                                0x09
#define NRF_REG_0A_RX_ADDR_P0                         0x0a
#define NRF_REG_0B_RX_ADDR_P1                         0x0b
#define NRF_REG_0C_RX_ADDR_P2                         0x0c
#define NRF_REG_0D_RX_ADDR_P3                         0x0d
#define NRF_REG_0E_RX_ADDR_P4                         0x0e
#define NRF_REG_0F_RX_ADDR_P5                         0x0f
#define NRF_REG_10_TX_ADDR                            0x10
#define NRF_REG_11_RX_PW_P0                           0x11
#define NRF_REG_12_RX_PW_P1                           0x12
#define NRF_REG_13_RX_PW_P2                           0x13
#define NRF_REG_14_RX_PW_P3                           0x14
#define NRF_REG_15_RX_PW_P4                           0x15
#define NRF_REG_16_RX_PW_P5                           0x16
#define NRF_REG_17_FIFO_STATUS                        0x17
#define NRF_REG_1C_DYNPD                              0x1c
#define NRF_REG_1D_FEATURE                            0x1d

// Mask and offset values for CONFIG register
#define NRF_MASK_RX_DR                                0x40
#define NRF_RX_DR_OFFSET							  (6)
#define NRF_MASK_TX_DS                                0x20
#define NRF_TX_DS_OFFSET							  (5)
#define NRF_MASK_MAX_RT                               0x10
#define NRF_MAX_RT_OFFSET							  (4)
#define NRF_EN_CRC                                    0x08
#define NRF_EN_CRC_OFFSET							  (3)
#define NRF_CRCO                                      0x04
#define NRF_CRCO_OFFSET								  (2)
#define NRF_PWR_UP                                    0x02
#define NRF_PWR_UP_OFFSET							  (1)
#define NRF_PRIM_RX                                   0x01
#define NRF_PRIM_RX_OFFSET							  (0)

// Mask and offset values for Enhanced shock burst register
#define NRF_MASK_ENAA_P5                              0x20
#define NRF_ENAA_P5_OFFSET							  (5)
#define NRF_MASK_ENAA_P54                             0x10
#define NRF_ENAA_P4_OFFSET							  (4)
#define NRF_MASK_ENAA_P3                              0x08
#define NRF_ENAA_P3_OFFSET							  (3)
#define NRF_MASK_ENAA_P2                              0x04
#define NRF_ENAA_P2_OFFSET							  (2)
#define NRF_MASK_ENAA_P1                              0x02
#define NRF_ENAA_P1_OFFSET							  (1)
#define NRF_MASK_ENAA_P0                              0x01
#define NRF_ENAA_P0_OFFSET							  (0)

// Mask and offset values for Enabled RX Addresses register
#define NRF_MASK_ERX_P5                              0x20
#define NRF_ERX_P5_OFFSET							  (5)
#define NRF_MASK_ERX_P4                             0x10
#define NRF_ERX_P4_OFFSET							  (4)
#define NRF_MASK_ERX_P3                              0x08
#define NRF_ERX_P3_OFFSET							  (3)
#define NRF_MASK_ERX_P2                              0x04
#define NRF_ERX_P2_OFFSET							  (2)
#define NRF_MASK_ERX_P1                              0x02
#define NRF_ERX_P1_OFFSET							  (1)
#define NRF_MASK_ERX_P0                              0x01
#define NRF_ERX_P0_OFFSET							  (0)

// Mask and offset values for Address Widths register
#define NRF_MASK_SETUP_AW                             0x03
#define NRF_SETUP_AW_OFFSET							  (1)

// Mask and offset values for Automatic Retransmission register
#define NRF_MASK_SETUP_RETR_ARD                       0xF0
#define NRF_SETUP_RETR_ARD_OFFSET					  (7)
#define NRF_MASK_SETUP_RETR_ARC                       0x0F
#define NRF_SETUP_RETR_ARC_OFFSET					  (0)

// Mask and offset values for RF Channel register
#define NRF_MASK_RF_CH			                      0xEF
#define NRF_RF_CH_OFFSET	      				      (6)

// Mask and offset values for RF Setup Register
#define NRF_MASK_PLL_LOCK		                      0x08
#define NRF_PLL_LOCK_OFFSET	      				      (3)
#define NRF_MASK_RF_DR			                      0x04
#define NRF_RF_DR_OFFSET	      				      (2)
#define NRF_MASK_RF_PWR			                      0x03
#define NRF_RF_PWR_OFFSET	      				      (1)
#define NRF_MASK_LNA_HCURR		                      0x01
#define NRF_LNA_HCURR_OFFSET	   				      (0)

// Mask and offset values for RF Setup Register
#define NRF_MASK_PLL_LOCK		                      0x08
#define NRF_PLL_LOCK_OFFSET	      				      (3)
#define NRF_MASK_RF_DR			                      0x04
#define NRF_RF_DR_OFFSET	      				      (2)
#define NRF_MASK_RF_PWR			                      0x03
#define NRF_RF_PWR_OFFSET	      				      (1)
#define NRF_MASK_LNA_HCURR		                      0x01
#define NRF_LNA_HCURR_OFFSET	   				      (0)


#endif /* INCLUDES_NRF24L01_H_ */
