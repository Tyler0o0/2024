#include "stm32f10x.h"

void SysTick_Init(uint32_t ticks)
{
    SysTick->LOAD = ticks - 1;//LOAD max,ticks&截断为24Bit
    SysTick->VAL = 0;//初始化计数
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Pos | //AHB/8
                    SysTick_CTRL_ENABLE_Msk;//SysTick启动
}
void SysTic_AHB8_DelayS(uint32_t AHB8,uint32_t s)
{
    //设置SysTickClock MHZ
    SystemCoreClock = AHB8;
    uint32_t i = 0;
    for(i = 0;i<s;i++)
    {   
        //SysTick初始化
        SysTick_Init(SystemCoreClock);

        //等待Counter结束
        // SysTick->CTRL
        //0000 0000 0000 0000 0000 0000 0000 0101 & 0000 0000 0000 0001 0000 0000 0000 0000
        //不等于零证明计时结束
        while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
        {
            ;
        }
            //关闭SysTick
        SysTick->CTRL = SysTick_CTRL_ENABLE_Pos;
    }

}

int main(void)
{
    //配置RCC_PP_PIN0_50MHZ
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&GPIO_InitStructure);//结构体状态写入GPIOA
   
    
    uint32_t AHB8 = 9000000/8;

    //循环次数；
    uint32_t s = 1;
    //GPIOA0 -- 3.3v
    //SET - turn off
    //RESET - turn on
    while(1)
    {
        uint32_t i = 1;
        for(i = 1;i<=0x80;i = i<<1)
        {
            GPIO_Write(GPIOA,~i);
            SysTic_AHB8_DelayS(AHB8,s);
        }
        // GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);//turn on
        // SysTic_AHB8_DelayS(AHB8,s);//1s延时
        // GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);//turn off
        // SysTic_AHB8_DelayS(AHB8,s);//1s延时
    }
}
