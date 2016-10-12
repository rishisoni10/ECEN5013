/*
 * log.h
 *
 *  Created on: Oct 7, 2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_LOG_H_
#define SOURCES_LOG_H_

void LOG_0(uint8_t * data, uint8_t len);
void LOG_1(uint8_t * data, uint8_t len, uint32_t param, uint8_t data_type_size);
void LOG_2(uint8_t * data, uint8_t len, float param);
void LOG_3(uint8_t *data, uint32_t len);
void LOG_4(uint8_t *datastring);

#endif /* SOURCES_LOG_H_ */
