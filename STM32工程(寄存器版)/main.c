#include "stm32f4xx.h" // Device header

void SystemInit(void);
void delay_1ms(unsigned int i);

int main(void)
{
	// 1.����GPIOF��ʱ��
	*((unsigned int *)(0x40023800 + 0x30)) |= (1 << 5);
	// 2.����GPIOF����ģʽ
	*((unsigned int *)(0x40021400 + 0x00)) &= ~((0x30) << (2 * 6));
	*((unsigned int *)(0x40021400 + 0x00)) |= (1 << (2 * 6));
	*((unsigned int *)(0x40021400 + 0x00)) &= ~((0x30) << (2 * 7));
	*((unsigned int *)(0x40021400 + 0x00)) |= (1 << (2 * 7));
	*((unsigned int *)(0x40021400 + 0x00)) &= ~((0x30) << (2 * 8));
	*((unsigned int *)(0x40021400 + 0x00)) |= (1 << (2 * 8));
	// 3.GPIOF�������
	// ��λ��������ݶ���0
	// ��ʱ��Ϊ�졢�̡���������ɫ�Ļ��ɫ(��ɫ)
	// ��������Ϩ������ߵ�ƽ
	*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 6);
	*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 7);
	*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 8);
	while (1)
	{
		// ��������������ɫ���
		// PF6����͵�ƽ������LED
		*((unsigned int *)(0x40021400 + 0x14)) &= ~(1 << 6);
		delay_1ms(1500);
		// PF6����ߵ�ƽϨ���LED
		*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 6);
		delay_1ms(1500);
		// PF7����͵�ƽ������LED
		*((unsigned int *)(0x40021400 + 0x14)) &= ~(1 << 7);
		delay_1ms(1500);
		// PF7����ߵ�ƽϨ����LED
		*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 7);
		delay_1ms(1500);
		// PF8����͵�ƽ������LED
		*((unsigned int *)(0x40021400 + 0x14)) &= ~(1 << 8);
		delay_1ms(1500);
		// PF8����ߵ�ƽϨ����LED
		*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 8);
//		delay_1ms(1500);
	}
}
// 1.���������Ƶ���
// 2.��������˸
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
