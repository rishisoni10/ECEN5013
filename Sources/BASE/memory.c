/*
 * memory.c
 *
 *  Created on: Nov 4, 2016
 *      Author: vikhyat
 */

#include "main.h"
#include "stdio.h"

int8_t my_memmove(void * s, void * d, uint32_t length)	//optimised for 32bits and then 8bits
{
	int8_t ret = 1;

	uint32_t len = length;
	uint32_t* src_l = (uint32_t*)s;
	uint32_t* dst_l = (uint32_t*)d;

	if (src_l != NULL && dst_l != NULL)
	{
		if(len >=4)
		{
			while (len >= 4)
			{
				*dst_l++ = *src_l++;
				len-=4;
			}
		}
		else
		{
			uint8_t* src_c = (uint8_t*)s;
			uint8_t* dst_c = (uint8_t*)d;

			while(len < 4)
			{
				*dst_c++ = *src_c++;
				len--;
			}
		}
	}
	else
	{
		LOG_0("\r\nNot moved\n");
		ret = 0;
	}
	return ret;
}



int8_t my_memzero(void * s, uint32_t length)	//optimised for 32bits and then 8bits
{
	int8_t ret = 1;
	uint32_t* src_l = (uint32_t*)s;
	if (src_l != NULL && length > 0)
	{
		while (length >= 4)
		{
			length-=4;
			*src_l++ = 0;
		}

		if(length < 4)
		{
			uint8_t* src_c = (uint8_t*)s;
			while (length < 4)
			{
				length--;
				*src_c++ = 0;
			}
		}
	}
	else {
		ret = 0;
	}
	return ret;
}
