/*
 * common.c
 *
 *  Created on: Jul 6, 2025
 *      Author: JJH
 */

#include "common.h"

/*
* @brief	us단위의 딜레이함수 USE_DELAY_US_TIMER 가 정의 되어있어야 한다.
* @details	HC_SR04 모듈의 트리거를 위해서 사용
* @param	딜레이할 정수값 입력 ex) 10이면 10us딜레이
* @return	viod
*/
#ifdef USE_DELAY_US_TIMER
void delay_us(uint16_t time){
	__HAL_TIM_SET_COUNTER(&DELAY_US_TIMER_HANDLE, 0);
	while (__HAL_TIM_GET_COUNTER (&DELAY_US_TIMER_HANDLE) < time);
}
#endif
