#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();			//OLED初始化
	CountSensor_Init();		//计数传感器初始化
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Count:");	//1行1列显示字符串Count:
	int count = 0;
	while (1)
	{   for(int i = 0;i<1000;i++)
		{SysTick->LOAD = 72000 - 1;  // 9MHz 对应 1s, 计数从 9000 递减到 0
        SysTick->VAL = 0;          // 重置当前值
        SysTick->CTRL = 0x5;//AHB/8_unassert_enable; 
        while (!(SysTick->CTRL&(1<<16)));
        //关闭计时器
        SysTick->CTRL = 0;
		}
		count++;
		OLED_ShowNum(1, 7, count, 5);		//OLED不断刷新显示CountSensor_Get的返回值
	}
}
