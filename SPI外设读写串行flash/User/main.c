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
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi.h"

void Delay(__IO u32 nCount); 

uint8_t write_buf[4096] = {0};
uint8_t read_buf[4096] = {0};

/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{
  /* LED 端口初始化 */
  // 写之前必须先擦除
  LED_GPIO_Config();
  Usart_Init();
  SPI_FLASH_Init();
  uint8_t recv_data = SPI_FLASH_Read_ID();
  printf("flash ID: 0x%02x\n", recv_data);
  SPI_FLASH_Erase_Sector(0);
  printf("擦除完成!!!\n");
  for (int i = 0; i < 4096; i++)
  {
    /* code */
    write_buf[i] = 0x55;
  }
  SPI_FLASH_Page_Program(10, write_buf, 4096);
  SPI_FLASH_Read_Data(0, read_buf,4096);
  for (int i = 0; i < 4096; i++)
  {
    /* code */
    printf("0x%02x ", read_buf[i]);
  }
  LED_RED;
  while (1)
  {
    
  }
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
