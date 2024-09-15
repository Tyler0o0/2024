void SysTick_Init(uint32_t ticks)
{
    SysTick->LOAD = ticks - 1;//LOAD max
    SysTick->VAL = 0;//初始化
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Pos | //AHB/8
        SysTick_CTRL_ENABLE_Msk;//SysTick启动
}
void SysTick_AHB8_DelayS(uint32_t AHB_8, uint32_t s)
{
    //设置SysTickClock MHZ
    SystemCoreClock = MHZ;
    int i = 0;
    for (i = 0; i < t; i++)
    {
        //SysTick初始化，溢出值保护
        SysTick_Init(SystemCoreClock);

        //等待Counter结束
        // SysTick->CTRL
        //0000 0000 0000 0000 0000 0000 0000 0101 & 0000 0000 0000 0001 0000 0000 0000 0000
        //不等于零证明计时结束
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
        {
            ;
        }

        //关闭SysTick
        SysTick->CTRL = SysTick_CTRL_ENABLE_Pos;
    }
}

void SysTick_AHB8_DelayMs(uint32_t AHB_8, uint32_t ms)
{
    //设置SysTickClock MHZ
    SystemCoreClock = AHB_8;
    int i = 0;
    for (i = 0; i < t; i++)
    {
        //SysTick初始化
        SysTick_Init((SystemCoreClock / 1000) * ms);

        //等待Counter结束
        // SysTick->CTRL
        //0000 0000 0000 0000 0000 0000 0000 0101 & 0000 0000 0000 0001 0000 0000 0000 0000
        //不等于零证明计时结束
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
        {
            ;
        }

        //关闭SysTick
        SysTick->CTRL = SysTick_CTRL_ENABLE_Pos;
    }
}