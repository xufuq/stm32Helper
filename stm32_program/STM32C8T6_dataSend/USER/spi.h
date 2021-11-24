#ifndef __SPI_H
#define __SPI_H
#include "headfile.h"
#include "stm32f10x.h"


void SPI2_Init(void);			 //��ʼ��SPI1��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData,u8 n);//SPI1���߶�дһ���ֽ�
void nrf_delay_us(u32 i);

#define          NRF_SCK_0()             GPIO_ResetBits( GPIOB, GPIO_Pin_13 )
#define          NRF_SCK_1()             GPIO_SetBits  ( GPIOB, GPIO_Pin_13 )

#define          NRF_MOSI_0()            GPIO_ResetBits( GPIOB, GPIO_Pin_15 )
#define          NRF_MOSI_1()            GPIO_SetBits  ( GPIOB, GPIO_Pin_15 )

#define          NRF_MISO_GET()          GPIO_ReadInputDataBit ( GPIOB, GPIO_Pin_14 )
		 
#endif

