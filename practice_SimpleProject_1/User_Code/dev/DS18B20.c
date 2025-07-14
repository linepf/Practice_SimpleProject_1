/*
 * DS18B20.c
 *
 *  Created on: Jul 14, 2025
 *      Author: JJH
 */


#include "DS18B20.h"


/*
* @brief	MCU가 DS18B20로 시작신호를 보내는 함수
* @details	DS18B20에서 응답이 없으면 0, 있으면 1
* @param	void
* @return	1 0
*/
uint8_t DS18B20_Reset(void) {
    uint8_t presence = 0;

    DS18B20_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
    delay_us(480);

    DS18B20_Pin_Input();
    delay_us(70);

    presence = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN);
    delay_us(410);

    return (presence == 0) ? 1 : 0;
}

/*
* @brief	DS18B20 버스를 output으로 설정
* @details	...
* @param	void
* @return	void
*/
void DS18B20_Pin_Output(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

/*
* @brief	DS18B20 버스를 input으로 설정
* @details	...
* @param	void
* @return	void
*/
void DS18B20_Pin_Input(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 내부 풀업 저항 활성화
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

/*
* @brief	DS18B20으로 한비트씩출력하는 함수
* @details	...
* @param	void
* @return	void
*/
void DS18B20_WriteBit(uint8_t bit) {
	DS18B20_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);

    if (bit) {
        delay_us(1);
        DS18B20_Pin_Input();
        delay_us(59);
    } else {
        delay_us(60);
        DS18B20_Pin_Input();
    }
}

/*
* @brief	DS18B20으로 1byte를 출력하는 함수
* @details	...
* @param	void
* @return	void
*/
void DS18B20_WriteByte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        DS18B20_WriteBit(byte & 0x01);
        byte >>= 1;
    }
}

/*
* @brief	DS18B20으로 1bit를 읽는 함수
* @details	...
* @param	void
* @return	bit
*/
uint8_t DS18B20_ReadBit(void) {
    uint8_t bit = 0;

    DS18B20_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
    delay_us(1);

    DS18B20_Pin_Input();
    delay_us(14);

    bit = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN);
    delay_us(45);

    return bit;
}

/*
* @brief	DS18B20으로 1byte를 읽는 함수
* @details	...
* @param	void
* @return	byte
*/
uint8_t DS18B20_ReadByte(void) {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if (DS18B20_ReadBit()) {
            byte |= (1 << i);
        }
    }
    return byte;
}

/*
* @brief	DS18B20에서 온도값을 읽어오는 함수
* @details	이 함수는 버스(신호선)에 센서가 한개만 있을때 사용해야한다.
* @param	void
* @return	byte
*/
float DS18B20_GetTemperature(void) {
    uint8_t temp_lsb, temp_msb;
    int16_t temp_raw;

    if (!DS18B20_Reset()) return -1000;

    DS18B20_WriteByte(0xCC);
    DS18B20_WriteByte(0x44);

    HAL_Delay(750);

    DS18B20_Reset();

    DS18B20_WriteByte(0xCC);
    DS18B20_WriteByte(0xBE);

    temp_lsb = DS18B20_ReadByte();
    temp_msb = DS18B20_ReadByte();

    temp_raw = (temp_msb << 8) | temp_lsb;

    return temp_raw / 16.0;
}
