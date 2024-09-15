#include "Diver_self.h"

// int main()
// {
//     Init_GPIOA(GPIO_Mode_Out_PP,GPIO_Pin_0,GPIO_Speed_50MHz);
//     Init_GPIOA(GPIO_Mode_Out_PP,GPIO_Pin_1,GPIO_Speed_50MHz);

//     Init_GPIOB(GPIO_Mode_IPU,GPIO_Pin_1,GPIO_Speed_50MHz);
//     Init_GPIOB(GPIO_Mode_IPU,GPIO_Pin_11,GPIO_Speed_50MHz);

//     uint8_t led_state = 0;
//     uint8_t button_pressed = 0;

//     uint32_t ms = 100;
//     uint32_t cycle = 1;
//     while(1)
//     {
//         //按一下点亮，按一下熄灭

//         if((IPU_INCRTL(GPIOB,GPIO_Pin_1)==1) && button_pressed == 0)
//         {
//             Delay_ms(HZ,ms,cycle);
//             if(IPU_INCRTL(GPIOB,GPIO_Pin_1)==1)
//             {
//                 led_state = !led_state;
//                 if(led_state)
//                 {
//                     GPIOx_CRTL(GPIOA,GPIO_Pin_0,RESET);
//                 }
//                 else
//                 {
//                     GPIOx_CRTL(GPIOA,GPIO_Pin_0,SET);
//                 }
//                 button_pressed = 1;//按键记录
//             }
//         }
//         else if (IPU_INCRTL(GPIOB,GPIO_Pin_1)==0)
//         {
//             button_pressed = 0;//松开重置
//         }
        
//         //按下点亮，松开熄灭
//         // if(IPU_INCRTL(GPIOB,GPIO_Pin_1) == 1)
//         // {
//         //     GPIOx_CRTL(GPIOA,GPIO_Pin_0,RESET);
//         // }
//         // else//return 0;
//         // {
//         //     GPIOx_CRTL(GPIOA,GPIO_Pin_0,SET);
//         // }

//         //按下熄灭
//         // GPIOx_CRTL(GPIOA,GPIO_Pin_0,RESET);
//         // GPIOx_CRTL(GPIOA,GPIO_Pin_1,SET);
//         // Delay_ms(HZ,ms,cycle);
//         // GPIOx_CRTL(GPIOA,GPIO_Pin_0,SET);
//         // GPIOx_CRTL(GPIOA,GPIO_Pin_1,RESET);
//         // Delay_ms(HZ,ms,cycle);
//     }
// }

int main(void)
{
    //light
    Init_GPIOA(GPIO_Mode_Out_PP,GPIO_Pin_0,GPIO_Speed_50MHz);

    //butter
    Init_GPIOB(GPIO_Mode_Out_PP,GPIO_Pin_12,GPIO_Speed_2MHz);

    //light sensor
    Init_GPIOB(GPIO_Mode_IPU,GPIO_Pin_14,GPIO_Speed_50MHz);
    uint32_t ms = 1000;
    uint32_t cycle = 5;
    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 0)
        {
            Delay_ms(HZ,100,1);
            GPIO_SetBits(GPIOA,GPIO_Pin_0);
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
            Delay_ms(HZ,100,1);
        }
        else
        {
            Delay_ms(HZ,100,1);
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            GPIO_ResetBits(GPIOA,GPIO_Pin_0);
            Delay_ms(HZ,100,1);
        }

        // GPIOx_CRTL(GPIOB,GPIO_Pin_12,RESET);
        // Delay_ms(HZ,100,1);
        // GPIOx_CRTL(GPIOB,GPIO_Pin_12,SET);
        // Delay_ms(HZ,ms,cycle);
    }
}