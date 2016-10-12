/*
 * memory.h
 *
 *  Created on: 12-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_MEMORY_H_
#define SOURCES_MEMORY_H_


/*******************************************************************/
/*descrition: function used to copy data from one memory           */
/*            to other.					           */
/*parameter: a pointer to source, a pointer to destination         */
/*	     and length of data to be moved      	           */
/*return:    0 : if the memory address specified are NULL          */
/*  		 if there is an overlap between the memory blocks. */
/*	     1 : otherwise					   */
/*******************************************************************/

int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);


/*******************************************************************/
/*descrition: function used to clear a specific length of memory   */
/*parameter: a pointer to source  			           */
/*	     and length of data to be moved      	           */
/*return:    0 : if the memory address specified are NULL          */
/*	     1 : otherwise					   */
/*******************************************************************/
int8_t my_memzero(uint8_t * src, uint32_t length);

/*******************************************************************/
/*descrition: function reverses the meomory elements for the       */
/*	       given length.					   */
/*parameter: a pointer to source  			           */
/*	     and length of data to be reversed      	           */
/*return:    0 : if the memory address specified are NULL          */
/*	     1 : otherwise					   */
/*******************************************************************/
int8_t my_reverse(uint8_t * src, uint32_t length);


#endif /* SOURCES_MEMORY_H_ */
