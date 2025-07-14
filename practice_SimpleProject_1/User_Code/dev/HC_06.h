/*
 * HC_06.h
 *
 *  Created on: Jul 13, 2025
 *      Author: JJH
 */

#ifndef DEV_HC_06_H_
#define DEV_HC_06_H_

#include "user_main.h"
#include <stdarg.h>

#define HC_06		  		huart3	// 사용할 UART 핸들러 입력

int HC_06_print(char *format, ...);


#endif /* DEV_HC_06_H_ */
