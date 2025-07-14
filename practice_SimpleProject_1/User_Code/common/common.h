/*
 * common.h
 *
 *  Created on: Jul 6, 2025
 *      Author: JJH
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include "user_main.h"

#define USE_DELAY_US_TIMER     1 		//delay_us 사용 유무 1사용
#define DELAY_US_TIMER_HANDLE  htim1  	//delay_us 헨들러 선택 htim1~4

void delay_us(uint16_t time);
void delay_us_Init();

#endif /* COMMON_COMMON_H_ */
