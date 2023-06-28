#include "bsp_exti.h"

/*NVIC�Ĵ�������*/
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    /*����NVICΪ���ȼ���1*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*�����ж�Դ������1*/
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    /*������ռ���ȼ���1*/
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    /*���������ȼ���1*/
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    /*ʹ���ж�ͨ��*/
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    /*�����ж�Դ������2*/
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI_Key_Config(void)
{
    /*��һ������ʼ����Ҫ���ӵ�EXTI�ߵ�GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
	/*�����ж���ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE); 
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	/*��������ģʽΪ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    /*�������Ų�����Ҳ������*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /*�ڶ�������ʼ��EXTI*/
    // ʹ��SYSCFGʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
    // ����EXTI�ж�Դ
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    /*������������NVIC*/
    NVIC_Configuration();
    /*���Ĳ�����stm32fxx_it.c�б�д�жϷ�����*/
    
}
