/*
 * LCD_I2C_16x2.c
 *
 *  Created on: Jul 4, 2025
 *      Author: JJH
 */

#include "LCD_I2C_16x2.h"

/*
* @brief	데이터 또는 명령어를 받아서 실제로 I2C통신을 이용해 LCD로 보내는 함수
* @details
* @param	cmd, flag
* @return	viod
*/
void LCD_SendInternal(uint8_t cmd, uint8_t flag)
{
  uint8_t data_u, data_l;
  uint8_t data_t[4];

  data_u = (cmd & 0xf0);
  data_l = ((cmd<<4) & 0xf0);
  data_t[0] = data_u|flag|0x0C;
  data_t[1] = data_u|flag|0x08;
  data_t[2] = data_l|flag|0x0C;
  data_t[3] = data_l|flag|0x08;
  HAL_I2C_Master_Transmit (&I2C_LCD_I2C_16X2, LCD_ADDR,data_t, sizeof(data_t), HAL_MAX_DELAY);
  HAL_Delay(5);
}

/*
* @brief	명령어를 LCD로 출력하는 함수
* @details	내부적으로 LCD_SendData로 명령어 전송
* @param	cmd
* @return	viod
*/
void LCD_print_Cmd(uint8_t cmd) {
  LCD_SendInternal(cmd, 0x00);
}

/*
* @brief	글자를 출력하는 함수
* @details	글자를 받아서 내부적으로 LCD_SendData로 한 워드씩 출력
* @param	str
* @return	viod
*/
void LCD_print_String(char *format, ...) {
	char buffer[256];

	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	char *temp = buffer;
    while(*temp) {
    	LCD_SendData(*temp++);
    }
}

/*
* @brief	데이터를 LCD로 출력하는 함수
* @details	내부적으로 LCD_SendData로 명령어 전송
* @param	data
* @return	void
*/
void LCD_SendData(uint8_t data) {
  LCD_SendInternal(data, 0x01);
}

/*
* @brief	LCD를 처음 켤때 초기화 해주는 함수
* @details	글자크기, 커서표시여부, 비트수, 백라이트 설정등을 제어
* @param	void
* @return	void
*/
void LCD_Init(void) {
  // LCD_FUNCTIONSET, 8-bit mode, 2 lines, 5x8 format
	LCD_print_Cmd(0x38); // 0b00111000
  // display & cursor home
	LCD_print_Cmd(0x02); // 0b00000010
  // display on, right shift, underline off, blink off
	LCD_print_Cmd(0x0C); // 0b00001100
  // clear display (optional here)
	LCD_print_Cmd(0x01); // 0b00000001
  // LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDEC
	LCD_print_Cmd(0x06); // 0b00000110
}


/*
* @brief	LCD화면을 클리어 하는 함수
* @details	...
* @param	void
* @return	void
*/
void LCD_clear(){
	LCD_print_Cmd(LCD_CLEARDISPLAY);
    HAL_Delay(2);
}


/*
* @brief	LCD의 커서 위치제어 함수
* @details	본 LCD는 16*2 크기이다.
* @param	width(가로), length(세로)
* @return	void
*/
void LCD_setCursor(uint8_t col, uint8_t row){
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if ( row > LCD_LINES ) {
        row = LCD_LINES-1;
    }
    LCD_print_Cmd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}
