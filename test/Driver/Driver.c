#include "stm32f10x.h"

void RCCCLK(void)
{
    //HSEON,选择时钟
    RCC->CR |= (1<<16); //HSEON = 1,启动HSE

    //HSERDY
    while(!(RCC->CR & (1<<17)));//等待HSE 就绪
    
    //MCO，选择输出时钟
    RCC->CFGR &= ~(7<<24);// MCO 26:24位初始化为000
    RCC->CFGR |= (6<<24);// MCO 26:24设置为110(HSE输出)

    //PLLMUL，设置输出倍率
    RCC->CFGR &= ~(0xF<<18);//PLLMUL 输出倍率初始化为0000（2倍）
    RCC->CFGR |= (7<<18);//输出倍率设置为9倍，0111；

    //PLLSRC,HSE作为PLL输入时钟
    RCC->CFGR |= (1<<16);

    //PLLON，PLL使能
    RCC->CR |= (1<<24);

    //PLLRDY,等待PLL就绪
    while(!(RCC->CR & (1<<25)));

    //选择PLL作为系统时钟
    //SW
    RCC->CFGR &= ~(3<<0);//SW 初始化。00
    RCC->CFGR |= (1<<0);//SW 01，HSE为系统时钟

    //配置总线分频
    RCC->CFGR &= ~(0xF<<4);//AHB 不分频 HPRE
    RCC->CFGR &= ~(7<<8);//APB1 不分频 PPRE1
    RCC->CFGR &= ~(7<<11);//APB2 不分频 PPRE2
}