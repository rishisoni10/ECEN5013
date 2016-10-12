/*
 * log.c
 *
 *  Created on: Oct 7, 2016
 *      Author: vikhyat
 */

#include<stdio.h>
#include<stdint.h>

#include "main.h"

uint8_t* Concatenate(uint8_t* adr, uint8_t* str1, uint32_t len1, uint8_t* str2, uint32_t len2)
{
	uint8_t* result;
	result = adr;
	while(len1--){
		*adr = *str1++;
		adr++;
	}
	while(len2--){
		*adr = *str2++;
		adr++;
	}
	return(result);
}

void LOG_0(uint8_t * data, uint8_t len)
{
#ifdef DEBUG
#ifdef FRDM
	while(len--)
	{
		while(!((UART0_S1&UART_S1_TDRE_MASK)|(UART0_S1&UART_S1_TC_MASK)));
	    UART0_D = *data++;
	}
#endif
#ifdef BBB
	for (int i=0;i<len;i++)
	{
		printf("\n%p",*data++);
	}
#endif
#endif

}

void LOG_1(uint8_t * data, uint8_t len, uint32_t  param, uint8_t data_len)
{
#ifdef DEBUG
#ifdef FRDM
	uint8_t deststr[100];
	uint8_t dest[20];
	uint8_t* datastr;
	datastr = deststr;
	itoa(dest,param,10);
	datastr = Concatenate(datastr,data,len,dest,data_len);
	LOG_0(datastr,(len+data_len));
#endif
#ifdef BBB
	for (int i=0;i<len;i++)
	{
		printf("\n%p",*data);
		*data++;
	}
	printf(":");
	printf("%d",param);
#endif
#endif
}

void LOG_2(uint8_t * data, uint8_t len, float param)
{
#ifdef DEBUG
#ifdef FRDM

	uint8_t deststr[100],temp[20];
	uint8_t* dest;
	uint8_t* datastr;
	datastr = deststr;
	dest = temp;
	dest = ftoa(param);
	datastr = Concatenate(datastr,data,len,dest,8);
	LOG_0(datastr,(len+8));
#endif
#ifdef BBB
	for (int i=0;i<len;i++)
	{
		printf("\n%p",*data);
		*data++;
	}
	printf(":");
	printf("%f",param);
#endif
#endif
}

void LOG_4(uint8_t *datastring)
{
	UART_print_string_noBuffer(datastring);
}

