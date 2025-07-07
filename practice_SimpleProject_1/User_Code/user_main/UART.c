/*
 * UART.c
 *
 *  Created on: Jun 2, 2025
 *      Author: linep
 */

#include "UART.h"


/*
 * @brief	UART 글자출력함수
 * @details	UART통신을 이용해서 아스키코드 포맷으로 출력하는 함수 / printf함수와 유사
 * @param
 * @return	int
 */
int UART_print(char *format, ...) {
    char buffer[256];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    HAL_UART_Transmit(&UART, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
    return 0;
}
