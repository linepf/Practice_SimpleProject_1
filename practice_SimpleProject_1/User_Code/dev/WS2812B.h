/*
 * WS2812B.h
 *
 *  Created on: Jul 9, 2025
 *      Author: JJH
 */

#ifndef DEV_WS2812B_H_
#define DEV_WS2812B_H_

#include "user_main.h"

#define NEO_LED_CNT		5		//네오픽셀 개수 최소 1개부터, 번호는 0번부터이다
#define	BIT_WIDTH		8*3		//네오픽셀 데이터(r,g,b개 수) 수 (bit기준)
#define	BIT_OFFSET		70		//시작 신호 값(레지스터에 들어갈 값)
#define BIT_LOW			28		//LOW 신호 값(레지스터에 들어갈 값)
#define BIT_HIGH		56		//HIGH 신호 값(레지스터에 들어갈 값)
#define NEO_TIM			htim2	// 사용할 타이머 핸들러 입력

void WS2812B_Init();
void WS2812B_SetPixel(uint8_t ch, uint8_t red, uint8_t green, uint8_t blue);
void WS2812B_OFFPixel();

struct neo_structure {
	uint8_t neo_data[BIT_OFFSET + BIT_WIDTH * NEO_LED_CNT];
};

extern struct neo_structure neo;

//uint8_t neo_data[BIT_OFFSET + BIT_WIDTH * NEO_LED_CNT];


#endif /* DEV_WS2812B_H_ */
