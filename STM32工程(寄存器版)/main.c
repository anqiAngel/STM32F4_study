#include "stm32f4xx.h" // Device header

void SystemInit(void);
void delay_1ms(unsigned int i);

int main(void)
{
	// 1.配置GPIOF的时钟
	*((unsigned int *)(0x40023800 + 0x30)) |= (1 << 5);
	// 2.配置GPIOF工作模式
	*((unsigned int *)(0x40021400 + 0x00)) &= ~((0x30) << (2 * 6));
	*((unsigned int *)(0x40021400 + 0x00)) |= (1 << (2 * 6));
	*((unsigned int *)(0x40021400 + 0x00)) &= ~((0x30) << (2 * 7));
	*((unsigned int *)(0x40021400 + 0x00)) |= (1 << (2 * 7));
	*((unsigned int *)(0x40021400 + 0x00)) &= ~((0x30) << (2 * 8));
	*((unsigned int *)(0x40021400 + 0x00)) |= (1 << (2 * 8));
	// 3.GPIOF输出数据
	// 复位后输出数据都是0
	// 此时灯为红、绿、蓝三种颜色的混合色(白色)
	// 让三个灯熄灭输出高电平
	*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 6);
	*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 7);
	*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 8);
	while (1)
	{
		// 先亮后灭否则会颜色混合
		// PF6输出低电平点亮红LED
		*((unsigned int *)(0x40021400 + 0x14)) &= ~(1 << 6);
		delay_1ms(1500);
		// PF6输出高电平熄灭红LED
		*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 6);
		delay_1ms(1500);
		// PF7输出低电平点亮绿LED
		*((unsigned int *)(0x40021400 + 0x14)) &= ~(1 << 7);
		delay_1ms(1500);
		// PF7输出高电平熄灭绿LED
		*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 7);
		delay_1ms(1500);
		// PF8输出低电平点亮蓝LED
		*((unsigned int *)(0x40021400 + 0x14)) &= ~(1 << 8);
		delay_1ms(1500);
		// PF8输出高电平熄灭蓝LED
		*((unsigned int *)(0x40021400 + 0x14)) |= (1 << 8);
//		delay_1ms(1500);
	}
}
// 1.其他两个灯点亮
// 2.三个灯闪烁
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
