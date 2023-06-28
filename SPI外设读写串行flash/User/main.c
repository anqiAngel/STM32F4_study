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

void Delay(__IO u32 nCount); 

uint8_t write_buf[4096] = {0};
uint8_t read_buf[4096] = {0};

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
  uint8_t recv_data = SPI_FLASH_Read_ID();
  printf("flash ID: 0x%02x\n", recv_data);
  SPI_FLASH_Erase_Sector(0);
  printf("�������!!!\n");
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

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
