#include "stm32f4xx.h"
#include "bsp_led.h"

void delay_1ms(unsigned int i);
int main(void)
{
	LED_GPIO_Config();
	GPIO_SetBits(GPIOF,GPIO_Pin_6);
	GPIO_SetBits(GPIOF,GPIO_Pin_7);
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	while (1)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_6);
		delay_1ms(5000);
		GPIO_SetBits(GPIOF,GPIO_Pin_6);
		delay_1ms(5000);
		GPIO_ResetBits(GPIOF,GPIO_Pin_7);
		delay_1ms(5000);
		GPIO_SetBits(GPIOF,GPIO_Pin_7);
		delay_1ms(5000);
		GPIO_ResetBits(GPIOF,GPIO_Pin_8);
		delay_1ms(5000);
		GPIO_SetBits(GPIOF,GPIO_Pin_8);
		delay_1ms(5000);
	}
}

// ÑÓÊ±1sº¯Êý
void delay_1ms(unsigned int i)
{
	while (i--)
		for (int j = 0; j < 5000; j++);
}
