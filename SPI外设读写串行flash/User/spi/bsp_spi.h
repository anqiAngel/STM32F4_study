#ifndef _bsp_spi_H
#define _bsp_spi_H
#include "stm32f4xx.h"
#include <stdio.h>
void SPI_GPIO_Config(void);
void SPI_Mode_Config(void);
void SPI_FLASH_Init(void);
uint8_t SPI_FLASH_Read_ID(void);
void SPI_FLASH_Erase_Sector(uint32_t addr);
void SPI_Write_Enable(void);
void FLASH_Wait_Busy(void);
void SPI_FLASH_Read_Data(uint32_t addr, uint8_t *data, uint16_t size);
void SPI_FLASH_Fast_Read(uint32_t addr);
void SPI_FLASH_Page_Program(uint32_t addr, uint8_t* buf, uint16_t size);
uint8_t error_callback(uint8_t error);
#endif
