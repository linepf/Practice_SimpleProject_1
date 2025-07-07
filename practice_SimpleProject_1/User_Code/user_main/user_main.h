/*
 * user_main.h
 *
 *  Created on: May 19, 2025
 *      Author: linep
 */

#ifndef USER_MAIN_USER_MAIN_H_
#define USER_MAIN_USER_MAIN_H_

#include "stdint.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "def.h"
#include "common.h"
#include "LCD_I2C_16x2.h"
#include "HC_SR04.h"
#include "UART.h"
#include "DHT11.h"


struct adc1_structure {
	uint32_t data_buff[4];
	int adcflag;
};



void user_main();

extern struct adc1_structure adc1;


extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;


#endif /* USER_MAIN_USER_MAIN_H_ */
