#include "bsp_exti.h"

/*NVIC寄存器配置*/
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    /*配置NVIC为优先级组1*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*配置中断源：按键1*/
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    /*配置抢占优先级：1*/
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    /*配置子优先级：1*/
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    /*使能中断通道*/
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    /*配置中断源：按键2*/
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI_Key_Config(void)
{
    /*第一步：初始化需要连接到EXTI线的GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
	/*开启中断相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE); 
	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	/*设置引脚模式为输入模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    /*设置引脚不上拉也不下拉*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /*第二步：初始化EXTI*/
    // 使能SYSCFG时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
    // 连接EXTI中断源
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
    /*第三步：配置NVIC*/
    NVIC_Configuration();
    /*第四步：在stm32fxx_it.c中编写中断服务函数*/
    
}
