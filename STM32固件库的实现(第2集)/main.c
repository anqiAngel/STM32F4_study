#include "stm32f4xx.h" // Device header
#include "stm32f4xx_gpio.h"

void SystemInit(void);
void delay_1ms(unsigned int i);

int main(void)
{
	// 1.��GPIOF��ʱ��
	RCC_AHB1ENR |= (1<<5);
	// ��ʼ��IO��
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	while (1)
	{
		// 3.��GPIOF_ODR��д������
		// Ϩ���
		GPIOF->ODR |= GPIO_InitStruct.GPIO_Pin;
		// GPIO_ResetBits(GPIOF,GPIO);
		delay_1ms(1000);
		// ����
		GPIOF->ODR &= ~GPIO_InitStruct.GPIO_Pin;
		// GPIO_SetBits(GPIOF,GPIO);
		delay_1ms(1000);
	}
}

void SystemInit(void)
{
	// ϵͳʱ�ӳ�ʼ������
}
// ��ʱ1s����
void delay_1ms(unsigned int i)
{
	while (i--)
		for (int j = 0; j < 1000; j++);
}
