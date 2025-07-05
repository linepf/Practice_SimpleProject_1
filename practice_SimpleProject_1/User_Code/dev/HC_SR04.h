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

void delay_us(uint16_t time);
void HC_SR04_Read(void);
void HC_SR04_Init(TIM_HandleTypeDef* htim, int CHANNEL);

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
