#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"

void delay_1ms(unsigned int i);
int main(void)
{
	LED_GPIO_Config();
	KEY_GPIO_Config();
	GPIO_SetBits(GPIOF,GPIO_Pin_6);
	while (1)
	{
		if (KEY_Scan(GPIOA,GPIO_Pin_0) == 1)
		{
			/* code */
			LED1_TOGGLE;
		}
				
	}
}

// ÑÓÊ±1sº¯Êý
void delay_1ms(unsigned int i)
{
	while (i--)
		for (int j = 0; j < 5000; j++);
}
