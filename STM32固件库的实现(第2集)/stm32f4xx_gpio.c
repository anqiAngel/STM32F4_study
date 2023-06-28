#include "stm32f4xx_gpio.h"

/*GPIO置位函数*/
void GPIO_SetBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRL = GPIO_Pin;
	
}
/*GPIO复位函数*/
void GPIO_ResetBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRH = GPIO_Pin;
}
/*GPIO初始化函数*/
/**
*函数功能：初始化引脚模式
*参数说明：GPIOx，该参数为 GPIO_TypeDef 类型的指针，指向 GPIO 端口的地址
* GPIO_InitTypeDef:GPIO_InitTypeDef 结构体指针，指向初始化变量
*/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	/*-- GPIO Mode Configuration --*/
	for (pinpos = 0x00; pinpos < 16; pinpos++) {
		/*以下运算是为了通过 GPIO_InitStruct->GPIO_Pin 算出引脚号 0-15*/
		/*经过运算后 pos 的 pinpos 位为 1，其余为 0，与 GPIO_Pin_x 宏对应。pinpos 变量每次循环加 1，*/
		pos = ((uint32_t)0x01) << pinpos;
		/* pos 与 GPIO_InitStruct->GPIO_Pin 做 & 运算，若运算结果 currentpin == pos，则表示 GPIO_InitStruct->GPIO_Pin 的 pinpos 位也为 1，从而可知 pinpos 就是 GPIO_InitStruct->GPIO_Pin 对应的引脚号：0-15*/
		currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
		/*currentpin == pos时执行初始化*/
		if (currentpin == pos) {
			/*GPIOx 端口，MODER 寄存器的 GPIO_InitStruct->GPIO_Pin 对应的引脚，MODER 位清空*/
			GPIOx->MODER &= ~(3 << (2 *pinpos));
			/*GPIOx 端口，MODER 寄存器的 GPIO_Pin 引脚，MODER 位设置"输入/输出/复用输出/模拟"模式*/
			GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 *pinpos));
			/*GPIOx 端口，PUPDR 寄存器的 GPIO_Pin 引脚，PUPDR 位清空*/
			GPIOx->PUPDR &= ~(3 << ((2 *pinpos))); 
			/*GPIOx 端口，PUPDR 寄存器的 GPIO_Pin 引脚，PUPDR 位设置"上/下拉"模式*/
			GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 *pinpos)); 
			/*若模式为"输出/复用输出"模式，则设置速度与输出类型*/
			if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) ||(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)) {
				/*GPIOx 端口，OSPEEDR 寄存器的 GPIO_Pin 引脚，OSPEEDR 位清空*/
				GPIOx->OSPEEDR &= ~(3 << (2 *pinpos));
				/*GPIOx 端口，OSPEEDR 寄存器的 GPIO_Pin 引脚，OSPEEDR 位设置输出速度*/
				GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed)<<(2 *pinpos)); 
				/*GPIOx 端口，OTYPER 寄存器的 GPIO_Pin 引脚，OTYPER 位清空*/
				GPIOx->OTYPER &= ~(1 << (pinpos)) ;
				/*GPIOx 端口，OTYPER 位寄存器的 GPIO_Pin 引脚，OTYPER 位设置"推挽/开漏"输出类型*/
				GPIOx->OTYPER |= (uint16_t)(( GPIO_InitStruct->GPIO_OType)<< (pinpos));
			}
		}
	}
}
