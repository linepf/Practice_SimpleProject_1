/*
 * WS2812B.c
 *
 *  Created on: Jul 9, 2025
 *      Author: JJH
 */

#include "WS2812B.h"

struct neo_structure neo;


/*
* @brief	WS2812B 초기 세팅, PWM_DMA활성화
* @details	WS2812B로 보낼 배열의 데이터를 초기 세팅, BIT_OFFSET, 과 BIT_LOW를 미리 입력
* @param	cmd, flag
* @return	void
*/
void WS2812B_Init(){
	memset(&(neo.neo_data), 0, sizeof(neo.neo_data));
	uint8_t temp[BIT_OFFSET] = { 0 };
	memcpy(&neo.neo_data[0], temp, BIT_OFFSET);
	HAL_TIM_PWM_Start_DMA(&NEO_TIM, TIM_CHANNEL_1, (uint32_t*)neo.neo_data, (BIT_OFFSET + BIT_WIDTH * NEO_LED_CNT)*1);

}

/*
* @brief	WS2812B set함수
* @details	WS2812B로 보낼 배열의 데이터를 변환 r, g, b, 체널순번 을 받아서 배열의 데이터 변경
* @param	ch, red, green, blue
* @return	void
*/
void WS2812B_SetPixel(uint8_t ch, uint8_t red, uint8_t green, uint8_t blue){


	uint8_t r_bit[8];
	uint8_t g_bit[8];
	uint8_t b_bit[8];
	//uint8_t w_bit[8];

	for(int i=0; i<8; i++){

		if(red & (1<<7)) r_bit[i] = BIT_HIGH;	//r의 최상위 비트가 1이면 참
		else r_bit[i] = BIT_LOW;
		red <<= 1;								//red = red << 1;

		if (green & (1 << 7)) g_bit[i] = BIT_HIGH;
		else g_bit[i] = BIT_LOW;
		green <<= 1;

		if (blue & (1 << 7)) b_bit[i] = BIT_HIGH;
		else b_bit[i] = BIT_LOW;
		blue <<= 1;

		//w_bit[i] = BIT_HIGH;
	}

	  memcpy(&neo.neo_data[BIT_OFFSET + ch*BIT_WIDTH + 8*0], g_bit, 8*1);
	  memcpy(&neo.neo_data[BIT_OFFSET + ch*BIT_WIDTH + 8*1], r_bit, 8*1);
	  memcpy(&neo.neo_data[BIT_OFFSET + ch*BIT_WIDTH + 8*2], b_bit, 8*1);
	 // memcpy(&neo.neo_data[BIT_OFFSET + ch*BIT_WIDTH + 8*3], w_bit, 8*1);
}

/*
* @brief	WS2812B off함수
* @details	WS2812B를 전부 끄는 함수, 초기에 WS2812B_Init함수와 같이 사용 권장(초기 오작동 방지)
* 			함수 호출후 딜레이 필요 픽셀 개수에 따라 다르지만 대략 500ms가량 필요
* @param	void
* @return	void
*/
void WS2812B_OFFPixel(){
	memset(&(neo.neo_data), BIT_LOW, sizeof(neo.neo_data));
	uint8_t temp[BIT_OFFSET] = { 0 };
	memcpy(&neo.neo_data[0], temp, BIT_OFFSET);
}
