/*
 * com.h
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_COM_H_
#define SOURCES_COM_H_

 uint8_t COM_getChar_withbuffer(void);
 void COM_PrintChar_withbuffer(uint8_t* data);
 void communicate(void);
 uint8_t User_Command(uint8_t* );
 uint8_t COM_get_first(void);
 void COM_Create_Tx(cirbuffer_t *cptr,uint8_t size);
 void COM_Create_Rx(cirbuffer_t *cptr,uint8_t size);

 cirbuffer_t RXBUFF,TXBUFF;
 uint8_t Rx[50],Tx[50];

#endif /* SOURCES_COM_H_ */

