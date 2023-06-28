#include "bsp_systick.h"

// __IO是volatile防止编译器优化
__IO uint32_t time;
/*系统定时器初始化函数*/
void Systick_Init(void){
    // 设置定时时间为1ms
    if (SysTick_Config(SystemCoreClock/1000))
    {
        /* code */
        while(1);
    }

}

// 延时nms
void Delay_nms(__IO uint32_t n){
    time = n;
    while (time);
}
