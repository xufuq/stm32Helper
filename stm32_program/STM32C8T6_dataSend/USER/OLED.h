#ifndef _OLED_H
#define _OLED_H

#include "headfile.h"
#include "stm32f10x.h"

#define  OLED_SCL_PIN	GPIO_Pin_12
#define  OLED_SDA_PIN	GPIO_Pin_13
#define  OLED_RST_PIN	GPIO_Pin_14
#define  OLED_DC_PIN	GPIO_Pin_15
#define  OLED_CS_PIN	0


void Dly_ms(u16 ms);
void OLED_Init(void);
void OLED_Fill(u8 dat);
void OLED_WrDat(u8 data);
void OLED_Wr6Dat(u8 data);
void OLED_PutPixel(u8 x,u8 y);
void OLED_ClrPixel(u8 x,u8 y);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);
void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
void OLED_HEXACSII(u16 hex,u8* Print);
void OLED_Print_Num(u8 x, u8 y, u16 num);
void OLED_Print_Num1(u8 x, u8 y, int num);
void dis_bmp(u16 high, u16 width, u8 *p,u8 value);
void OLED_HEXACSIIFF(u16 hex,u8* Print);
void OLED_Print_ASCII(u8 x, u8 y, int num);








#endif
