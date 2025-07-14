/*
 * HC_06.c
 *
 *  Created on: Jul 13, 2025
 *      Author: JJH
 */


#include "HC_06.h"

int HC_06_print(char *format, ...){
	  char buffer[256];

	    va_list args;
	    va_start(args, format);
	    vsnprintf(buffer, sizeof(buffer), format, args);
	    va_end(args);

	    HAL_UART_Transmit(&HC_06, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
	    return 0;
}
