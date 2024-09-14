#include "stm32f10x.h"                  // Device header

int main(void)
{
//	//直接控制寄存器电灯PC13
//	RCC->APB2ENR = 0x00000010;//PC13 control GPIOC
//	GPIOC->CRH = 0x00300000;//PC13 通用推挽输出模式 50MHZ
//	//PC13 0x00000000输出
//	//     0x00002000关闭输出
//	GPIOC->ODR = 0x00002000;
	
	//库函数实现PC13控制
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOC,GPIO_Pin_13);//高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	while(1)
	{
		
	}//
}
