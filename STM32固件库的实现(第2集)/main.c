#include "stm32f4xx.h" // Device header
#include "stm32f4xx_gpio.h"

void SystemInit(void);
void delay_1ms(unsigned int i);

int main(void)
{
	// 1.开GPIOF的时钟
	RCC_AHB1ENR |= (1<<5);
	// 初始化IO口
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	while (1)
	{
		// 3.向GPIOF_ODR中写入数据
		// 熄灭灯
		GPIOF->ODR |= GPIO_InitStruct.GPIO_Pin;
		// GPIO_ResetBits(GPIOF,GPIO);
		delay_1ms(1000);
		// 亮灯
		GPIOF->ODR &= ~GPIO_InitStruct.GPIO_Pin;
		// GPIO_SetBits(GPIOF,GPIO);
		delay_1ms(1000);
	}
}

void SystemInit(void)
{
	// 系统时钟初始化函数
}
// 延时1s函数
void delay_1ms(unsigned int i)
{
	while (i--)
		for (int j = 0; j < 1000; j++);
}
