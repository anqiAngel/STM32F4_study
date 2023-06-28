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
#include "bsp_dma.h"

// ������������flash��ʹ��const
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  /* �����űȽϽ������ */
  uint8_t TransferStatus;
  
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
    
  /* ����RGB��ɫ��Ϊ��ɫ */
  LED_PURPLE;  
  
  /* ����ʱ���� */
  Delay(0xFFFFFF);  
  
  /* DMA�������� */
  DMA_Config(); 
  
  /* �ȴ�DMA������� */
  while(DMA_GetFlagStatus(DMA_STREAM,DMA_FLAG_TCIF)==DISABLE)
  {
    
  }   
  
  /* �Ƚ�Դ�����봫������� */
  TransferStatus=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
  
  /* �ж�Դ�����봫������ݱȽϽ��*/
  if(TransferStatus==0)  
  {
    /* Դ�����봫������ݲ����ʱRGB��ɫ����ʾ��ɫ */
    LED_RED;
  }
  else
  { 
    /* Դ�����봫����������ʱRGB��ɫ����ʾ��ɫ */
    LED_BLUE;
  }

	while (1)
	{		
	}
}

/*********************************************END OF FILE**********************/

