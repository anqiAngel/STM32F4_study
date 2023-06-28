#include "stm32f4xx.h" // Device header

void SystemInit(void);
void delay_1ms(unsigned int i);

int main(void)
{
	// 1.��GPIOF��ʱ��
	RCC_AHB1ENR |= (1<<5);
	// 2.����GPIOFΪ���ģʽ
	GPIOF->MODER &= ~(3<<(2*6));
	GPIOF->MODER |= (1<<(2*6));
	GPIOF->ODR |= (1<<6);
	while (1)
	{
		// 3.��GPIOF_ODR��д������
		// Ϩ���
		GPIOF->ODR |= (1<<6);
		delay_1ms(1000);
		// ����
		GPIOF->ODR &= ~(1<<6);
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
