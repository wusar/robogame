#include "encoder.h"
int encoder_num0 = 0;
int motor_speed0 = 0;
int last_encoder_num0 = 0;

int encoder_num1 = 0;
int motor_speed1 = 0;
int last_encoder_num1 = 0;

int encoder_num2 = 0;
int motor_speed2 = 0;
int last_encoder_num2 = 0;

int all_time = 0;
//????0????
void EXTIX_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //????????
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //??GPIOA??
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //100M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10);
    EXTI_InitStructure.EXTI_Line = EXTI_Line10;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);                              //??EXTI_InitStruct???????????EXTI???
                                                                 //    //GPIOA.11 ???????????? ?????
                                                                 //    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource11);
                                                                 //    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
                                                                 //    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
                                                                 //    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
                                                                 //    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
                                                                 //    EXTI_Init(&EXTI_InitStructure); //??EXTI_InitStruct???????????EXTI???
                                                                 ////    //GPIOA.12 ???????????? ?????
                                                                 //    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource12);
                                                                 //    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
                                                                 //    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
                                                                 //    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
                                                                 //    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
                                                                 //    EXTI_Init(&EXTI_InitStructure);                              //??EXTI_InitStruct???????????EXTI??
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;         //????????
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //?????2,
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;        //????3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //????????
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        //delay_us(10);
        //if(PEin(10)==1)
        if (PEin(10) != PEin(11))
            encoder_num0++;
        else
            encoder_num0--;
        EXTI_ClearITPendingBit(EXTI_Line10); //??LINE???????
    }
    //	if (EXTI_GetITStatus(EXTI_Line11) != RESET)
    //	{

    //     encoder_num1++;
    //			EXTI_ClearITPendingBit(EXTI_Line11); //??LINE???????
    // }
    //	//LED0=!LED0;
    //	if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    //	{

    //     encoder_num2++;
    //			EXTI_ClearITPendingBit(EXTI_Line12); //??LINE???????
    // }
}

//void EXTI12_IRQHandler(void)
//{
//
//
//}
////????10~15????
//void EXTI15_10_IRQHandler(void)
//{
//	LED0=!LED0;
//    // A??????
//    if (EXTI_GetITStatus(EXTI_Line11) != RESET)
//    {
//        // ??B????
//        if (ENCODER_B == 1)
//            encoder_num1--;
//        else
//            encoder_num1++;
//        EXTI_ClearITPendingBit(EXTI_Line11); //??LINE???????
//    }
//    // B??????
//    if (EXTI_GetITStatus(EXTI_Line12) != RESET)
//    {

//        if (ENCODER_A == 1)
//            encoder_num1++;
//        else
//            encoder_num1--;
//        EXTI_ClearITPendingBit(EXTI_Line12); //??LINE???????
//    }
//}
void TIM5_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //????

    TIM_TimeBaseStructure.TIM_Period = arr; //?????????

    TIM_TimeBaseStructure.TIM_Prescaler = psc; //??????TIMx

    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM??????
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             //??

    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);                //?????TIM4??,??????
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;           //TIM4??
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //?????0?
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //????3?
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ?????
    NVIC_Init(&NVIC_InitStructure);                           //??

    TIM_Cmd(TIM5, ENABLE); //??TIMx??
}

void motor_control(void)
{
    all_time++;
    motor_speed0 = encoder_num0 - last_encoder_num0; // ???????
    last_encoder_num0 = encoder_num0;                // ??,??????
    // motor_speed1 = encoder_num1 - last_encoder_num1; // ???????
    // last_encoder_num1 = encoder_num1;                // ??,??????
    // motor_speed2 = encoder_num2 - last_encoder_num2; // ???????
    // last_encoder_num2 = encoder_num2;                // ??,??????
}

void TIM5_IRQHandler(void) //TIM4??
{
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //?????TIM?????
    {
        motor_control();
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update); //??TIMx???????:TIM ?
    }
}
