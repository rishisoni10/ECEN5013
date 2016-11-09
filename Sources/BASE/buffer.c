/*
 * buffer.c
 *
 *  Created on: Oct 30, 2016
 *      Author: vikhyat
 */
#include "main.h"
#include "malloc.h"
/*---------------------------------------------------------------------------
 *uint8_t init_cbuff(cir_buff_t *cptr,uint8_t size)
 *This function is can be used to initialise circular buffer of size "size"
 ---------------------------------------------------------------------------*/
uint8_t init_cbuff(cir_buff_t *cptr,uint8_t size)
{
	cptr->start = malloc(sizeof(uint8_t)* size);
    cptr->size = size;							 //total size of buffer
    cptr->end=cptr->start + size;				 //calculate address of end of buffer
    cptr->head = cptr->start;					 //initially head and tail are at start
    cptr->tail = cptr->start;
    cptr->num_items = 0;			   			 //current number of items in buffer
}

/*---------------------------------------------------------------------------
 *uint8_t Destroy(cir_buff_t *cptr)
 *This function destroys or frees up the heap memory assigned to the buffer
 ---------------------------------------------------------------------------*/
uint8_t Destroy(cir_buff_t *cptr)
{
	free(cptr->start);
	return 1;
}
/*---------------------------------------------------------------------------
 *uint8_t buffer_full(cir_buff_t *cptr)
 *This functions returns 1 if the buffer is full
 *						 0 if the buffer is not full
 *The head is incremented on every data addition and tail is incremented
 *on every data read.After the buffer is full,the head wraps around to the
 *start of the buffer.
 ---------------------------------------------------------------------------*/
uint8_t buffer_full(cir_buff_t *cptr)
{
	if((cptr->head == cptr->tail) && (cptr->num_items != 0))
		return 1;
    else
    	return 0;
}
/*---------------------------------------------------------------------------
 * uint8_t buffer_empty(cir_buff_t *cptr)
 * This functions returns 1 if the buffer is empty
 *						  0 if the buffer is not empty
 *The head is incremented on every data addition and tail is incremented
 *on every data read.After all the items in the buffer is read,the tail
 *wraps around to the start of the buffer.
 ---------------------------------------------------------------------------*/
uint8_t buffer_empty(cir_buff_t *cptr)
{
	if(cptr->num_items == 0)
		return 1;
    else
    	return 0;
}
/*---------------------------------------------------------------------------
 *uint8_t add_cbuff(cir_buff_t *cptr,uint8_t data)
 *This function lets you add data to the buffer, it also checks if the
 *buffer is full before addition. After data is added at head location,
 *the head is incremented along with the item count.
 *The function also includes wrapping the head pointer to the start of
 *the buffer when it reaches an address after the end of buffer
 ---------------------------------------------------------------------------*/
uint8_t add_cbuff(cir_buff_t *cptr,uint8_t data)
{
	if (cptr->head > cptr->end)  {			//wrap around to start of buffer
		cptr->head = cptr->start;
	}

	if(buffer_full(cptr))					//check if buffer is full
		{
	        return 0;
		}
    *cptr->head = data;						//write data at head
    cptr->num_items++;						//increment item count
    cptr->head++;							//move head to next location
    return 1;								//return on success
}
/*---------------------------------------------------------------------------
 *uint8_t del_cbuff(cir_buff_t *cptr)
 *This function lets you read data from the buffer, it also checks if the
 *buffer is empty before removal/read. After data is read at tail location,
 *the tail is incremented and the item count is decremented.
 *The function also includes wrapping the tail pointer to the start of
 *the buffer when it reaches an address after the end of buffer
 ---------------------------------------------------------------------------*/
uint8_t del_cbuff(cir_buff_t *cptr)
{
	uint8_t data;
    if (cptr->tail > cptr->end){  			//wrap tail ptr to start of buffer
    	cptr->tail = cptr->start;
    }

	if(buffer_empty(cptr))					//check if buffer empty
	{
        return 0;
	}

    data = *cptr->tail;						//read at tail
    (cptr->num_items)--;						//decrement item count
    (cptr->tail)++;							//increment tail after read
    return data;							//return data on success
}




