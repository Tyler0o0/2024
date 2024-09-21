#include "stm32f10x.h"

#include "OLED.h"

#include "Function.h"

//2024_9_21_检查输入，控制输出
// int main(void)
// {   
//     //PB12_PB13_OLED开启
//     OLED_Init();

//     //端口配置
//     LED_Init();
//     Button_Init();
//     uint16_t LED_state = 0;
    
//     //默认关闭
//     LED_OFF();
    
//     while(1)
//     {
//         Delay(50);
//         if(Read_Button_In())
//         {
//             LED_state = !LED_state;
//             if(LED_state)
//             {
//                 LED_ON();
//             }
//             else
//             {
//                 LED_OFF();
//             }
//         }

//         //等待松手
//         while(Read_Button_In())
//         {
//              Delay(50);
//         }
//     }
// }

int main(void)
{
    LED_Init();
    Redray_Sensor_Init();
    
    while(1)
    {
        LED_ON();
    }
}
