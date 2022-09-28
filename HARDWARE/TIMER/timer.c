#include "timer.h"
#include "led.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////
//STM32F103ZE���İ�
//��ʱ�� ��������

//////////////////////////////////////////////////////////////////////////////////

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //ʹ��ָ����TIM3�ж�,���������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;			  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);							  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE); //ʹ��TIMx����
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void) //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���TIMx���жϴ�����λ:TIM �ж�Դ
		LED1 = !LED1;
	}
}

//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);						//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5

	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;									 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO

	//��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM3 Channel1 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			  //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);					  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel2 PWMģʽ
	//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel3 PWMģʽ
	//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel4 PWMģʽ
	//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM3, ENABLE); //ʹ��TIM3
}

//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);						//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE); //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5

	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;										 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ��GPIO

	//��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);				//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM3 Channel1 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			  //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);					  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel2 PWMģʽ
	//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel3 PWMģʽ
	//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���

	//��ʼ��TIM3 Channel4 PWMģʽ
	//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM4, ENABLE); //ʹ��TIM3
}

void motor0(int speed, int in1, int in2) //right behind motor
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_0, in1);
	GPIO_WriteBit(GPIOD, GPIO_Pin_1, in2);
	TIM_SetCompare1(TIM4, speed); //PD12
								  //pca_setpwm(0,0,speed);
}

void motor1(int speed, int in1, int in2) //left behind motor
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_2, in1);
	GPIO_WriteBit(GPIOD, GPIO_Pin_3, in2);
	//pca_setpwm(1,0,speed);
	TIM_SetCompare2(TIM3, speed); //PB5
}

void motor2(int speed, int in1, int in2) //left forward motor
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_4, in1);
	GPIO_WriteBit(GPIOD, GPIO_Pin_5, in2);
	//pca_setpwm(2,0,speed);
	TIM_SetCompare3(TIM3, speed); //PB0
}

void motor3(int speed, int in1, int in2) //right forward motor
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_6, in1);
	GPIO_WriteBit(GPIOD, GPIO_Pin_7, in2);
	//pca_setpwm(3,0,speed);
	TIM_SetCompare4(TIM3, speed); //PB1
}

void motor4(int speed, int in1, int in2)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_8, in1);
	GPIO_WriteBit(GPIOD, GPIO_Pin_9, in2);
	TIM_SetCompare2(TIM4, speed);
	//pca_setpwm(4,0,speed);//PD13
}

void all_motor(int speed, int in1, int in2)
{
	motor0(speed, in1, in2); //right forward
	motor1(speed, in1, in2); //left forward
	motor2(speed, in1, in2);
	motor3(speed, in1, in2);
}

//void motor5(int speed,int in1,int in2)
//{
//	GPIO_WriteBit(GPIOD,GPIO_Pin_10,in1);
//	GPIO_WriteBit(GPIOD,GPIO_Pin_11,in2);
//	//TIM_SetCompare1(TIM3,speed);
//	pca_setpwm(5,0,speed);
//}
//void encoder_tim2_init(void)
//{
//	// GPIO????
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	GPIO_InitTypeDef GPIO_InitStructure;  // GPIO???????????,???????????
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
////	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM2);
////	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM2);
////
//	// ???????????
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//
//	TIM_DeInit(TIM2);
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Prescaler = 0;
//	TIM_TimeBaseStructure.TIM_Period = 65535;
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ????????,??????
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//
//	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // ??????????
//
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	//TIM_ICInitStructure.TIM_ICFilter = 10; // ????????,??????
//	TIM_ICInit(TIM2, &TIM_ICInitStructure);
//
//	TIM_SetCounter(TIM2, 0);
//	TIM_Cmd(TIM2, ENABLE);
//}

//// ????????
//int read_encoder(void)
//{
//	int encoder_num;
//	encoder_num = (int)((int16_t)(TIM3->CNT)); // ????????????
//	TIM_SetCounter(TIM3, 0);
//	return encoder_num;
//}

//int main(void)
//{
//	u32 t=0;
//	uart_init(115200);
//	encoder_tim3_init();
//	delay_init(84);
//	int encoder;
//    while(1){
//		encoder = read_encoder();
//        printf("t:%d\r\n",encoder);
//		delay_ms(1000);
//		t++;
//	}
//}
