#ifndef MOTOR_H
#define MOTOR_H	 
#include "sys.h"
#include "delay.h"
 
extern u8 STEP; //���嵥������ ȫ�ֱ���
 
 
#define STEP_MOTOR_PORT			GPIOG	//����IO�ӿ�������
#define STEP_MOTOR_A				GPIO_Pin_2	//����IO�ӿ�
#define STEP_MOTOR_B				GPIO_Pin_3	//����IO�ӿ�
#define STEP_MOTOR_C				GPIO_Pin_4	//����IO�ӿ�
#define STEP_MOTOR_D				GPIO_Pin_5	//����IO�ӿ�
#define STEP_MOTOR_CLK      RCC_APB2Periph_GPIOG
 
 
 
void STEP_MOTOR_Init(void);//��ʼ��
void STEP_MOTOR_OFF (void);//�ϵ�״̬
void STEP_MOTOR_8A (u8 a,u16 speed);
void STEP_MOTOR_NUM (u8 RL,u16 num,u8 speed);//�������������
void STEP_MOTOR_LOOP (u8 RL,u8 LOOP,u8 speed);//�����Ȧ������
 
#endif

