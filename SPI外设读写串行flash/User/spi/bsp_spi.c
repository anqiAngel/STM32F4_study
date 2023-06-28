#include "bsp_spi.h"

// ��ʼ��SPI����ʹ�õ�GPIO
void SPI_GPIO_Config(void)
{
    // GPIO��ʼ���ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;
    // �����ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOG, ENABLE);
    // GPIO��������
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
    // GPIO�������
    // PB3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // PB4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // PB5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // PG6 Ƭѡ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

// SPIģʽ����
void SPI_Mode_Config(void)
{
    // SPI��ʼ���ṹ��
    SPI_InitTypeDef SPI_InitStructure;
    // �����ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    // SPI�������
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CRCPolynomial = 0;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
}

// SPI��дflash��ʼ������
void SPI_FLASH_Init(void)
{
    SPI_GPIO_Config();
    SPI_Mode_Config();
}

uint32_t TIMEOUT = 0;
// SPIд�뵥���ַ�
uint8_t SPI_Write_Byte(uint8_t data)
{
    // ��⴫��λTXE
    // TXEΪ1Ϊ��
    uint8_t recv_data = 0;
    TIMEOUT = 0xffff;
    while (!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE))
    {
        /* code */
        TIMEOUT--;
        if (TIMEOUT == 0)
        {
            /* code */
            return error_callback(1);
        }
    }
    SPI_I2S_SendData(SPI1, data);
    // ͬʱ��
    // �����շǿ�λRXNE
    // RXNEΪ1Ϊ�ǿ�
    TIMEOUT = 0xffff;
    while (!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
    {
        /* code */
        TIMEOUT--;
        if (TIMEOUT == 0)
        {
            /* code */
            return error_callback(2);
        }
    }
    recv_data = SPI_I2S_ReceiveData(SPI1);
    return recv_data;
}

// ��flash��ID
uint8_t SPI_FLASH_Read_ID(void)
{
    // ѡ��flash ����CS
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    // ָ��
    SPI_Write_Byte(0xAB);
    // dummy
    SPI_Write_Byte(0xFF);
    SPI_Write_Byte(0xFF);
    SPI_Write_Byte(0xFF);
    // ��ȡ
    uint8_t recv_data = SPI_Write_Byte(0xFF);
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
    return recv_data;
}

// ����flash ����sector 4kB
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
    // flashдʹ��
    SPI_Write_Enable();
    // ѡ��flash ����CS
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    // ָ��
    SPI_Write_Byte(0x20);
    // �����η���������ַ
    SPI_Write_Byte(addr >> 16);
    SPI_Write_Byte(addr >> 8);
    SPI_Write_Byte(addr);
    // ѡ��flash ����CS
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
    FLASH_Wait_Busy();
}

// flashдʹ��
void SPI_Write_Enable(void)
{
    // ѡ��flash ����CS
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    SPI_Write_Byte(0x06);
    // ѡ��flash ����CS
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

// ��ȡbusyλ Ϊ0����
void FLASH_Wait_Busy(void)
{
    // ѡ��flash ����CS
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    uint8_t recv_data = SPI_Write_Byte(0x05);
    TIMEOUT = 0xffff;
    // �ж�busyλ Ϊ1������ Ϊ0����
    while (1)
    {
        /* code */
        recv_data = SPI_Write_Byte(0xff);
        if (!(recv_data & 0x01))
        {
            break;
        }
        if ((TIMEOUT--) == 0)
        {
            /* code */
            error_callback(3);
            break;
        }
    }
    // ѡ��flash ����CS
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

// ��flash��
void SPI_FLASH_Read_Data(uint32_t addr, uint8_t *data, uint16_t size)
{
    // ѡ��flash ����CS
    GPIO_ResetBits(GPIOG, GPIO_Pin_6);
    // ָ��
    SPI_Write_Byte(0x03);
    // �����η���������ַ
    SPI_Write_Byte(addr >> 16);
    SPI_Write_Byte(addr >> 8);
    SPI_Write_Byte(addr);
    // ��ȡ
    for (int i = 0; i < size; i++)
    {
        /* code */
        *(data + i) = SPI_Write_Byte(0xFF);
    }
    // ѡ��flash ����CS
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

// ���ٶ�flash
void SPI_FLASH_Fast_Read(uint32_t addr)
{
}

// д�����ݵ�flash
void SPI_FLASH_Page_Program(uint32_t addr, uint8_t *buf, uint16_t size)
{
    for (int i = 0; i < size; i++)
    {
        /* code */
        if (i % 256 == 0)
        {
            /* code */
            if (i != 0)
            {
                /* code */
                addr += 256;
            }
            // ѡ��flash ����CS
            GPIO_SetBits(GPIOG, GPIO_Pin_6);
            FLASH_Wait_Busy();
            // flashдʹ��
            SPI_Write_Enable();
            // ѡ��flash ����CS
            GPIO_ResetBits(GPIOG, GPIO_Pin_6);
            // ָ��
            SPI_Write_Byte(0x02);
            // �����η���������ַ
            SPI_Write_Byte(addr >> 16);
            SPI_Write_Byte(addr >> 8);
            SPI_Write_Byte(addr);
        }
        SPI_Write_Byte(*(buf + i));
    }
    // ѡ��flash ����CS
    GPIO_SetBits(GPIOG, GPIO_Pin_6);
    FLASH_Wait_Busy();
}

// ���������Ϣ����
uint8_t error_callback(uint8_t error)
{
    printf("ERROR:%d\n", error);
    return error;
}
