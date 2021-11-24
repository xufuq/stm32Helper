/*
*   author   : Fuqiang Xu
*   Done date: 2018-11-27
*   e-mail   : 17843124829@163.com
*/

#ifndef __FREECAR_H__
#define __FREECAR_H__
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"


void Delay1(uint32_t nCount);
void uart_putchar(USART_TypeDef* USARTx,unsigned char Data);
void push(unsigned char adr,unsigned int date);
void uSendOnePage(void);
void push_head(unsigned int raw,unsigned int line);
void push_in_data(int byte_num,unsigned char *buf);
void push_end(void);






#endif 
