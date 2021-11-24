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
* ��16������ͨ��ѹ�����������
* adr:����ͨ����ţ�date������������
* adr:0~15;         date:-32768~32767
*/
void push(unsigned char adr,unsigned int date)
{
  uSendBuf[adr*2]=date/256;
  uSendBuf[adr*2+1]=date%256;
}

/*
* ʾ��������ר�ú���
* pushѹ����������ݺ�ִ�д˺���
* ͼ����ʾ���ܲ���Ҫ
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
* ͼ����ʾ����ר�ú���
* �ɷ��ͻҶ�ͼ��Ͷ�ֵͼ��������
* �Ҷ�ͼ��һ���ֽڴ�1������
* ��ֵͼ��һ���ֽڴ�8������
* �ڷ���һ֡ͼ��֮ǰ��ִ�д˺���
* raw ���˴η���ͼ�����������Ϊ320����ÿ��������ص���
* line���˴η���ͼ�����������Ϊ240����ÿ��������ص���
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
* ͼ����ʾ����ר�ú���
* ��������ͼ����������ѹ�뷢������
* byte_num:�˴η��͵��ֽ���
* buf     :�޷����ַ������飬����������ܳ���256
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
* ͼ����ʾ����ר�ú���
* �ڷ������һ֡ͼ���ִ�д˺���
*/
void push_end(void)
{
  uart_putchar(USART1,37);  
  uart_putchar(USART1,255);
}
