/**
 ******************************************************************************
 * @file    main.c
 * @author  fire
 * @version V1.0
 * @date    2015-xx-xx
 * @brief   ���ƶ����ˮ��
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
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi.h"

float a = 1.5f;
char *str = "abcd";
float b = 0.0f;
char str1[] = "";
/**
 * @brief  ������
 * @param  ��
 * @retval ��
 */
int main(void)
{
  /* LED �˿ڳ�ʼ�� */
  // д֮ǰ�����Ȳ���
  LED_GPIO_Config();
  Usart_Init();
  SPI_FLASH_Init();
  SPI_FLASH_Erase_Sector(0);
  printf("�������!!!\n");
  // ��дС��
  SPI_FLASH_Page_Program(0, (uint8_t *)&a, sizeof(a));
  SPI_FLASH_Read_Data(0, (uint8_t *)&b, sizeof(a));
  printf("%f\n", b);
  SPI_FLASH_Erase_Sector(0);
  printf("�������!!!\n");
  // ��д�ַ���
  SPI_FLASH_Page_Program(0, (uint8_t *)str, sizeof(str));
  SPI_FLASH_Read_Data(0, (uint8_t *)str1, sizeof(str));
  printf("%s\n", str1);
  LED_RED;
  while (1)
  {
  }
}
/*********************************************END OF FILE**********************/
