#include "bsp_usart.h"

// 接收需要中断
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* 嵌套向量中断控制器组选择 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* 配置 USART 为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    /* 抢断优先级为 1 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* 子优先级为 1 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* 使能中断 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* 初始化配置 NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

// 串口初始化
void Usart_Init(void)
{
    /*1.初始化串口需要的GPIO*/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOA, ENABLE);
    /*GPIO初始化*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*配置TX引脚复用*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*GPIO具体复用什么功能*/
    /*连接PXx到USARTx_Tx*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    /*连接PXx到USARTx_Rx*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    /*2.配置串口初始化结构体*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    /*3.配置串口的接收中断*/
    // NVIC_Configuration();
    // USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /*4.使能串口*/
    USART_Cmd(USART1, ENABLE);
}

// 串口发送一个字节
void Usart_Send_Byte(USART_TypeDef *USARTx, uint8_t ch)
{
    USART_SendData(USARTx, ch);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

// 串口发送字符串
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
// 重写fputc函数 将printf函数重定向到串口
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}

// 重写fgetc函数 将scanf、getchar函数重定向到串口
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(USART1);
}

// 发送菜单信息
void Show_Message(void){
	
    printf("   串口指令控制RGB灯实验 \n");
    printf("使用的USART1参数为: 115200 8-N-1 \n");
    printf("指令-----------------彩灯颜色\n");
    printf("  1--------------------红 \n");
    printf("  2--------------------绿 \n");
    printf("  3--------------------蓝 \n");
    printf("  4--------------------黄 \n");
    printf("  5--------------------紫 \n");
    printf("  6--------------------青 \n");
    printf("  7--------------------白 \n");
    printf("  8--------------------灭 \n");
}
