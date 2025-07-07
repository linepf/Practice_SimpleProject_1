/*
 * LCD_I2C_16x2.h
 *
 *  Created on: Jul 4, 2025
 *      Author: JJH
 *
 *     I2C설정은 기본 설정으로 한다 i2c1사용
 *     기본모드
 *     100000hz
 *     Primary Address Length selection 7bit
 *     나머지는 전부 disabled
 *
 */

#ifndef DEV_LCD_I2C_16X2_H_
#define DEV_LCD_I2C_16X2_H_

#include "user_main.h"
#include <stdarg.h>

#define I2C_LCD_I2C_16X2	hi2c1				// 사용할 I2C 핸들러 입력
#define LCD_ADDR 			(0x3f << 1) 	//lcd 주소
#define LCD_CLEARDISPLAY 	0x01			//lcd화면 클리어
#define LCD_SETDDRAMADDR 	0x80			//
#define LCD_LINES 			2 				//16X2 numlines


void LCD_SendInternal(uint8_t cmd, uint8_t flag);
void LCD_print_Cmd(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Init(void);
void LCD_print_String(char *format, ...);
void LCD_clear();
void LCD_setCursor(uint8_t col, uint8_t row);


#endif /* DEV_LCD_I2C_16X2_H_ */
