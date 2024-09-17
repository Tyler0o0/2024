#include "stm32f10x.h"

#include "Driver.h"
int main()
{
    void RCCCLK();
    RCC->APB2ENR |= (1<<2);//GPIOA时钟使能
    GPIOA->CRL &= ~(0xF<<0);//clear PA0 ORD
    GPIOA->CRL |= ~(0xC<<0);//PA0_OUT_PP_50MHZ
    GPIOA->ODR |= (1<<0);
    while(1)
    {
        
    }
}
