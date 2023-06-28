#include "bsp_usart.h"

// ������Ҫ�ж�
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Ƕ�������жϿ�������ѡ�� */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* ���� USART Ϊ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    /* �������ȼ�Ϊ 1 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* �����ȼ�Ϊ 1 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* ʹ���ж� */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* ��ʼ������ NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

// ���ڳ�ʼ��
void Usart_Init(void)
{
    /*1.��ʼ��������Ҫ��GPIO*/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOA, ENABLE);
    /*GPIO��ʼ��*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*����TX���Ÿ���*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*GPIO���帴��ʲô����*/
    /*����PXx��USARTx_Tx*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    /*����PXx��USARTx_Rx*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    /*2.���ô��ڳ�ʼ���ṹ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    /*3.���ô��ڵĽ����ж�*/
    // NVIC_Configuration();
    // USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /*4.ʹ�ܴ���*/
    USART_Cmd(USART1, ENABLE);
}

// ���ڷ���һ���ֽ�
void Usart_Send_Byte(USART_TypeDef *USARTx, uint8_t ch)
{
    USART_SendData(USARTx, ch);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

// ���ڷ����ַ���
void Usart_Send_String(USART_TypeDef *USARTx, char *str)
{
    uint32_t i = 0;
    while (*(str + i) != '\0')
    {
        /* code */
        Usart_Send_Byte(USARTx, *(str + i));
        i++;
    }
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}
// ��дfputc���� ��printf�����ض��򵽴���
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}

// ��дfgetc���� ��scanf��getchar�����ض��򵽴���
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(USART1);
}

// ���Ͳ˵���Ϣ
void Show_Message(void){
	
    printf("   ����ָ�����RGB��ʵ�� \n");
    printf("ʹ�õ�USART1����Ϊ: 115200 8-N-1 \n");
    printf("ָ��-----------------�ʵ���ɫ\n");
    printf("  1--------------------�� \n");
    printf("  2--------------------�� \n");
    printf("  3--------------------�� \n");
    printf("  4--------------------�� \n");
    printf("  5--------------------�� \n");
    printf("  6--------------------�� \n");
    printf("  7--------------------�� \n");
    printf("  8--------------------�� \n");
}
