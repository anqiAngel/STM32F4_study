#include "bsp_i2c.h"

#define TIME_OUT 0x000FFFFF
uint32_t count_wait = TIME_OUT;
// 硬件I2C实现(不是软件模拟I2C)
// 通过标准库的库函数组合实现
void EEPROM_I2C_Config(void)
{
    /*1.初始化串口需要的GPIO*/
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOB, ENABLE);
    /*GPIO具体复用什么功能*/
    /*连接PXx到I2C*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
    /*连接PXx到I2C*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
    /*GPIO初始化*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*配置I2C引脚复用*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /*2.配置I2C初始化结构体*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_Init(I2C1, &I2C_InitStructure);
    /*4.使能I2C*/
    I2C_Cmd(I2C1, ENABLE);
}

// 向EEPROM写一个字节
// addr 要写入的存储单元格地址
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
    // 1.起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // 等待事件5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(1);
        }
    }
    // 2.发送设备地址和传输方向
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // 等待事件6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(2);
        }
    }
    // 3.发送内存单元地址
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // 等待事件8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(3);
        }
    }
    // 4.发送一字节的数据
    I2C_SendData(I2C1, data);
    count_wait = TIME_OUT;
    // 等待事件8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(4);
        }
    }
    // 5.停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
    Wait_For_Standby();
    return 0;
}

// 从EEPROM读一个字节
// addr 要读出的存储单元格地址
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
    // 1.起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // 等待事件5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(5);
        }
    }
    // 2.发送设备地址和传输方向
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // 等待事件6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(6);
        }
    }
    // 3.发送要读取的内存单元地址
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // 等待事件8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(7);
        }
    }
    /*--------------------------------------第二次起始信号-------------------------------------------*/
    // 4.起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // 等待事件5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(8);
        }
    }
    // 5.发送设备地址和传输方向
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Receiver);
    count_wait = TIME_OUT;
    // 等待事件6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(9);
        }
    }
    // 主机NACK
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    count_wait = TIME_OUT;
    // 等待事件7
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(10);
        }
    }
    // 6.接收一字节的数据
    *data = I2C_ReceiveData(I2C1);
    // 7.停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
    return 0;
}

// EEPROM页写入
// addr 要写入的首地址 data 要写入数据的数组指针 size 写入个数(小于等于8)
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size)
{
    // 1.起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // 等待事件5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(1);
        }
    }
    // 2.发送设备地址和传输方向
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // 等待事件6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(2);
        }
    }
    // 3.发送内存单元地址
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // 等待事件8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(3);
        }
    }
    for (int i = 0; i < size; i++)
    {
        /* code */
        // 4.发送一字节的数据
        I2C_SendData(I2C1, *(data + i));
        count_wait = TIME_OUT;
        // 等待事件8_2
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
        {
            count_wait--;
            if (count_wait == 0)
            {
                /* code */
                return Error_Callback(4);
            }
        }
    }
    // 5.停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
    return Wait_For_Standby();
}

// 从EEPROM读取多个字节
// addr 要读出的存储单元格地址 rdata 读取出来的数据 size 读取多少
uint8_t EEPROM_Sequential_Read(uint8_t addr, uint8_t *rdata, uint16_t size)
{
    // 1.起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // 等待事件5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(5);
        }
    }
    // 2.发送设备地址和传输方向
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // 等待事件6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(6);
        }
    }
    // 3.发送要读取的内存单元地址
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // 等待事件8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(7);
        }
    }

    /*--------------------------------------第二次起始信号-------------------------------------------*/
    // 4.起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // 等待事件5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(8);
        }
    }
    // 5.发送设备地址和传输方向
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Receiver);
    count_wait = TIME_OUT;
    // 等待事件6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(9);
        }
    }
    for (int i = 0; i < size; i++)
    {
        /* code */
        if (i == size - 1)
        {
            /* code */
            // 主机NACK
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }
        else
        {
            /* code */
            // 主机ACK
            I2C_AcknowledgeConfig(I2C1, ENABLE);
        }
        count_wait = TIME_OUT;
        // 等待事件7
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR)
        {
            count_wait--;
            if (count_wait == 0)
            {
                /* code */
                return Error_Callback(10);
            }
        }
        // 收到之后再开始写
        *(rdata + i) = I2C_ReceiveData(I2C1);
    }
    // 7.停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);
    return 0;
}

// EEPROM写入
// addr 要写入的首地址 data 要写入数据的数组指针 size 写入个数(长度没有限制)
// 需要注意地址对齐 addr % 8 != 0会出错
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size)
{
    // 页数
    uint8_t page_num = size / 8;
    // 单数(不足一页的块数)
    uint8_t single_num = size % 8;
    // addr对齐
    if (addr % 8 == 0)
    {
        /* code */
        for (int i = 0; i < page_num; i++)
        {
            /* code */
            EEPROM_Page_Write(addr + i * 8, data + i * 8, 8);
        }
        EEPROM_Page_Write(addr + page_num * 8, data + page_num * 8, single_num);
        return 0;
    }
    else // addr不对齐
    {
        /* code */
        // 本行剩余多少个存储单元
        uint8_t single_addr = 8 - addr % 8;
        // 1.写入剩余的存储单元
        EEPROM_Page_Write(addr, data, single_addr);
        // 2.从头开始写入 递归
        EEPROM_Buffer_Write(addr + single_addr, data + single_addr, size - single_addr);
        return 0;
    }
}

// 等待EEPROM内部写入操作完成
uint8_t Wait_For_Standby(void)
{
    uint32_t check_count = 0xFFFFF;
    while (check_count--)
    {
        /* code */
        // 1.起始信号
        I2C_GenerateSTART(I2C1, ENABLE);
        count_wait = TIME_OUT;
        // 等待事件5
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
        {
            count_wait--;
            if (count_wait == 0)
            {
                /* code */
                return Error_Callback(11);
            }
        }
        // 2.发送设备地址和传输方向
        I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
        count_wait = TIME_OUT;
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
        {
            count_wait--;
            if (count_wait == 0)
            {
                /* code */
                break;
            }
        }
        // 说明EEPROM已经写入完毕
        if (count_wait != 0)
        {
            /* code */
            // 停止本次通讯
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 0;
        }
    }
    // 停止本次通讯
    I2C_GenerateSTOP(I2C1, ENABLE);
    return 1;
}

// 打印错误代码函数
uint8_t Error_Callback(uint8_t code)
{
    printf("\r\nError: %d\r\n", code);
    return code;
}
