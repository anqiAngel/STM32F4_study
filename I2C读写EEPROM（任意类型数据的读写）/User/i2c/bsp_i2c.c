#include "bsp_i2c.h"

#define TIME_OUT 0x000FFFFF
uint32_t count_wait = TIME_OUT;
// Ӳ��I2Cʵ��(�������ģ��I2C)
// ͨ����׼��Ŀ⺯�����ʵ��
void EEPROM_I2C_Config(void)
{
    /*1.��ʼ��������Ҫ��GPIO*/
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOB, ENABLE);
    /*GPIO���帴��ʲô����*/
    /*����PXx��I2C*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
    /*����PXx��I2C*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
    /*GPIO��ʼ��*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*����I2C���Ÿ���*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /*2.����I2C��ʼ���ṹ��*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_Init(I2C1, &I2C_InitStructure);
    /*4.ʹ��I2C*/
    I2C_Cmd(I2C1, ENABLE);
}

// ��EEPROMдһ���ֽ�
// addr Ҫд��Ĵ洢��Ԫ���ַ
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
    // 1.��ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(1);
        }
    }
    // 2.�����豸��ַ�ʹ��䷽��
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // �ȴ��¼�6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(2);
        }
    }
    // 3.�����ڴ浥Ԫ��ַ
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // �ȴ��¼�8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(3);
        }
    }
    // 4.����һ�ֽڵ�����
    I2C_SendData(I2C1, data);
    count_wait = TIME_OUT;
    // �ȴ��¼�8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(4);
        }
    }
    // 5.ֹͣ�ź�
    I2C_GenerateSTOP(I2C1, ENABLE);
    Wait_For_Standby();
    return 0;
}

// ��EEPROM��һ���ֽ�
// addr Ҫ�����Ĵ洢��Ԫ���ַ
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
    // 1.��ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(5);
        }
    }
    // 2.�����豸��ַ�ʹ��䷽��
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // �ȴ��¼�6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(6);
        }
    }
    // 3.����Ҫ��ȡ���ڴ浥Ԫ��ַ
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // �ȴ��¼�8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(7);
        }
    }
    /*--------------------------------------�ڶ�����ʼ�ź�-------------------------------------------*/
    // 4.��ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(8);
        }
    }
    // 5.�����豸��ַ�ʹ��䷽��
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Receiver);
    count_wait = TIME_OUT;
    // �ȴ��¼�6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(9);
        }
    }
    // ����NACK
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�7
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(10);
        }
    }
    // 6.����һ�ֽڵ�����
    *data = I2C_ReceiveData(I2C1);
    // 7.ֹͣ�ź�
    I2C_GenerateSTOP(I2C1, ENABLE);
    return 0;
}

// EEPROMҳд��
// addr Ҫд����׵�ַ data Ҫд�����ݵ�����ָ�� size д�����(С�ڵ���8)
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size)
{
    // 1.��ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(1);
        }
    }
    // 2.�����豸��ַ�ʹ��䷽��
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // �ȴ��¼�6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(2);
        }
    }
    // 3.�����ڴ浥Ԫ��ַ
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // �ȴ��¼�8_2
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
        // 4.����һ�ֽڵ�����
        I2C_SendData(I2C1, *(data + i));
        count_wait = TIME_OUT;
        // �ȴ��¼�8_2
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
    // 5.ֹͣ�ź�
    I2C_GenerateSTOP(I2C1, ENABLE);
    return Wait_For_Standby();
}

// ��EEPROM��ȡ����ֽ�
// addr Ҫ�����Ĵ洢��Ԫ���ַ rdata ��ȡ���������� size ��ȡ����
uint8_t EEPROM_Sequential_Read(uint8_t addr, uint8_t *rdata, uint16_t size)
{
    // 1.��ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(5);
        }
    }
    // 2.�����豸��ַ�ʹ��䷽��
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
    count_wait = TIME_OUT;
    // �ȴ��¼�6
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(6);
        }
    }
    // 3.����Ҫ��ȡ���ڴ浥Ԫ��ַ
    I2C_SendData(I2C1, addr);
    count_wait = TIME_OUT;
    // �ȴ��¼�8_2
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(7);
        }
    }

    /*--------------------------------------�ڶ�����ʼ�ź�-------------------------------------------*/
    // 4.��ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    count_wait = TIME_OUT;
    // �ȴ��¼�5
    while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
    {
        count_wait--;
        if (count_wait == 0)
        {
            /* code */
            return Error_Callback(8);
        }
    }
    // 5.�����豸��ַ�ʹ��䷽��
    I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Receiver);
    count_wait = TIME_OUT;
    // �ȴ��¼�6
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
            // ����NACK
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }
        else
        {
            /* code */
            // ����ACK
            I2C_AcknowledgeConfig(I2C1, ENABLE);
        }
        count_wait = TIME_OUT;
        // �ȴ��¼�7
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR)
        {
            count_wait--;
            if (count_wait == 0)
            {
                /* code */
                return Error_Callback(10);
            }
        }
        // �յ�֮���ٿ�ʼд
        *(rdata + i) = I2C_ReceiveData(I2C1);
    }
    // 7.ֹͣ�ź�
    I2C_GenerateSTOP(I2C1, ENABLE);
    return 0;
}

// EEPROMд��
// addr Ҫд����׵�ַ data Ҫд�����ݵ�����ָ�� size д�����(����û������)
// ��Ҫע���ַ���� addr % 8 != 0�����
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size)
{
    // ҳ��
    uint8_t page_num = size / 8;
    // ����(����һҳ�Ŀ���)
    uint8_t single_num = size % 8;
    // addr����
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
    else // addr������
    {
        /* code */
        // ����ʣ����ٸ��洢��Ԫ
        uint8_t single_addr = 8 - addr % 8;
        // 1.д��ʣ��Ĵ洢��Ԫ
        EEPROM_Page_Write(addr, data, single_addr);
        // 2.��ͷ��ʼд�� �ݹ�
        EEPROM_Buffer_Write(addr + single_addr, data + single_addr, size - single_addr);
        return 0;
    }
}

// �ȴ�EEPROM�ڲ�д��������
uint8_t Wait_For_Standby(void)
{
    uint32_t check_count = 0xFFFFF;
    while (check_count--)
    {
        /* code */
        // 1.��ʼ�ź�
        I2C_GenerateSTART(I2C1, ENABLE);
        count_wait = TIME_OUT;
        // �ȴ��¼�5
        while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) == ERROR)
        {
            count_wait--;
            if (count_wait == 0)
            {
                /* code */
                return Error_Callback(11);
            }
        }
        // 2.�����豸��ַ�ʹ��䷽��
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
        // ˵��EEPROM�Ѿ�д�����
        if (count_wait != 0)
        {
            /* code */
            // ֹͣ����ͨѶ
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 0;
        }
    }
    // ֹͣ����ͨѶ
    I2C_GenerateSTOP(I2C1, ENABLE);
    return 1;
}

// ��ӡ������뺯��
uint8_t Error_Callback(uint8_t code)
{
    printf("\r\nError: %d\r\n", code);
    return code;
}
