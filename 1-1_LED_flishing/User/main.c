#include "stm32f10x.h"

int main(void)
{
    //配置RCC_PP_PIN0_50MHZ
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //GPIOA0 -- 3.3v
    //SET - turn off
    //RESET - turn on
    while(1)
    {
        GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);//turn on

        //  GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);//turn off
    }
}
