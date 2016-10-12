/*
 * memory.c
 *
 *  Created on: 12-Oct-2016
 *      Author: Vikhyat
 */

/****************************************************/
/*Module name: memory.c			    */
/*Author name : Vikhyat Goyal			    */
/* Date : 09/15/16				    */
/****************************************************/
#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define MAX_MEMORY_ADDRESS (100)


/*******************************************************************/
/*descrition: function used to copy data from one memory           */
/*            to other.					           */
/*parameter: a pointer to source, a pointer to destination         */
/*	     and length of data to be moved      	           */
/*return:    0 : if the memory address specified are NULL          */
/*  		 if there is an overlap between the memory blocks. */
/*	     1 : otherwise					   */
/*******************************************************************/

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{
int8_t result = 1;

/*check if the any of the pointer is a NULL pointer.*/
 if((src == NULL)||(dst == NULL)) {
    result = 0;
   }
/*check if there is an overall between the memory blocks.*/
 /*if(((src + length*(sizeof(uint8_t)) > dst)
    ||(dst + length*(sizeof(uint8_t)) > MAX_MEMORY_ADDRESS))) {
    result = 0;
   }
 else*/ {
    while(length) {
          *dst = *src;
           src++;
           dst++;
	   length--;
         }
   }
return(result);
}


/*******************************************************************/
/*descrition: function used to clear a specific length of memory   */
/*parameter: a pointer to source  			           */
/*	     and length of data to be moved      	           */
/*return:    0 : if the memory address specified are NULL          */
/*	     1 : otherwise					   */
/*******************************************************************/
int8_t my_memzero(uint8_t *src, uint32_t length)
{
int8_t result = 1;

/*check if the any of the pointer is a NULL pointer.*/
 if(src == NULL) {
    result = 0;
   }
/*check if there is enough space in memory for the length*/
 /*if(src + length*(sizeof(uint8_t)) > MAX_MEMORY_ADDRESS) {
    length = MAX_MEMORY_ADDRESS;
    }*/
 while(length) {
    *src++ = 0;
     length--;
    }
return(result);
}

/*******************************************************************/
/*descrition: function reverses the meomory elements for the       */
/*	       given length.					   */
/*parameter: a pointer to source  			           */
/*	     and length of data to be reversed      	           */
/*return:    0 : if the memory address specified are NULL          */
/*	     1 : otherwise					   */
/*******************************************************************/
int8_t my_reverse(uint8_t *src, uint32_t length)
{
int8_t result = 1;
uint8_t temp;
int templen;

 templen=length;

/*check if the any of the pointer is a NULL pointer.*/
 if((src == NULL)||(length == 0)) {
    result = 0;
   }
/*check if there is enough space in memory for the reverse*/
 /*if(src + length*(sizeof(uint8_t)) > MAX_MEMORY_ADDRESS) {
    length = MAX_MEMORY_ADDRESS;
    }*/
 while((templen/2)||(templen ==2))
         {
          temp = *src;
          *src = *(src +(sizeof(uint8_t))*(templen-1));
          *(src + (sizeof(uint8_t))*(templen -1)) = temp;
          src++;
          templen =templen-2;
         }
return(result);
}




