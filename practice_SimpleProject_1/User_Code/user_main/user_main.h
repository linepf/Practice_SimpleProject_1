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



struct adc1_structure {
	uint32_t data_buff[4];
	int adcflag;
};

struct uart1_structure {
	uint8_t RxBuffer[0xff];
	uint8_t enter;
};


void user_main();


extern struct uart1_structure uart1;
extern struct adc1_structure adc1;


extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;




#endif /* USER_MAIN_USER_MAIN_H_ */
