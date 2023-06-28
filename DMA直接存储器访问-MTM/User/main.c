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
#include "bsp_dma.h"

// 将变量定义在flash中使用const
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  /* 定义存放比较结果变量 */
  uint8_t TransferStatus;
  
	/* LED 端口初始化 */
	LED_GPIO_Config();
    
  /* 设置RGB彩色灯为紫色 */
  LED_PURPLE;  
  
  /* 简单延时函数 */
  Delay(0xFFFFFF);  
  
  /* DMA传输配置 */
  DMA_Config(); 
  
  /* 等待DMA传输完成 */
  while(DMA_GetFlagStatus(DMA_STREAM,DMA_FLAG_TCIF)==DISABLE)
  {
    
  }   
  
  /* 比较源数据与传输后数据 */
  TransferStatus=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
  
  /* 判断源数据与传输后数据比较结果*/
  if(TransferStatus==0)  
  {
    /* 源数据与传输后数据不相等时RGB彩色灯显示红色 */
    LED_RED;
  }
  else
  { 
    /* 源数据与传输后数据相等时RGB彩色灯显示蓝色 */
    LED_BLUE;
  }

	while (1)
	{		
	}
}

/*********************************************END OF FILE**********************/

