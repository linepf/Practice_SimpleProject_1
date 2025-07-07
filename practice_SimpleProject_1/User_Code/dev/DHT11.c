/*
 * DHT11.c
 *
 *  Created on: Jul 6, 2025
 *      Author: JJH
 */


#include "DHT11.h"
struct DHT11_structure DHT11;

/*
* @brief	MCU가 DHT11로 시작신호를 보내는 함수
* @details
* @param	void
* @return	void
*/
void DHT11_Start(){
	Set_Pin_Output();
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 0);
	delay_us(18000);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);
	delay_us(20);
	Set_Pin_Input();
}

/*
* @brief	DHT11에 연결된 신호핀을 Output로 만드는 함수
* @details
* @param	void
* @return	void
*/
void Set_Pin_Output() {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = DHT11_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

/*
* @brief	DHT11에 연결된 신호핀을 Input로 만드는 함수
* @details
* @param	void
* @return	void
*/
void Set_Pin_Input() {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

/*
* @brief	DHT11이 처음에 제대로 응답하는지 확인하는 함수
* @details	정상응답 : 1 / 제대로 응답하지 않거나 전혀 응답이 없을경우: 0
* @param	void
* @return	void
*/
uint8_t DHT11_Check_Response() {
	uint8_t Response = 0;
	delay_us(40);
	if (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))) {
		delay_us(80);
		if ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))) {
			Response = 1;
		} else {
			Response = 0;
		}
	}

	uint8_t timeout = 0;
	while((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))){
		if (++timeout > 50) return 0; // 타임아웃 50us 이상
		delay_us(1);
	}

	return Response;
}

/*
* @brief	DHT11에서 오는 온습도 및 체크sum 을 읽는 함수
* @details	8bit씩 읽으므로 이함수를 총 5번 사용해야 한다
* @param	void
* @return	void
*/
uint8_t DHT11_Read_8bit(void) {

	uint8_t i, j;
	uint8_t timeout = 0;
	for (j = 0; j < 8; j++) {
		timeout = 0;
		while (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))) {
			if (++timeout > 50) return 0xFF; // 타임아웃 50us 이상
			delay_us(1);
		}
		delay_us(40);   // wait for 40 us
		if (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))   // if the pin is low
		{
			i &= ~(1 << (7 - j));   // write 0
		} else
			i |= (1 << (7 - j));  // if the pin is high, write 1
		timeout = 0;
		while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)) {
			if (++timeout > 50) return 0xFF; // 타임아웃 50us 이상
			delay_us(1);
		}
	}
	return i;
}

/*
* @brief	DHT11 온도 출력함수
* @details	통신에서 오류가 나거나 체크섬이 안맞으면 0xff를 출력한다
* 			이 함수를 사용 할때는 2초 간격으로 사용하기를 권장한다
* @param	void
* @return	0xff, result
*/
float DHT11_Read_temp(){
	DHT11_Start();
	int a = DHT11_Check_Response();
	if(a == 0xFF) return 0xFF;

	uint8_t temp , hum, sum , hum1 , temp1 ;
	hum = DHT11_Read_8bit();
	hum1 = DHT11_Read_8bit();
	temp = DHT11_Read_8bit();
	temp1 = DHT11_Read_8bit();
	sum = DHT11_Read_8bit();

	float result = temp + (temp1 / 10.0f);

	if((hum + temp + hum1 + temp1) == sum) return result;
	else return 0xFF;
}

/*
* @brief	DHT11 습도 출력함수 정수로만 출력, 소수점 지원 안함
* @details	통신에서 오류가 나거나 체크섬이 안맞으면 0xff를 출력한다
* 			이 함수를 사용 할때는 2초 간격으로 사용하기를 권장한다
* @param	void
* @return	0xff, hum
*/
uint8_t DHT11_Read_hum(){
	DHT11_Start();
	int a = DHT11_Check_Response();
	if(a == 0xFF) return 0xFF;

	uint8_t temp , hum, sum , hum1 , temp1 ;
	hum = DHT11_Read_8bit();
	hum1 = DHT11_Read_8bit();
	temp = DHT11_Read_8bit();
	temp1 = DHT11_Read_8bit();
	sum = DHT11_Read_8bit();

	if((hum + temp + hum1 + temp1) == sum) return hum;
	else return 0xFF;
}

/*
* @brief	DHT11 습도 온도 한번에 확인하는 함수
* @details	온도는 float이고 습도는 int형이므로 정의 되어 있는 구조체를 사용
* 			통신에서 오류가 나거나 체크섬이 안맞으면 0xff를 출력한다
* 			이 함수를 사용 할때는 2초 간격으로 사용하기를 권장한다
* @param	void
* @return	0xff, hum
*/
uint8_t DHT11_Read_tmepandhum(){
		DHT11_Start();
		int a = DHT11_Check_Response();
		if(a == 0xFF) return 0xFF;

		uint8_t temp , hum, sum , hum1 , temp1 ;
		hum = DHT11_Read_8bit();
		hum1 = DHT11_Read_8bit();
		temp = DHT11_Read_8bit();
		temp1 = DHT11_Read_8bit();
		sum = DHT11_Read_8bit();

		float result = temp + (temp1 / 10.0f);

		if((hum + temp + hum1 + temp1) == sum)
		{
			DHT11.DHT11_temp = result;
			DHT11.DHT11_hum = hum;
			return 0;
		}else return 0xFF;
}
