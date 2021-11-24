
/******************** (C) COPYRIGHT  ��˼���ܵ��ӹ����� ********************
 * �ļ���  	��main.c
 * ����    	  	��
 * ��汾  	��V3.5
 * ����    		��	zxb  
 *�޸�ʱ�� 	��2014-6-04
**********************************************************************************/
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"

//ָʾ��
#define 	LED1_PORT	GPIOB
#define 	LED1_PIN	GPIO_Pin_10
#define 	LED1		0x01

#define 	OUT_PUT	1
#define 	IN_PUT		0

/************************************************************************
* ������ :UserDelay(uint32_t time_ms)
* ����   :��ʱ����
* ����   ��uint32_t time_ms
* ���   ����
* ����   ����
************************************************************************/
void UserDelay(uint32_t times)
{
    while(times--)
    {
        uint32_t i;
        for (i=0; i<0xffff; i++)
            ;
    }
}

/************************************************************************
* ������ 	:LED_Blink(UINT8 ledNum)
* ����   	:Led��ת 
* ����   	:uint32_t time_ms
* ���   	:��
* ����   	:��
************************************************************************/
void LED_Blink(uint8_t ledNum)
{
    uint8_t cnt=2;
    
    if(ledNum == LED1)
    {
        while(cnt--)
        {
            LED1_PORT->ODR ^= LED1_PIN;            
            UserDelay(40);
        }
    }
}

/************************************************************************
* ������	:GPIO_InitIO (GPIO_TypeDef* GpioID,int data,uint16_t GPIO_Pin)
* ����   	:��ʼ��IO 
* ����   	:0:����SDAΪ���룬�ر�����
			 1:����SDAΪ���
* ���  	:��
* ����   	:��
************************************************************************/
void GPIO_InitIO (GPIO_TypeDef* GpioID,int data,uint16_t GPIO_Pin)
 {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    if(data)
    {
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    } 	
    else
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    }
    GPIO_Init(GpioID,&GPIO_InitStructure);
 }

void RCC_Configuration(void)
{ 
    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_OFF);

    RCC_HSICmd(ENABLE);  //���ڲ�ʱ��

    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)        
    {
        ;
    }
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    //APB2
    RCC_PCLK2Config(RCC_HCLK_Div1);
    //APB1
    RCC_PCLK1Config(RCC_HCLK_Div2);
    
    //PLL ��Ƶ
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);        //�ڲ�ʱ�ӱ�Ƶ4*12
    
    RCC_PLLCmd(ENABLE);                        //ʹ�ܱ�Ƶ

    //�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
        ;
    }

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    
/***************************************************************************
    ��ȡRCC����Ϣ,������
    ��ο�RCC_ClocksTypeDef�ṹ�������,��ʱ��������ɺ�,
    ���������ֵ��ֱ�ӷ�ӳ�������������ֵ�����Ƶ��
****************************************************************************/
    while(RCC_GetSYSCLKSource() != 0x08)
    {
        ;
    }
    
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000);
    
    //ϵͳʱ�ӳ�ʼ��
    RCC_Configuration();

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);

    //��ʼ��LED1 
    GPIO_InitIO(LED1_PORT,OUT_PUT,LED1_PIN);


    while(1)
    {
        LED_Blink(LED1);
        UserDelay(20);
    }

}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1)
  {
	  
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
