#ifndef _KEY1_H
#define _KEY1_H	 

#include <stm32f10x.h>
#include "usart.h"
#include "sys.h"

#define uint unsigned int 
#define uchar unsigned char

#define X1_GPIO_PORT GPIOF           
#define X2_GPIO_PORT GPIOF   
#define X3_GPIO_PORT GPIOF           
#define X4_GPIO_PORT GPIOF 

#define Y1_GPIO_PORT GPIOF         
#define Y2_GPIO_PORT GPIOF   
#define Y3_GPIO_PORT GPIOF           
#define Y4_GPIO_PORT GPIOF 

#define X1_GPIO_PIN GPIO_Pin_7
#define X2_GPIO_PIN GPIO_Pin_6
#define X3_GPIO_PIN GPIO_Pin_5
#define X4_GPIO_PIN GPIO_Pin_4

#define Y1_GPIO_PIN GPIO_Pin_0
#define Y2_GPIO_PIN GPIO_Pin_1
#define Y3_GPIO_PIN GPIO_Pin_2
#define Y4_GPIO_PIN GPIO_Pin_3

#define X1_RCC RCC_APB2Periph_GPIOF
#define X2_RCC RCC_APB2Periph_GPIOF
#define X3_RCC RCC_APB2Periph_GPIOF
#define X4_RCC RCC_APB2Periph_GPIOF

#define Y1_RCC RCC_APB2Periph_GPIOF
#define Y2_RCC RCC_APB2Periph_GPIOF
#define Y3_RCC RCC_APB2Periph_GPIOF
#define Y4_RCC RCC_APB2Periph_GPIOF


#define KEY_ERR 255


void Matrix_Key_Init(void);
int Matrix_Key_Scan(void);
void Matrix_Key_Test(void) ;

#endif
