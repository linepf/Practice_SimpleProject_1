/*
 * DS18B20 .h
 *
 *  Created on: Jul 14, 2025
 *      Author: JJH
 *
 *      이 예제는 DS18B20가 신호선에 하나만 있을때 사용해야 하는 예제이다!!!
 */

#ifndef DEV_DS18B20_H_
#define DEV_DS18B20_H_

#include "user_main.h"

#define DS18B20_PORT	GPIOA	  			// 포트 입력 ex) GPIOB
#define DS18B20_PIN     GPIO_PIN_12	   	// 포트 번호 입력 ex)GPIO_PIN_15


void DS18B20_Pin_Output(void);
void DS18B20_Pin_Input(void);
uint8_t DS18B20_Reset(void);
void DS18B20_WriteBit(uint8_t bit);
void DS18B20_WriteByte(uint8_t byte);
float DS18B20_GetTemperature(void);

#endif /* DEV_DS18B20_H_ */
