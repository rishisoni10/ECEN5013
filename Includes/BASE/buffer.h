/*
 * buffer.h
 *
 *  Created on: Oct 30, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_HSW_BUFFER_H_
#define INCLUDES_HSW_BUFFER_H_


typedef struct
{
     uint8_t *start;			//start of buffer
     uint8_t *head;
     uint8_t *tail;
     uint8_t *end;				//buffer end address
     uint16_t num_items;		//number of items currently in buffer
     uint16_t size;				//total size of buffer
}cir_buff_t;

cir_buff_t RXBUFF;

typedef enum cir_buff_ERROR {	//buffer error codes
	CBUF_FULL = 1,
	CBUF_EMPTY = 2,
	CBUF_ADD_PASS = 3,
	CBUF_DEL_PASS = 4
}cir_buff_error_t;

uint8_t buffer_full(cir_buff_t *cptr);				//Check for buffer full
uint8_t buffer_empty(cir_buff_t *cptr);				//Check for buffer empty
uint8_t init_cbuff(cir_buff_t *cptr,uint8_t size);	//initialise buffer
uint8_t add_cbuff(cir_buff_t *cptr,uint8_t data);	//Add data to buffer
uint8_t del_cbuff(cir_buff_t *cptr);				//Removing data from buffer
uint8_t Destroy(cir_buff_t *cptr);


#endif /* INCLUDES_HSW_BUFFER_H_ */
