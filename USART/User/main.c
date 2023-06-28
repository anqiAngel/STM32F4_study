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
#include "./led/bsp_led.h"
#include "bsp_usart.h"
#include <stdio.h>

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	LED_GPIO_Config();
	Usart_Init();
	// Usart_Send_Byte(USART1, 'A');
	// printf("STM32����ʵ��\n");
	// Usart_Send_String(USART1,"STM32���ڷ���ʵ��\n");
	Show_Message();
	uint8_t ch;
	while (1)
	{
    ch = getchar();
    printf("������ַ���: %c\n",ch);
    switch (ch)
    {
      case '1':
        /* code */
        LED_RED;
        break;
      case '2':
        /* code */
        LED_GREEN;
        break;
      case '3':
        /* code */
        LED_BLUE;
        break;
      case '4':
        /* code */
        LED_YELLOW;
        break;
      case '5':
        /* code */
        LED_PURPLE;
        break;
      case '6':
        /* code */
        LED_CYAN;
        break;
      case '7':
        /* code */
        LED_WHITE;
        break;
      case '8':
        /* code */
        LED_RGBOFF;
        break;  
      default:
        printf("��������!!!\n");
		Show_Message(); 
    }
	}
}

/*********************************************END OF FILE**********************/

