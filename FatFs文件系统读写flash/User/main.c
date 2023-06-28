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
#include "ff.h"
#include "string.h"

FATFS fs;
uint8_t res;
FIL fil;
UINT bw;
uint8_t read_buff[100];
/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{
  /* LED 端口初始化 */
  LED_GPIO_Config();
  Usart_Init();
  res = f_mount(&fs, "1:", 1);
  printf("f_mount res: %d\n", res);
  if (res == FR_NO_FILESYSTEM)
  {
    /* code */
    // 格式化
    res = f_mkfs("1:", 0, 0);
    printf("f_mkfs res: %d\n", res);
    // 格式化后重新挂载文件系统
    res = f_mount(NULL, "1:", 1);
    res = f_mount(&fs, "1:", 1);
  }
  res = f_open(&fil, "1:mes.txt", FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
  printf("f_open res: %d\n", res);
  res = f_write(&fil, "文件系统读写flash实验", strlen("文件系统读写flash实验") + 1, &bw);
  printf("f_write res: %d\n", res);
  res = f_close(&fil);
  printf("f_close res: %d\n", res);
  res = f_open(&fil, "1:mes.txt", FA_OPEN_EXISTING | FA_READ);
  printf("f_open res: %d\n", res);
  res = f_read(&fil, read_buff, sizeof("文件系统读写flash实验"), &bw);
  printf("f_read res: %d\n", res);
  printf("读取出来的数据->%s\n", read_buff);
  res = f_close(&fil);
  printf("f_close res: %d\n", res);
  while (1)
  {
  }
}

/*********************************************END OF FILE**********************/
