/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   控制多彩流水灯
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
#define MAXSIZE 256

void Delay(__IO u32 nCount); 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
//	uint8_t rdata = 0; 
//	uint8_t data[10] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10};
//	uint8_t rdata[10] = {0};
  uint8_t data[MAXSIZE] = {0};
  uint8_t rdata[MAXSIZE] = {0};
  // 初始0-255 256个数的数组
  for (uint16_t i = 0; i < MAXSIZE; i++)
  {
    /* code */
    data[i] = i;
  }
	Usart_Init();
	printf("这是一个EEPROM读写实验\n");
	EEPROM_I2C_Config();
	// 写入
	// EEPROM_Byte_Write(0x00, 0x12);
	// Wait_For_Standby();
	// Delay(0xffff);
	// EEPROM_Random_Read(0x00,&rdata);
  // printf("读写测试结束, rdata=0x%x\n",rdata);
	// EEPROM_Page_Write(0x00,data,10);
	EEPROM_Buffer_Write(0x00, data, MAXSIZE);
	EEPROM_Sequential_Read(0x00,rdata,MAXSIZE);
  // EEPROM_Buffer_Write(0x01, data, 200);
	// EEPROM_Sequential_Read(0x01,rdata,200);
	for (uint16_t i = 0; i < 256; i++)
	{
		/* code */
		printf("0x%02x ",rdata[i]);
	}
  printf("\n");
//  EEPROM_Random_Read(0x05,&rdata);
//  printf("读写测试结束, rdata=0x0%x\n",rdata);
	printf("读写测试结束!!!\n");
  while (1)
	{

	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

