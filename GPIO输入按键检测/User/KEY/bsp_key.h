#ifndef _BSP_KEY_H
#define _BSP_KEY_H
#include "stm32f4xx.h"
void KEY_GPIO_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
#endif
