#include "stm32f10x.h"

//初始化
void Buzzer_On(void)
{
    //开启PB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct_PA;
        GPIO_InitStruct_PA.GPIO_Mode = GPIO_Mode_Out_PP;//推挽
        GPIO_InitStruct_PA.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;//
        GPIO_InitStruct_PA.GPIO_Speed = GPIO_Speed_50MHz;

    //设置输出模式
    GPIO_Init(GPIOA,&GPIO_InitStruct_PA);
}
void Delay_ms(uint32_t ms)
{
    SystemCoreClock = 9000000;
    uint32_t ticks = (SystemCoreClock/1000)*ms;
    //SysTickick初始化
    SysTick->LOAD = ticks-1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Pos|
                    SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick->CTRL>>16))
    {
        ;
    }
    SysTick->CTRL = SysTick_CTRL_ENABLE_Pos;
}
int main(void)
{
    //初始化
    Buzzer_On();
    int ms = 1000;//0<ms<1000;
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
    while(1)
    {
        GPIOA->BRR = 0x3;
        Delay_ms(ms);
        GPIOA->BSRR = 0x3;
        Delay_ms(ms);
    }
}

