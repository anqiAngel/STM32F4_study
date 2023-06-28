#include "stm32f4xx_gpio.h"

/*GPIO��λ����*/
void GPIO_SetBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRL = GPIO_Pin;
	
}
/*GPIO��λ����*/
void GPIO_ResetBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRH = GPIO_Pin;
}
/*GPIO��ʼ������*/
/**
*�������ܣ���ʼ������ģʽ
*����˵����GPIOx���ò���Ϊ GPIO_TypeDef ���͵�ָ�룬ָ�� GPIO �˿ڵĵ�ַ
* GPIO_InitTypeDef:GPIO_InitTypeDef �ṹ��ָ�룬ָ���ʼ������
*/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	/*-- GPIO Mode Configuration --*/
	for (pinpos = 0x00; pinpos < 16; pinpos++) {
		/*����������Ϊ��ͨ�� GPIO_InitStruct->GPIO_Pin ������ź� 0-15*/
		/*��������� pos �� pinpos λΪ 1������Ϊ 0���� GPIO_Pin_x ���Ӧ��pinpos ����ÿ��ѭ���� 1��*/
		pos = ((uint32_t)0x01) << pinpos;
		/* pos �� GPIO_InitStruct->GPIO_Pin �� & ���㣬�������� currentpin == pos�����ʾ GPIO_InitStruct->GPIO_Pin �� pinpos λҲΪ 1���Ӷ���֪ pinpos ���� GPIO_InitStruct->GPIO_Pin ��Ӧ�����źţ�0-15*/
		currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
		/*currentpin == posʱִ�г�ʼ��*/
		if (currentpin == pos) {
			/*GPIOx �˿ڣ�MODER �Ĵ����� GPIO_InitStruct->GPIO_Pin ��Ӧ�����ţ�MODER λ���*/
			GPIOx->MODER &= ~(3 << (2 *pinpos));
			/*GPIOx �˿ڣ�MODER �Ĵ����� GPIO_Pin ���ţ�MODER λ����"����/���/�������/ģ��"ģʽ*/
			GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 *pinpos));
			/*GPIOx �˿ڣ�PUPDR �Ĵ����� GPIO_Pin ���ţ�PUPDR λ���*/
			GPIOx->PUPDR &= ~(3 << ((2 *pinpos))); 
			/*GPIOx �˿ڣ�PUPDR �Ĵ����� GPIO_Pin ���ţ�PUPDR λ����"��/����"ģʽ*/
			GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 *pinpos)); 
			/*��ģʽΪ"���/�������"ģʽ���������ٶ����������*/
			if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) ||(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)) {
				/*GPIOx �˿ڣ�OSPEEDR �Ĵ����� GPIO_Pin ���ţ�OSPEEDR λ���*/
				GPIOx->OSPEEDR &= ~(3 << (2 *pinpos));
				/*GPIOx �˿ڣ�OSPEEDR �Ĵ����� GPIO_Pin ���ţ�OSPEEDR λ��������ٶ�*/
				GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed)<<(2 *pinpos)); 
				/*GPIOx �˿ڣ�OTYPER �Ĵ����� GPIO_Pin ���ţ�OTYPER λ���*/
				GPIOx->OTYPER &= ~(1 << (pinpos)) ;
				/*GPIOx �˿ڣ�OTYPER λ�Ĵ����� GPIO_Pin ���ţ�OTYPER λ����"����/��©"�������*/
				GPIOx->OTYPER |= (uint16_t)(( GPIO_InitStruct->GPIO_OType)<< (pinpos));
			}
		}
	}
}
