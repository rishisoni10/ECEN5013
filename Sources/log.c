/*
 * log.c
 *
 *  Created on: Oct 7, 2016
 *      Author: vikhyat
 */

#include<stdio.h>
#include<stdint.h>

#include "main.h"

uint8_t* Concatenate(uint8_t* str1, uint32_t len1, uint8_t* str2, uint32_t len2)
{
	uint8_t* adr;
	adr = str1;
	while(len2--){
		*(adr+len1) = *str2++;
		adr++;
	}
	*adr = '\0';
	return(str1);
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
	/*
	uint8_t dest[20];
	uint8_t* string;
	uint8_t* datastr;
	string = dest;
	datastr = my_itoa(dest,param,10);
	string = Concatenate(data,len,datastr,data_len);
	LOG_0(string,(len+data_len));*/
	LOG_0(data,len);
	uint8_t dest[20];
	itoa(dest,param,10);
	LOG_0(dest,data_len);
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
	/*uint32_t data_len=0;
	uint8_t *dest,*tempptr,*string;
	uint8_t temp[20], temp1[20];
	string = temp;
	dest = temp1;
	dest = ftoa(param);
	tempptr = dest;
	while(*tempptr++ != '\0')
	{
		data_len++;
	}
	string = Concatenate(data,len,dest,data_len);
	LOG_0(string,(len+data_len));*/
	uint8_t size = 8;
	LOG_0(data,len);
	char *dest;
	char temp[20];
	dest = temp;
	dest = ftoa(param);
	LOG_0(dest,size);
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

