#include "spi.h"




/*
//以下是SPI模块的初始化代码，配置成主机模式 						  
//SPI口初始化
//这里针是对SPI1的初始化
void SPI2_Init(void)
{	 
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    
     RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;//sck mosi
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//miso
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//cs
    GPIO_Init(GPIOB,&GPIO_InitStructure);

  SPI_Cmd(SPI2, DISABLE);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;      

  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  SPI_Cmd(SPI2, ENABLE);
    
    
	SPI2_ReadWriteByte(0xff);//启动传输		 
}   
//SPI1速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI2->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI2,ENABLE); //使能SPI1
} 
//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
	
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个byte  数据
		
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据	
 		    
}
*/

//应用模拟spi执行，专一适用于nrf24l01通信模块

void nrf_delay_us(u32 i)
{
u32 temp;
    SysTick->LOAD = 9*i;
    SysTick->CTRL = 0x01;
    SysTick->VAL  = 0;
    do
    {
    temp = SysTick->CTRL;
    }while((temp&0x01)&&(!(temp&(1<<16))));
    SysTick->CTRL = 0;
    SysTick->VAL  = 0;
}


void SPI2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );//PORTB???? 

    // SCK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //A4
    // MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //A5

    // MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //A6

    // CE
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //A7

    // CSN
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //B0
    
    // IRQ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //A6
}

void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
;
} 
//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData,u8 n)//n=0,写数据，n=1，读数据
{		 			 
 	
    u8 counter;
  if(!n)
  {
    for(counter=0;counter<8;counter++)
    {     
            
            nrf_delay_us( 10 );

            NRF_SCK_0 (); //上升沿或下降沿发送

            nrf_delay_us( 10 );
if ( TxData & 0x80 )
                    NRF_MOSI_1 ();
            else 
                    NRF_MOSI_0 ();
            NRF_SCK_1();

            nrf_delay_us( 10 );

            TxData <<= 1; 

    } 
    return 0;
  }
  if(n)
  {
      u8 SPI_Data;


    for(counter=0;counter<8;counter++)
    {
            SPI_Data <<= 1;

            NRF_SCK_0 ();

            nrf_delay_us( 10 );

            

            nrf_delay_us( 10 );

            NRF_SCK_1 ();

            nrf_delay_us( 10 );
if ( NRF_MISO_GET() == 1)//获取引脚当前电平状态
                    SPI_Data |= 0x01;

           nrf_delay_us( 10 );
    }
    return SPI_Data;
  }
    
}

