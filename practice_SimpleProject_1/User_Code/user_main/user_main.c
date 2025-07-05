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
	HC_SR04_Init(&htim1, 1);

	while (1) {

		HC_SR04_Read();
		LCD_setCursor(0, 0);
		LCD_print_String("distance : %.3d", HC_SR04.Distance);
		HAL_Delay(100);

	}

}

