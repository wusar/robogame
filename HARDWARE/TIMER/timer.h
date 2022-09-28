#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "pca9685.h"
//////////////////////////////////////////////////////////////////////////////////
//STM32F103ZE���İ�
//��ʱ�� ��������

//********************************************************************************

void TIM3_Int_Init(u16 arr, u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);
void TIM4_PWM_Init(u16 arr, u16 psc);
void motor0(int speed, int in1, int in2);
void motor1(int speed, int in1, int in2);
void motor2(int speed, int in1, int in2);
void motor3(int speed, int in1, int in2);
void motor4(int speed, int in1, int in2);
//void motor5(int speed,int in1,int in2);
void all_motor(int speed, int in1, int in2);
#endif
