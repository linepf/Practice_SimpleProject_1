/*
 * DHT11.h
 *
 *  Created on: Jul 6, 2025
 *      Author: JJH
 */

#ifndef DEV_DHT11_H_
#define DEV_DHT11_H_

#include "user_main.h"

//#define TIMER_DHT11		  		htim1	// 사용할 타이머 핸들러 입력

#define DHT11_PORT		GPIOA  			// 포트 입력 ex) GPIOB
#define DHT11_PIN     	GPIO_PIN_12   	// 포트 번호 입력 ex)GPIO_PIN_15

void DHT11_Start();
void Set_Pin_Output();
void Set_Pin_Input();
uint8_t DHT11_Check_Response();
uint8_t DHT11_Read_8bit ();
uint8_t DHT11_Read_hum();
float DHT11_Read_temp();
uint8_t DHT11_Read_tmepandhum();

struct DHT11_structure {
	float DHT11_temp;
	int	  DHT11_hum;
};

extern struct DHT11_structure DHT11;

#endif /* DEV_DHT11_H_ */
