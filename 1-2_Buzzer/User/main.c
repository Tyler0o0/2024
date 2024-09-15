#include "stm32f10x.h"

//初始化
void Buzzer_On(void)
{
    //开启PB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct_PB12;
        GPIO_InitStruct_PB12.GPIO_Mode = GPIO_Mode_Out_PP;//推挽
        GPIO_InitStruct_PB12.GPIO_Pin = GPIO_Pin_12;//
        GPIO_InitStruct_PB12.GPIO_Speed = GPIO_Speed_10MHz;

    //设置输出模式
    GPIO_Init(GPIOB,&GPIO_InitStruct_PB12);
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
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
    {
        ;
    }
    SysTick->CTRL = SysTick_CTRL_ENABLE_Pos;
}
int main(void)
{
    //初始化
    Buzzer_On();
    int ms = 100;//0<ms<1000;
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
    while(1)
    {
        // GPIO_ResetBits(GPIOB,GPIO_Pin_12);
        // Delay_ms(ms);
        // GPIO_SetBits(GPIOB,GPIO_Pin_12);
        // Delay_ms(ms);
    }
}

