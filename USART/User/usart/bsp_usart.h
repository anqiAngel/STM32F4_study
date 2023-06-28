#ifndef _BSP_USART_H
#define _BSP_USART_H
#include "stm32f4xx.h"
#include <stdio.h>
static void NVIC_Configuration(void);
void Usart_Init(void);
void Usart_Send_Byte(USART_TypeDef *USARTx, uint8_t ch);
void Usart_Send_String(USART_TypeDef *USARTx, char *str);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void Show_Message(void);
#endif
