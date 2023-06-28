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
#include "ff.h"
#include "string.h"

FATFS fs;
uint8_t res;
FIL fil;
UINT bw;
uint8_t read_buff[100];
/**
 * @brief  ������
 * @param  ��
 * @retval ��
 */
int main(void)
{
  /* LED �˿ڳ�ʼ�� */
  LED_GPIO_Config();
  Usart_Init();
  res = f_mount(&fs, "1:", 1);
  printf("f_mount res: %d\n", res);
  if (res == FR_NO_FILESYSTEM)
  {
    /* code */
    // ��ʽ��
    res = f_mkfs("1:", 0, 0);
    printf("f_mkfs res: %d\n", res);
    // ��ʽ�������¹����ļ�ϵͳ
    res = f_mount(NULL, "1:", 1);
    res = f_mount(&fs, "1:", 1);
  }
  res = f_open(&fil, "1:mes.txt", FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
  printf("f_open res: %d\n", res);
  res = f_write(&fil, "�ļ�ϵͳ��дflashʵ��", strlen("�ļ�ϵͳ��дflashʵ��") + 1, &bw);
  printf("f_write res: %d\n", res);
  res = f_close(&fil);
  printf("f_close res: %d\n", res);
  res = f_open(&fil, "1:mes.txt", FA_OPEN_EXISTING | FA_READ);
  printf("f_open res: %d\n", res);
  res = f_read(&fil, read_buff, sizeof("�ļ�ϵͳ��дflashʵ��"), &bw);
  printf("f_read res: %d\n", res);
  printf("��ȡ����������->%s\n", read_buff);
  res = f_close(&fil);
  printf("f_close res: %d\n", res);
  while (1)
  {
  }
}

/*********************************************END OF FILE**********************/
