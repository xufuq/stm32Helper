

//ͷ�ļ�
#include "stm32f10x.h"
#include "headfile.h"
#include "uart.h"
#include "JLU.h"
#include "string.h"
//��������
 unsigned char ch[2] = {0xfe,0x09};
 unsigned char dat1[16]={0x01,0x34,0x56,0x78,1,1,1,1,1,1,1,1,0x01,0x01,0x01,0x01};
 unsigned char dat2[16]={0};
 extern unsigned char SN[4]; //����
 extern u8 KEY[6];
 unsigned char m=0;
 unsigned char buffer[8];
//=============================================================================
//�ļ����ƣ�Delay
//���ܸ�Ҫ����ʱ
//����˵����nCount����ʱ����
//�������أ���
//=============================================================================

void Delay(uint32_t nCount)
{
    int i=0,j=0;
    for(i=0;i<nCount;i++)
    for(j=0;j<1000;j++);
}


//=============================================================================
//�ļ����ƣ�main
//���ܸ�Ҫ��������
//����˵������
//�������أ�int
//=============================================================================
int main(void)
{    
    int jj=0;
    int i=0,j=0;
    char text[]="======This is the first test APP code for the stm32 OTA=======";
    char text1[]="======you can change the APP code to what you want============";
    char text2[]="========================2021.04===============================";
    int strlength;
    NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x3000);
    uart_init(115200);
    
    strlength=strlen(text);
    for(i=0;i<strlength;i++)
    {
        uart_putchar(USART1,text[i]);
    }
    strlength=strlen(text1);
    for(i=0;i<strlength;i++)
    {
        uart_putchar(USART1,text1[i]);
    }
    strlength=strlen(text2);
    for(i=0;i<strlength;i++)
    {
        uart_putchar(USART1,text2[i]);
    }
        
    // uart_putchar(USART1,'A');
    Delay1(10);
    // uart_putchar(USART1,'B');
    Delay(10);

    Delay(10);

    


}

