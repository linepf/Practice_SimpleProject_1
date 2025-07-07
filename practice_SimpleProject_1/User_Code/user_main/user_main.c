/*
 * user_main.c
 *
 *  Created on: May 19, 2025
 *      Author: linep
 *
 */

#include "user_main.h"



void user_main() {
	LCD_Init();
	LCD_setCursor(0, 0);
	HC_SR04_Init();
	int a = 0;


	while (1) {

		HAL_Delay(500);

		DHT11_Read_tmepandhum();
		LCD_setCursor(0, 0);
		LCD_print_String("T: %.2f ", DHT11.DHT11_temp);
		LCD_print_String("H: %d", DHT11.DHT11_hum);

		a = HC_SR04_Read();
		LCD_setCursor(0, 1);
		LCD_print_String("Distance : %.3d", a);
		UART_print("Distance : %.3d\n", a);

	}

}

