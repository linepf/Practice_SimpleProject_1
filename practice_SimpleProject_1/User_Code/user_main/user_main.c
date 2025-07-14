/*
 * user_main.c
 *
 *  Created on: May 19, 2025
 *      Author: linep
 *
 */

#include "user_main.h"



void user_main() {
	float temperature;
	delay_us_Init();

	while (1) {

		temperature = DS18B20_GetTemperature();

		HC_06_print("Temperature %.2f\n",temperature);

		HAL_Delay(1000);


	}
}

