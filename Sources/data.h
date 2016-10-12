#ifndef _FTOA_H
#define _FTOA_H

void reverse(uint8_t *str, uint32_t len);

int8_t itoa(int8_t *str, int32_t data, int32_t base);

char* ftoa(float f);

char* my_itoa(char* str, uint32_t num, uint32_t base);



#endif
