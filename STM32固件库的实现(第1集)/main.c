#include "stm32f4xx.h" // Device header

void SystemInit(void);
void delay_1ms(unsigned int i);

int main(void)
{
	// 1.开GPIOF的时钟
	RCC_AHB1ENR |= (1<<5);
	// 2.配置GPIOF为输出模式
	GPIOF->MODER &= ~(3<<(2*6));
	GPIOF->MODER |= (1<<(2*6));
	GPIOF->ODR |= (1<<6);
	while (1)
	{
		// 3.向GPIOF_ODR中写入数据
		// 熄灭灯
		GPIOF->ODR |= (1<<6);
		delay_1ms(1000);
		// 亮灯
		GPIOF->ODR &= ~(1<<6);
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
