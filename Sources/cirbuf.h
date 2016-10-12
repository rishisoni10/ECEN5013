/*
 * cirbuf.h
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_CIRBUF_H_
#define SOURCES_CIRBUF_H_

typedef struct {
uint8_t* buff; /*The buffer address*/
uint8_t* head; /*The buffer start address*/
uint8_t* tail; /*The buffer end address*/
uint32_t size; /*The total capacity of the buffer*/
uint8_t count; /*Total number of elements currently in buffer*/
} cirbuffer_t;


uint8_t Is_buffer_full(cirbuffer_t*);
uint8_t Is_buffer_Empty(cirbuffer_t*);

void    CirBuff_init(cirbuffer_t*,uint8_t ,uint8_t* );
uint8_t Circular_Push(cirbuffer_t*,uint8_t );
uint8_t Circular_Pop(cirbuffer_t*, uint8_t*);

//uint8_t *Allocate(cirbuffer_t *cptr,uint8_t size);
//uint8_t Destroy(cirbuffer_t *cptr);


#endif /* SOURCES_CIRBUF_H_ */
