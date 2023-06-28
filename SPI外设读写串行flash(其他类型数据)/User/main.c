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

float a = 1.5f;
char *str = "abcd";
float b = 0.0f;
char str1[] = "";
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
  SPI_FLASH_Erase_Sector(0);
  printf("擦除完成!!!\n");
  // 读写小数
  SPI_FLASH_Page_Program(0, (uint8_t *)&a, sizeof(a));
  SPI_FLASH_Read_Data(0, (uint8_t *)&b, sizeof(a));
  printf("%f\n", b);
  SPI_FLASH_Erase_Sector(0);
  printf("擦除完成!!!\n");
  // 读写字符串
  SPI_FLASH_Page_Program(0, (uint8_t *)str, sizeof(str));
  SPI_FLASH_Read_Data(0, (uint8_t *)str1, sizeof(str));
  printf("%s\n", str1);
  LED_RED;
  while (1)
  {
  }
}
/*********************************************END OF FILE**********************/
