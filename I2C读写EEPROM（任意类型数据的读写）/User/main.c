
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"
#define MAXSIZE 256

void Delay(__IO u32 nCount); 

int main(void)
{

  uint8_t data[MAXSIZE] = {0};
  uint8_t rdata[MAXSIZE] = {0};
  for (uint16_t i = 0; i < MAXSIZE; i++)
  {
    /* code */
    data[i] = i;
  }
	Usart_Init();
	EEPROM_I2C_Config();
  while (1)
	{

	}
}

void Delay(__IO uint32_t nCount)	 //??????????
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

