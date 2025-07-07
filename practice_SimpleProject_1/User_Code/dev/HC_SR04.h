/*
 * HC_SR04.h
 *
 *  Created on: Jul 4, 2025
 *      Author: JJH
 *
 *      HC_SR04는 초음파 센서이다
 *
 */

#ifndef DEV_HC_SR04_H_
#define DEV_HC_SR04_H_

#include "user_main.h"

#define TIMER_HC_SR04	  	htim1	// 사용할 타이머 핸들러 입력
#define CHALLEL_NUMBER     	1	//사용할 타이머의 체널 번호입력

#define TRIGGER_PORT		GPIOB  			// 트리터 포트 입력 ex) GPIOB
#define TRIGGERPORT_PIN     GPIO_PIN_15   	// 트리거 포트 번호 입력 ex)GPIO_PIN_15

#define Trig(x) (HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGERPORT_PIN, x))


int HC_SR04_Read(void);
void HC_SR04_Init();

struct HC_SR04_structure{
	uint32_t IC_Val1;
	uint32_t IC_Val2;
	uint32_t Difference;
	uint8_t Is_First_Captured;
	uint8_t Distance;
	TIM_HandleTypeDef* HC_SR04_timer;
};



extern struct HC_SR04_structure HC_SR04;

#endif /* DEV_HC_SR04_H_ */
