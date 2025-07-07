/*
 * UART.h
 *
 *  Created on: Jun 2, 2025
 *      Author: linep
 */

#ifndef USER_MAIN_UART_H_
#define USER_MAIN_UART_H_

#include "user_main.h"
#include <stdarg.h>

#define UART		  		huart1	// 사용할 UART 핸들러 입력

int UART_print(char *format, ...);

#endif /* USER_MAIN_UART_H_ */
