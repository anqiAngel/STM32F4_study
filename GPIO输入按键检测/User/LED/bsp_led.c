// bsp board support package �弶֧�ְ�
#include "bsp_led.h"
// GPIO���ú���
void LED_GPIO_Config(void){
    /*�����ĸ������ʺ����е�����ĳ�ʼ��*/

    /*��һ��:�������ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    /*�ڶ���:����һ��GPIO��ʼ���ṹ��*/
    GPIO_InitTypeDef GPIO_InitStruct;
    /*������:����GPIO��ʼ���ṹ��ĳ�Ա*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    /*���Ĳ�:����GPIO��ʼ������,�����úõĽṹ��ĳ�Ա����д��Ĵ���*/
    GPIO_Init(GPIOF, &GPIO_InitStruct);

}
