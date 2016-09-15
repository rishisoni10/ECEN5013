#include "hw1.h"

char reverse_string(char * str, int length)
{
	
	char * last;
	last = str + (length - 1);
	char temp;

	while(last>str)
	{
		temp = *last;
		*last = *str;
		*str = temp;

		str++;
		last--;
	}
}