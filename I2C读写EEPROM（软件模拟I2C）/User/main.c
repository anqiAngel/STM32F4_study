/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   读写EEPROM
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"

#define  EEP_Firstpage      0x00
uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];
uint8_t I2C_Test(void);
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  LED_GPIO_Config();
	
	LED_BLUE;
  /*初始化USART1*/
	Usart_Init(); 

	printf("欢迎使用野火STM32F407开发板。\n");		 
	printf("这是一个I2C外设(AT24C02)读写测试例程\n");

	if(ee_Test() == 1)
	{
		LED_GREEN;
	}
	else
	{
			LED_RED;
	}
  
  while (1)
  {      
  }  

}
/*********************************************END OF FILE**********************/

