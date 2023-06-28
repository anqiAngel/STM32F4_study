#ifndef _STM32F4XX_GPIO_H
#define _STM32F4XX_GPIO_H

#include "stm32f4xx.h"
#define GPIO_Pin0 ((uint16_t)(1<<0))
#define GPIO_Pin1 ((uint16_t)(1<<1))
#define GPIO_Pin2 ((uint16_t)(1<<2))
#define GPIO_Pin3 ((uint16_t)(1<<3))
#define GPIO_Pin4 ((uint16_t)(1<<4))
#define GPIO_Pin5 ((uint16_t)(1<<5))
#define GPIO_Pin6 ((uint16_t)(1<<6))
#define GPIO_Pin7 ((uint16_t)(1<<7))
#define GPIO_Pin8 ((uint16_t)(1<<8))
#define GPIO_Pin9 ((uint16_t)(1<<9))
#define GPIO_Pin10 ((uint16_t)(1<<10))
#define GPIO_Pin11 ((uint16_t)(1<<11))
#define GPIO_Pin12 ((uint16_t)(1<<12))
#define GPIO_Pin13 ((uint16_t)(1<<13))
#define GPIO_Pin14 ((uint16_t)(1<<14))
#define GPIO_Pin15 ((uint16_t)(1<<15))
typedef enum
{
	GPIO_Mode_IN = 0x00, /*!< 输入模式 */
	GPIO_Mode_OUT = 0x01, /*!< 输出模式 */
	GPIO_Mode_AF = 0x02, /*!< 复用模式 */
	GPIO_Mode_AN = 0x03 /*!< 模拟模式 */
} GPIOMode_TypeDef;

typedef enum 
{
	GPIO_OType_PP = 0x00, /*!< 推挽模式 */
	GPIO_OType_OD = 0x01 /*!< 开漏模式 */
} GPIOOType_TypeDef;

typedef enum 
{
	GPIO_Speed_2MHz = 0x00, /*!< 2MHz */
	GPIO_Speed_25MHz = 0x01, /*!< 25MHz */
	GPIO_Speed_50MHz = 0x02, /*!< 50MHz */
	GPIO_Speed_100MHz = 0x03 /*!<100MHz */
} GPIOSpeed_TypeDef;

typedef enum 
{
	GPIO_PuPd_NOPULL = 0x00,/*浮空*/
	GPIO_PuPd_UP = 0x01, /*上拉*/
	GPIO_PuPd_DOWN = 0x02 /*下拉*/
} GPIOPuPd_TypeDef;

/*定义GPIO的初始化结构体*/
typedef struct
{
	uint16_t GPIO_Pin;
	uint32_t GPIO_Mode;
	uint32_t GPIO_PuPd;
	uint32_t GPIO_OType;
	uint32_t GPIO_Speed;
}GPIO_InitTypeDef;

/*函数初始化*/
void GPIO_SetBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
#endif
