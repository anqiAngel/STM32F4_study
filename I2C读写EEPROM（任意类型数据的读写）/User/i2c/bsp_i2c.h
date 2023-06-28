#ifndef __BSP_I2C_H
#define __BSP_I2C_H
#include "stm32f4xx.h"
#include <stdio.h>
void EEPROM_I2C_Config(void);
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data);
uint8_t EEPROM_Random_Read(uint8_t addr,uint8_t* data);
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t* data,uint8_t size);
uint8_t EEPROM_Sequential_Read(uint8_t addr, uint8_t *rdata, uint16_t size);
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size);
uint8_t Wait_For_Standby(void);
uint8_t Error_Callback(uint8_t code);
#endif
