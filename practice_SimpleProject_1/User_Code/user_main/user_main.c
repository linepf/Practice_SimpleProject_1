/*
 * user_main.c
 *
 *  Created on: May 19, 2025
 *      Author: linep
 *
 */

#include "user_main.h"



void user_main() {
/*	LCD_Init();
	LCD_setCursor(0, 0);
	HC_SR04_Init();*/
	//int a = 0;

	WS2812B_Init();
	WS2812B_OFFPixel();
	HAL_Delay(500);
	int r=0,g=0,b=0;
	int a=255;
	int i=0;





	//WS2812B_SetPixel(4,0,250,0);

	while (1) {

		WS2812B_SetPixel(3, 0, 0, a);
		HAL_Delay(2000);
		WS2812B_SetPixel(0, a, 0, 0);
		HAL_Delay(2000);
		WS2812B_SetPixel(4, 0, a, 0);
		HAL_Delay(2000);
		WS2812B_SetPixel(2, a, a, a);
		HAL_Delay(2000);
		WS2812B_OFFPixel();
		HAL_Delay(500);



	/*	while(i != 4){
			if(r<a && g==0 && b==0){
				++r;
				WS2812B_SetPixel(i,r,g,b);
				HAL_Delay(10);
			}else if(r==a && g<a && b==0){
				++g;
				WS2812B_SetPixel(i,r,g,b);
				HAL_Delay(10);
			}else if(r==a && g==a && b<a){
				++b;
				WS2812B_SetPixel(i,r,g,b);
				HAL_Delay(10);
			}
			if(r==a && g==a && b==a){
				r=g=b=0;
				++i;
			}
		}
		WS2812B_OFFPixel();*/



		/*DHT11_Read_tmepandhum();
		LCD_setCursor(0, 0);
		LCD_print_String("T: %.2f ", DHT11.DHT11_temp);
		LCD_print_String("H: %d", DHT11.DHT11_hum);

		a = HC_SR04_Read();
		LCD_setCursor(0, 1);
		LCD_print_String("Distance : %.3d", a);
		UART_print("Distance : %.3d\n", a);*/


		//WS2812B_SetPixel(1,255,0,0);

	}

}

