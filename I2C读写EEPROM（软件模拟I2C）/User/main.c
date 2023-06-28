/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��дEEPROM
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  LED_GPIO_Config();
	
	LED_BLUE;
  /*��ʼ��USART1*/
	Usart_Init(); 

	printf("��ӭʹ��Ұ��STM32F407�����塣\n");		 
	printf("����һ��I2C����(AT24C02)��д��������\n");

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

