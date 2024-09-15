#include "stm32f10x.h"

#define HZ 9000000

void Init_GPIOA(uint32_t GPIO_Mode_x,uint32_t GPIO_Pin_x,uint32_t GPIO_Speed_x);

void Init_GPIOB(uint32_t GPIO_Mode_x,uint32_t GPIO_Pin_x,uint32_t GPIO_Speed_x);

void GPIOx_CRTL(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin_x,uint32_t Set);

void Delay_ms(uint32_t MHZ,uint32_t ms,uint32_t cycle);

uint8_t IPU_INCRTL(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin_x);