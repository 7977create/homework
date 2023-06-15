#ifndef __SERVER_H
#define __SERVER_H
#include "sys.h"

/*
 *	舵机驱动头文件
 */

void TIM8_PWM_Init(void);
void Server_360_Forward(void);
void Server_180_Angle(void);
#endif 
