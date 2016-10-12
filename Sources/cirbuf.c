/*
 * cirbuf.c
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */


#include "main.h"
#include "stdlib.h"

/*******************************************************************/
/*descrition: This function adds a new data to the given circular  */
/*	      buffer						   */
/*parameter: data to be added, the buffer address  	           */
/*return:    0 : if the buffer is full and a wrap fill occurs	   */
/*	     1 : otherwise					   */
/*******************************************************************/
uint8_t Circular_Push(cirbuffer_t *c,uint8_t data)
{
	uint8_t* adr;
	adr = c->head + 1;
	if(adr >= c->buff + c->size) {
	adr = c->buff;
	}
	if(Is_buffer_full(c)) {
	return(0);
	}
	*c->head = data;
	c->head = adr;
	c->count++;
	return(1);
}

/*******************************************************************/
/*descrition: This function removes the oldest data from the given */
/*	      circular buffer					             */
/*parameter: the buffer address and pointer to location where the  */
/*           data should be kept.				   		 */
/*return:    0 : if the buffer is empty.			   		 */
/*	     1 : otherwise					   		 */
/*******************************************************************/
uint8_t Circular_Pop(cirbuffer_t *c, uint8_t *data)
{
	uint8_t* adr;
	if(c->count == 0) {
	return(0);
	}
	else {
	*data = *(c->tail);
	*(c->tail) = 0;
	adr = c->tail + 1;
	if(adr >= c->buff + c->size) {
	adr = c->buff;
	}
	c->tail = adr;
	c->count--;
	}
	return(1);
}


/*******************************************************************/
/*descrition: This function tells if the circular buffer is empty  */
/*parameter: the buffer address 		 	           		 */
/*return:    1 : if the buffer is empty				   	 */
/*	     0 : otherwise					   		 */
/*******************************************************************/
uint8_t Is_buffer_Empty(cirbuffer_t *c)
{
	return(c->count == 0);
}

/*******************************************************************/
/*descrition: This function tells if the circular buffer is full   */
/*parameter: the buffer address 		 	           		 */
/*return:    1 : if the buffer is full				   	 */
/*	     0 : otherwise					    		 */
/*******************************************************************/
uint8_t Is_buffer_full(cirbuffer_t *c)
{
	return(c->count == c->size);
}


/*---------------------------------------------------------------------------
 *uint8_t CirBuff_init(cirbuffer_t *cptr,uint8_t size)
 *This function is can be used to initialise circular buffer of size "size"
 ---------------------------------------------------------------------------*/
void CirBuff_init(cirbuffer_t *c,uint8_t size,uint8_t* buff)
{
	c->buff = malloc(sizeof(int8_t) * size);
    c->size = size;							 //total size of buffer
    c->head = c->buff;					 //initially head and tail are at buff
    c->tail = c->buff;
    c->count = 0;			   			 //current number of items in buffer
}

/*---------------------------------------------------------------------------
 *uint8_t Destroy(cirbuffer_t *cptr)
 *This function destroys or frees up the heap memory assigned to the buffer
 ---------------------------------------------------------------------------*/
uint8_t Destroy(cirbuffer_t *c)
{
	free(c->buff);
	return 1;
}






