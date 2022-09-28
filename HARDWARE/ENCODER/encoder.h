#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
#include "delay.h"
#include "stm32f10x_exti.h"
#include "led.h"
#define ENCODER_A GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11) //?????A?
#define ENCODER_B GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12) //?????B?
extern int encoder_num0;
extern int motor_speed0;
extern int last_encoder_num0;

extern int encoder_num1;
extern int motor_speed1;
extern int last_encoder_num1;

extern int encoder_num2;
extern int motor_speed2;
extern int last_encoder_num2;

extern int all_time;
void EXTIX_Init(void);
void TIM5_Int_Init(u16 arr, u16 psc);
void motor_control(void);

#endif
