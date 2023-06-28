#include "bsp_key.h"
// GPIO配置函数
void KEY_GPIO_Config(void){
    /*以下四个步骤适合所有的外设的初始化*/
    /*第一步:开外设的时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /*第二步:定义一个GPIO初始化结构体*/
    GPIO_InitTypeDef GPIO_InitStruct;
    /*第三步:配置GPIO初始化结构体的成员*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    /*第四步:调用GPIO初始化函数,把配置好的结构体的成员参数写入寄存器*/
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin){
    	if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1)
		{
			/* code */
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);
			return 1;
		}
		else
		{
			/* code */
			return 0;
		}
}
