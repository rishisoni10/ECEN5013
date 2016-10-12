/*
 * profile.h
 *
 *  Created on: 12-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_PROFILE_H_
#define SOURCES_PROFILE_H_

#include <stdint.h>

#define DATA_LEN_MAX    5000

void start_profiler(void);
void stop_profiler(void);

extern volatile uint32_t count ;


#endif /* SOURCES_PROFILE_H_ */
