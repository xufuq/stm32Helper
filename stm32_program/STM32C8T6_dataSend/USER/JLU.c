/*
*   author   : Fuqiang Xu
*   Done date: 2018-11-27
*   e-mail   : 17843124829@163.com
*/

#include "JLU.h"

unsigned char uSendBuf[32]={0};

void Delay1(uint32_t nCount)
{
    int i=0,j=0;
    for(i=0;i<nCount;i++)
    for(j=0;j<1000;j++);
}

void uart_putchar(USART_TypeDef* USARTx,unsigned char Data)
{
    USART_SendData(USARTx, Data);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}

/*
* 向16个数据通道压入待发送数据
* adr:数据通道序号；date：待发送数据
* adr:0~15;         date:-32768~32767
*/
void push(unsigned char adr,unsigned int date)
{
  uSendBuf[adr*2]=date/256;
  uSendBuf[adr*2+1]=date%256;
}

/*
* 示波器功能专用函数
* push压入待发送数据后执行此函数
* 图像显示功能不需要
*/
void uSendOnePage(void)
{
  unsigned char i; 
  uart_putchar(USART1,255);
    Delay1(0);
  uart_putchar(USART1,37);
  for(i=0;i<16;i++)
  {
    uart_putchar(USART1, uSendBuf[i*2]);
    Delay1(0);
    uart_putchar(USART1, uSendBuf[i*2+1]);
    Delay1(0);  
  }
  uart_putchar(USART1,37);
  Delay1(0);
  uart_putchar(USART1,255);
  
}

/*
* 图像显示功能专用函数
* 可发送灰度图像和二值图像两个种
* 灰度图像一个字节存1个像素
* 二值图像一个字节存8个像素
* 在发送一帧图像之前先执行此函数
* raw ：此次发送图像行数，最大为320，即每列最多像素点数
* line：此次发送图像列数，最大为240，即每行最多像素点数
*/
void push_head(unsigned int raw,unsigned int line)
{
  int i=0;
  uart_putchar(USART1,255);
  uart_putchar(USART1,37);
  uart_putchar(USART1,(unsigned char)((raw/10)&0xff));
  uart_putchar(USART1,(unsigned char)((line/10)&0xff));
  for(i=0;i<32;i++)
  {
      uart_putchar(USART1,uSendBuf[i]);
  }
}

/*
* 图像显示功能专用函数
* 按照需求将图像数据依次压入发送序列
* byte_num:此次发送的字节数
* buf     :无符号字符型数组，最大容量不能超过256
*/
void push_in_data(int byte_num,unsigned char *buf)
{
    int i=0;
  for(i=0;i<byte_num;i++)
    {
        uart_putchar(USART1,(buf[i]&0xff));
    } 
}

/*
* 图像显示功能专用函数
* 在发送完成一帧图像后执行此函数
*/
void push_end(void)
{
  uart_putchar(USART1,37);  
  uart_putchar(USART1,255);
}
