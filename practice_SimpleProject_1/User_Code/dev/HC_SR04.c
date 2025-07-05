/*
 * HC_SR04.c
 *
 *  Created on: Jul 4, 2025
 *      Author: JJH
 */

#include "HC_SR04.h"

struct HC_SR04_structure HC_SR04;


/*
* @brief	HC_SR04 모듈 초기화 함수
* @details	타이머, 체널선택 및 연산에 필요한 변수값 초기화
* @param	사용할 타이머 주소 주소, 사용할 체널 1~4까지 정수로 입력
* @return	viod
*/
void HC_SR04_Init(TIM_HandleTypeDef* htim, int CHANNEL){
	HC_SR04.IC_Val1 = 0;
	HC_SR04.IC_Val2 = 0;
	HC_SR04.Difference = 0;
	HC_SR04.Is_First_Captured = 0;
	HC_SR04.Distance = 0;
	HC_SR04.HC_SR04_timer = htim;

	uint32_t temp = 0;

	switch(CHANNEL){
	case 1:
		temp = TIM_CHANNEL_1;
	case 2:
		temp = TIM_CHANNEL_2;
	case 3:
		temp = TIM_CHANNEL_3;
	case 4:
		temp = TIM_CHANNEL_4;
	}

	HAL_TIM_IC_Start_IT(HC_SR04.HC_SR04_timer, temp);
}

/*
* @brief	us단위의 딜레이함수
* @details	HC_SR04 모듈의 트리거를 위해서 사용
* @param	딜레이할 정수값 입력 ex) 10이면 10us딜레이
* @return	viod
*/
void delay_us(uint16_t time){
	__HAL_TIM_SET_COUNTER(HC_SR04.HC_SR04_timer, 0);
	while (__HAL_TIM_GET_COUNTER (HC_SR04.HC_SR04_timer) < time);
}

/*
* @brief	HC_SR04 모듈의 거리값읽는 함수
* @details	HC_SR04 모듈에 트리거를 입력후 인터럽트를 활성화 시켜 거리를 연산
* 			초음파 모듈 측정주기는 60ms이상을 권장한다
* @param	void
* @return	void
*/
void HC_SR04_Read(void){
	Trig(1);
	delay_us(10);
	Trig(0);
	__HAL_TIM_ENABLE_IT(HC_SR04.HC_SR04_timer, TIM_IT_CC1);
}

/*
* @brief	입력 캡처 콜백함수
* @details	입력 캡처 인터럽트가 발생했을 때 자동으로 호출되는 콜백 함수
* @param	htim
* @return	void
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if (HC_SR04.Is_First_Captured==0) // if the first value is not captured
		{
			HC_SR04.IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			HC_SR04.Is_First_Captured = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (HC_SR04.Is_First_Captured==1)   // if the first is already captured
		{
			HC_SR04.IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (HC_SR04.IC_Val2 > HC_SR04.IC_Val1)
			{
				HC_SR04.Difference = HC_SR04.IC_Val2 - HC_SR04.IC_Val1;
			}

			else if (HC_SR04.IC_Val1 > HC_SR04.IC_Val2)
			{
				HC_SR04.Difference = (0xffff - HC_SR04.IC_Val1) + HC_SR04.IC_Val2;
			}

			HC_SR04.Distance = HC_SR04.Difference * .034/2;
			HC_SR04.Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(HC_SR04.HC_SR04_timer, TIM_IT_CC1);
		}
	}
}
