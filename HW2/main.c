#include <stdio.h>
#include <string.h>
#include "hw1.h"

int main()
{
  	printf("Hello World\n");
  	int length;
  	char str[256];

  	
	
	printf("Enter the string to be reversed: \n");
	fgets(str, sizeof(str), stdin);

	length = strlen(str);
	reverse_string(str, length);

	printf("The reversed string is: %s\n", str);
  	return 0;
  }
