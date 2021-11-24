
/******************** (C) COPYRIGHT  飞思智能电子工作室 ********************
 * 文件名  	：main.c
 * 描述    	  	：
 * 库版本  	：V3.5
 * 作者    		：	zxb  
 *修改时间 	：2014-6-04
**********************************************************************************/
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"

//指示灯
#define 	LED1_PORT	GPIOB
#define 	LED1_PIN	GPIO_Pin_10
#define 	LED1		0x01

#define 	OUT_PUT	1
#define 	IN_PUT		0

/************************************************************************
* 函数名 :UserDelay(uint32_t time_ms)
* 描述   :延时函数
* 输入   ：uint32_t time_ms
* 输出   ：无
* 返回   ：无
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
* 函数名 	:LED_Blink(UINT8 ledNum)
* 描述   	:Led翻转 
* 输入   	:uint32_t time_ms
* 输出   	:无
* 返回   	:无
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
* 函数名	:GPIO_InitIO (GPIO_TypeDef* GpioID,int data,uint16_t GPIO_Pin)
* 描述   	:初始化IO 
* 输入   	:0:设置SDA为输入，关闭下拉
			 1:设置SDA为输出
* 输出  	:无
* 返回   	:无
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

    RCC_HSICmd(ENABLE);  //打开内部时钟

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
    
    //PLL 倍频
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);        //内部时钟倍频4*12
    
    RCC_PLLCmd(ENABLE);                        //使能倍频

    //等待指定的 RCC 标志位设置成功 等待PLL初始化成功
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
        ;
    }

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    
/***************************************************************************
    获取RCC的信息,调试用
    请参考RCC_ClocksTypeDef结构体的内容,当时钟配置完成后,
    里面变量的值就直接反映了器件各个部分的运行频率
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
    
    //系统时钟初始化
    RCC_Configuration();

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);

    //初始化LED1 
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
