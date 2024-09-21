#include "stm32f10x.h"

//2024_9_21
void LED_Init(void)
{
    RCC->APB2ENR |= (1<<2);
    //重置PA0_PA1_CRL_0000;
    GPIOA->CRL &= ~(0xF);
    //PA0_PA1_out_pp_50mhz
    GPIOA->CRL |= 0x33;
}

void LED_ON(void)
{
    //PA0_PA1_OUT_0
    GPIOA->BSRR |= (0x3<<16);
}

void LED_OFF(void)
{
    //PA0_PA1_OUT_1
    GPIOA->BSRR |= (0x3);
}

// void Button_Init(void)
// {
//     //重置PA6_CRL_0000
//     GPIOA->CRL &= ~(0xF<<24);
//     //PA6上下拉输入
//     GPIOA->CRL |= (0x8<<24);
// }

// uint16_t Read_Button_In(void)
// {
//     uint16_t PA6_In = (GPIOA->IDR>>6 & 1);
//     return PA6_In;
// }

// uint16_t Read_LED_Out(void)
// {
//     uint16_t PA0_PA1_Out = (GPIOA->ODR & 1);
//     return PA0_PA1_Out;
// }

void Delay(uint16_t ms)
{
    SysTick->CTRL = 1;
    SysTick->VAL = 0;
    while(ms--)
    {
        SysTick->LOAD = 9000 - 1;
        while(!((SysTick->CTRL>>16) & 1));
    }
    SysTick->CTRL = 0;
}

void Redray_Sensor_Init(void)
{
    //AFIO时钟开启
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    RCC->APB2ENR |= (0x1<<0);
    
    //设置GPIO_PA7
    // GPIO_InitTypeDef GPIOA_InitStructure;
    // GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    // GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_7;
    // GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    // GPIO_Init(GPIOA,&GPIOA_InitStructure);
    GPIOA->CRL &= ~(0xF<<28);
    GPIOA->CRL |= (0x8<<28);

    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
    AFIO->EXTICR[1] = ~(0xF<<12);
    AFIO->EXTICR[1] |= (0x0<<12);


    // EXTI_InitTypeDef EXTI_InitStructure;
    // EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    // EXTI_Init(&EXTI_InitStructure);
    EXTI->IMR |= (1<<7);
    EXTI->RTSR |= (1<<7);

    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // NVIC_InitTypeDef NVIC_Struct;
    // NVIC_Struct.NVIC_IRQChannel = EXTI9_5_IRQn;
    // NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 2;
    // NVIC_Struct.NVIC_IRQChannelSubPriority = 2;
    // NVIC_Init(&NVIC_Struct);
    SCB->AIRCR = (0x5FA<<16)|(0x5<<8);
    NVIC->ISER[0] |= (1<<23);
    NVIC->IP[23] |= (0x5<<4); 
}

void EXTI9_5_IRQHandler(void)
{
    Delay(20);
    while(GPIOA->IDR>>7 & 1)
    {
        EXTI->PR = (1<<7);
        LED_OFF();
        Delay(50);
    }
}
