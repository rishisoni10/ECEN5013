//	ftoa(n, res, afterpoint)
//	n          --> Input Number
//	res[]      --> Array where output string to be stored
//	afterpoint --> Number of digits to be considered after point.




// C program for implementation of ftoa()
#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include "data.h"

// reverses a string 'str' of length 'len'
void reverse(uint8_t *str, uint32_t len)
{
	uint32_t i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}



typedef union {
long	L;
float	F;
}	LF_t;

char *ftoa(float f)
{
	long mantissa, int_part, frac_part;
	short exp2;
	LF_t x;
	char *p;
	static char outbuf[15];

	if (f == 0.0)
	{
		outbuf[0] = '0';
		outbuf[1] = '.';
		outbuf[2] = '0';
		outbuf[3] = 0;
		return outbuf;
	}
	x.F = f;

	exp2 = (unsigned char)(x.L >> 23) - 127;
	mantissa = (x.L & 0xFFFFFF) | 0x800000;
	frac_part = 0;
	int_part = 0;

	if (exp2 >= 23)
		int_part = mantissa << (exp2 - 23);
	else if (exp2 >= 0)
	{
		int_part = mantissa >> (23 - exp2);
		frac_part = (mantissa << (exp2 + 1)) & 0xFFFFFF;
	}
	else /* if (exp2 < 0) */
		frac_part = (mantissa & 0xFFFFFF) >> -(exp2 + 1);

	p = outbuf;

	if (x.L < 0)
		*p++ = '-';

	if (int_part == 0)
		*p++ = '0';
	else
	{
		itoa(p, int_part, 10);
		while (*p)
			p++;
	}
	*p++ = '.';

	if (frac_part == 0)
		*p++ = '0';
	else
	{
		char m, max;
		max = sizeof (outbuf) - (p - outbuf) - 1;
		if (max > 7)
			max = 7;
		/* print BCD */
		for (m = 0; m < max; m++)
		{
			/* frac_part *= 10;	*/
			frac_part = (frac_part << 3) + (frac_part << 1);

			*p++ = (frac_part >> 24) + '0';
			frac_part &= 0xFFFFFF;
		}
		/* delete ending zeroes */
		for (--p; p[0] == '0' && p[-1] != '.'; --p)
			;
		++p;
	}
	*p = 0;

	return outbuf;
}


int8_t itoa(int8_t *str, int32_t data, int32_t base)
{
	int8_t* str1 = str;
	int isNeg = 0;
	if (data < 0)
	{
		isNeg = 1;
		data = -data;
	}

	if (data == 0)
	{
		*str++ = '\0';
		return 1;
	}

	int length = 0;
	while (data != 0)
	{
		int8_t reminder = data% base;
		data = data / base;
		if (reminder > 9)
		{
			*str++ = (reminder - 10) + 'a';
		}
		else
		{
			*str++ = reminder + '0';
		}
		length++;
	}
	if (isNeg)
	{
		*str++ = '-';
		length++;
	}
	*str++ = '\0'; //End of character

	int8_t* src = str1;

	int index = 0;
	uint8_t temp;
	while (index<length / 2)
	{
		temp = *(src + index);
		*(src + index) = *(src + length - index - 1);
		*(src + length - index - 1) = temp;
		index++;
	}
	if (index == (length/2))
		return 1;
	else
		return 0;
}




/*

char* my_itoa(char* str, uint32_t num, uint32_t base)
{
    int i = 0;
    int isNegative = 0;

    /* Handle 0 explicitely, otherwise empty string is printed for 0
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Process individual digits
    while (num > 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}*/
