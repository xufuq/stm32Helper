#include "RC522.h"

unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
unsigned char RFID[16];         //存放RFID 
unsigned char lxl_bit=0;
unsigned char card1_bit=0;
unsigned char card2_bit=0;
unsigned char card3_bit=0;
unsigned char card4_bit=0;
unsigned char total=0;
unsigned char lxl[4]={196,58,104,217};
unsigned char card_1[4]={83,106,11,1};
unsigned char card_2[4]={208,121,31,57};
unsigned char card_3[4]={176,177,143,165};
unsigned char card_4[4]={5,158,10,136};
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
u8 AUDIO_OPEN[6] = {0xAA, 0x07, 0x02, 0x00, 0x09, 0xBC};
unsigned char RFID1[16]={0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x07,0x80,0x29,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char status;
unsigned char s=0x08;

unsigned char BEEP;//蜂鸣器标志位

void delay_us(u32 i)
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


void delay_ms(u32 i)
{
u32 temp;
    SysTick->LOAD = 9000*i;
    SysTick->CTRL = 0x01;
    SysTick->VAL  = 0;
    do
    {
    temp = SysTick->CTRL;
    }while((temp&0x01)&&(!(temp&(1<<16))));
    SysTick->CTRL = 0;
    SysTick->VAL  = 0;
}


#define   RC522_DELAY()  delay_us( 20 )


void RC522_Handel(void)
{

    status = PcdRequest(PICC_REQALL,CT);//寻卡,0x52，寻天线内全部卡，ct是卡的类型
    //CT作为返回值显示出卡的类型

    if(status==MI_OK)//寻卡成功，即返回值为0
    {
         status=MI_ERR;
         status = PcdAnticoll(SN);//防冲撞函数，SN是返回值
    }

    if (status==MI_OK)//防冲撞成功，判断读到哪张卡
    {
        status=MI_ERR;      
        BEEP=1;

        if((SN[0]==lxl[0])&&(SN[1]==lxl[1])&&(SN[2]==lxl[2])&&(SN[3]==lxl[3]))
        {
            lxl_bit=1;

        }
        if((SN[0]==card_1[0])&&(SN[1]==card_1[1])&&(SN[2]==card_1[2])&&(SN[3]==card_1[3]))
        {
            card1_bit=1;

        }
        if((SN[0]==card_2[0])&&(SN[1]==card_2[1])&&(SN[2]==card_2[2])&&(SN[3]==card_2[3]))
        {
            card2_bit=1;

        }

        if((SN[0]==card_3[0])&&(SN[1]==card_3[1])&&(SN[2]==card_3[2])&&(SN[3]==card_3[3]))
        {
            card3_bit=1;

        }
        if((SN[0]==card_4[0])&&(SN[1]==card_4[1])&&(SN[2]==card_4[2])&&(SN[3]==card_4[3]))
        {
            card4_bit=1;

        }
        status =PcdSelect(SN);//所谓防冲撞是当读到一张卡之后不再读其他的卡

    }
    else
    {

        BEEP=0;// BEEP  on
    }
    if(status==MI_OK)//选卡成功
    {

        status=MI_ERR; //2
        status =PcdAuthState(0x60,0x09,KEY,SN);//验证函数
     }
    if(status==MI_OK)//验证成功
    {
        status=MI_ERR;
        status=PcdRead(s,RFID);//读卡函数
    }

    if(status==MI_OK)//读卡成功
    {
        status=MI_ERR;
        delay_ms(100);
        PCout(13)=0;
    }   

}

void RC522_Init ( void )
{
    SPI1_Init();

    RC522_Reset_Disable();

    RC522_CS_Disable();

    PcdReset ();

    M500PcdConfigISOType ( 'A' );//

}

void SPI1_Init(void)    //spi通信引脚初始化
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );//PORTB???? 

    // CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //A4
    // SCK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //A5

    // MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //A6

    // MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   //A7

    // RST
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO????50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //B0

}

/*
 * ???:SPI_RC522_SendByte
 * ??  :向RC522发送1 Byte 数据，mcu向读卡器发送
 * 输入  :byte,要输入的数据
 * 返回  : RC522返回的数据
 * 调用  :内部调用，在应用时不涉及
 */
void SPI_RC522_SendByte ( u8 byte )
{
    u8 counter;

    for(counter=0;counter<8;counter++)
    {     
            if ( byte & 0x80 )
                    RC522_MOSI_1 ();
            else 
                    RC522_MOSI_0 ();

            RC522_DELAY();

            RC522_SCK_0 (); //上升沿或下降沿发送

            RC522_DELAY();

            RC522_SCK_1();

            RC522_DELAY();

            byte <<= 1; 

    } 

}


/*
 * ???:SPI_RC522_ReadByte
 * ??  :从RC522发送1 Byte 数据
 * ??  :?上升沿发送接受数据
 * 返回  : RC522返回的数据
 * ??  :????
 */
u8 SPI_RC522_ReadByte ( void )
{
    u8 counter;
    u8 SPI_Data;


    for(counter=0;counter<8;counter++)
    {
            SPI_Data <<= 1;

            RC522_SCK_0 ();

            RC522_DELAY();

            if ( RC522_MISO_GET() == 1)//获取引脚当前电平状态
                    SPI_Data |= 0x01;

            RC522_DELAY();

            RC522_SCK_1 ();

            RC522_DELAY();

    }
    return SPI_Data;
}


/*
 * ???:ReadRawRC
 * ??  :读RC522寄存器
 * ??  :ucAddress,寄存器地址
 * 返回  : 寄存器的当前值
 * ??  :????
 */
u8 ReadRawRC ( u8 ucAddress )
{
    u8 ucAddr, ucReturn;


    ucAddr = ( ( ucAddress << 1 ) & 0x7E ) | 0x80;

    RC522_CS_Enable();

    SPI_RC522_SendByte ( ucAddr );

    ucReturn = SPI_RC522_ReadByte ();

    RC522_CS_Disable();

    return ucReturn;
}


/*
 * ???:WriteRawRC
 * ??  :写RC522寄存器
 * ??  :ucAddress,寄存器地址
 *      ucValue,写入寄存器的值
 * ??  : ?
 * ??  :????
 */
void WriteRawRC ( u8 ucAddress, u8 ucValue )
{  
    u8 ucAddr;

    ucAddr = ( ucAddress << 1 ) & 0x7E;//地址的计算方法

    RC522_CS_Enable();

    SPI_RC522_SendByte ( ucAddr );//spi发送八位数据，地址

    SPI_RC522_SendByte ( ucValue );//操作数

    RC522_CS_Disable(); 
}

/*
 * ???:SetBitMask
 * ??  :对RC522寄存器置位
 * ??  :ucReg,寄存器地址
 *         ucMask,置位值
 * ??  : ?
 * ??  :????
 */
void SetBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;

    ucTemp = ReadRawRC ( ucReg );         //获取当前寄存器的值

    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask，只改变有限个值，其余不变

}

/*
 * ???:ClearBitMask
 * ??  :对RC522寄存器清位
 * ??  :ucReg,?????
 *         ucMask,???
 * ??  : ?
 * ??  :????
 */
void ClearBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;

    ucTemp = ReadRawRC ( ucReg );//读取当前的寄存器值

    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask


}


/*
 * ???:PcdAntennaOn
 * ??  :开启天线
 * ??  :?
 * ??  : ?
 * ??  :????
 */
void PcdAntennaOn ( void )
{
    u8 uc;

    uc = ReadRawRC ( TxControlReg );//0x14,应该是天线对应寄存器值

    if ( ! ( uc & 0x03 ) )      //如果对应位不是1，置位
            SetBitMask(TxControlReg, 0x03);

}

/*
 * ???:PcdAntennaOff
 * ??  :关闭天线
 * ??  :?
 * ??  : ?
 * ??  :????
 */
void PcdAntennaOff ( void )
{

    ClearBitMask ( TxControlReg, 0x03 );

}

/*
 * ???:PcdRese
 * ??  :复位RC522 
 * ??  :?
 * ??  : ?
 * ??  :????
 */
void PcdReset ( void )
{
    RC522_Reset_Disable();//对rst位置一

    delay_us ( 1 );

    RC522_Reset_Enable();

    delay_us ( 1 );

    RC522_Reset_Disable();//上升沿复位

    delay_us ( 1 );

    WriteRawRC ( CommandReg, 0x0f );

    while ( ReadRawRC ( CommandReg ) & 0x10 );//powerdown为0准备好

    delay_us ( 1 );

    WriteRawRC ( ModeReg, 0x3D );            //定义发送和接受常用模式，和Mifare通讯,CRC初始值0x6363

    WriteRawRC ( TReloadRegL, 30 );          //16位定时器低位
    WriteRawRC ( TReloadRegH, 0 );               //16位定时器高位，产生30延时

    WriteRawRC ( TModeReg, 0x8D );                 //定义内部定时器的设置

    WriteRawRC ( TPrescalerReg, 0x3E );          //设置定时器分频系数

    WriteRawRC ( TxAutoReg, 0x40 );                //???????100%ASK 


}

/*
 * ???:M500PcdConfigISOType
 * ??  :设置RC522的工作方式
 * ??  :ucType,工作方式
 * ??  : ?
 * ??  :????
 */
void M500PcdConfigISOType ( u8 ucType )
{
    if ( ucType == 'A')                     //ISO14443_A
  {
        ClearBitMask ( Status2Reg, 0x08 );

        WriteRawRC ( ModeReg, 0x3D );//3F

        WriteRawRC ( RxSelReg, 0x86 );//84

        WriteRawRC( RFCfgReg, 0x7F );   //4F

        WriteRawRC( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 

        WriteRawRC ( TReloadRegH, 0 );

        WriteRawRC ( TModeReg, 0x8D );

        WriteRawRC ( TPrescalerReg, 0x3E );//设置定时器分频系数

        delay_us ( 2 );

        PcdAntennaOn ();//开天线

   }

}


/*
 * ???:PcdComMF522
 * ??  :通过RC522和ISO14443卡通信
 * ??  :ucCommand,RC522命令字
 *         pInData,通过RC522发送到卡片的数据
 *         ucInLenByte,发送数据的字节长度
 *         pOutData,接收到的卡片返回数据
 *         pOutLenBit,返回数据的位长度
 * ??  : 返回值
 *         = MI_OK,成功
 * ??  :????
 */
char PcdComMF522 ( u8 ucCommand, u8 * pInData, u8 ucInLenByte, u8 * pOutData, u32 * pOutLenBit )        
{
    char cStatus = MI_ERR;
    u8 ucIrqEn   = 0x00;
    u8 ucWaitFor = 0x00;
    u8 ucLastBits;
    u8 ucN;
    u32 ul;

    switch ( ucCommand )
    {
       case PCD_AUTHENT:        //Mifare认证，0x0e,验证秘钥
          ucIrqEn   = 0x12;     //允许错误中断请求ErrIEn  允许空闲中断IdleIEn
          ucWaitFor = 0x10;     //认证寻卡等待时候查询空闲中断标志
          break;

       case PCD_TRANSCEIVE:     //0x0c    发送并接受数据
          ucIrqEn   = 0x77;     //允许TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
          ucWaitFor = 0x30;     //寻卡等代时候查询接受中断标志位与空闲中断标志位
          break;

       default:
         break;

    }

    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );       //IRqInv置位管脚IRQ与Status1Reg的IRq位的值相反
    ClearBitMask ( ComIrqReg, 0x80 );           //Set1该位清零时,CommIRqReg的屏蔽位清零
    WriteRawRC ( CommandReg, PCD_IDLE );        //写空闲命令，0x00,取消当前命令
    SetBitMask ( FIFOLevelReg, 0x80 );          //置位FlushBuffer清除内部FIFO的读和写指针以及ErrReg的BufferOvfl??????

    for ( ul = 0; ul < ucInLenByte; ul ++ )
          WriteRawRC ( FIFODataReg, pInData [ ul ] );           //写数据进FIFOdata，数据并行输入输出转换器

    WriteRawRC ( CommandReg, ucCommand );                   //写命令


    if ( ucCommand == PCD_TRANSCEIVE )                     //0x0c,发送并接受数据
            SetBitMask(BitFramingReg,0x80);                 //StartSend置位启动数据发送
    //将FIFO中数据发送给上边的命令字寄存器，实现命令

    ul = 1000;//根据时钟频率调整，操作M1最大等待时间25ms

    do                                                      //认证与寻卡等待时间
    {
         ucN = ReadRawRC ( ComIrqReg);                         //查询事件中断
         ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );       //退出循环的条件，ucn最后一位必须为1才能退出循环
    //当定时器的寄存器的值递减0时该位置位

    ClearBitMask ( BitFramingReg, 0x80 );                   //清理允许StartSend位，结束数据发送

    if ( ul != 0 )        //如果上个程序执行成功
    {
        if ( ! (ReadRawRC ( ErrorReg ) & 0x1B ) )            //读错误标志寄存器BufferOfI CollErr ParityErr ProtocolErr
        {
            cStatus = MI_OK;

            if ( ucN & ucIrqEn & 0x01 )                 //是否发生定时器中断，在收发命令程序执行过程中，如果产生定时器中断
              cStatus = MI_NOTAGERR;   

            if ( ucCommand == PCD_TRANSCEIVE )          //收发数据过程中
            {
                ucN = ReadRawRC ( FIFOLevelReg );           //读FIFO中保存的字节数

                ucLastBits = ReadRawRC ( ControlReg ) & 0x07;   //最后接受到的字节的有效位数，取这个控制字最后三位作为有效数字

                if ( ucLastBits )   //如果不是八位全都有效
                    * pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;    //N个字节数减去1(最后一个字节)+最后一位的位数，读取到的总位数
                //前N-1个字节是八位的，加上最后一个字节的有效位数是总位数
                else
                    * pOutLenBit = ucN * 8;                     //最后接受到的字节整个字节有效

                if ( ucN == 0 ) 
                    ucN = 1;    

                if ( ucN > MAXRLEN )   //18，FIFO中保存的最大字节数
                    ucN = MAXRLEN;   

                for ( ul = 0; ul < ucN; ul ++ )
                  pOutData [ ul ] = ReadRawRC ( FIFODataReg );   //存放输出信息，当读卡时输出2字节的卡号
            }       
        }
            else
                cStatus = MI_ERR;   
    }

   SetBitMask ( ControlReg, 0x80 );           // stop timer now
   WriteRawRC ( CommandReg, PCD_IDLE );       //清除所有命令

   return cStatus;

}

/*
 * ???:PcdRequest
 * 功能  :寻卡
 * ??  :ucReq_code,寻卡方式
 *                     = 0x52,寻感应区内所有符合14443A标准的卡
 *                     = 0x26,寻未进入休眠的卡
 *         pTagType,卡片类型代码
 *                   = 0x4400,Mifare_UltraLight
 *                   = 0x0400,Mifare_One(S50)
 *                   = 0x0200,Mifare_One(S70)
 *                   = 0x0800,Mifare_Pro(X))
 *                   = 0x4403,Mifare_DESFire
 * 返回  : 状态值
 *         = MI_OK,成功
 * ??  :????
 */
char PcdRequest( u8 ucReq_code, u8 * pTagType )   //ptagtype返回值，code可寻全部卡或者休眠卡
{
    char cStatus;  
    u8 ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;

    ClearBitMask ( Status2Reg, 0x08 );  //清理指示MIFARECyptol单元接通以及所有卡的数据，status2reg是当前操作寄存器
    //包含接收器和发送器的状态标志，0x08
    WriteRawRC ( BitFramingReg, 0x07 ); //  发送的最后一个字节 的七位，面向位的帧的调节，000代表八位
    SetBitMask ( TxControlReg, 0x03 );  //TX1,TX2管脚输出信号的频率设置为13.56MHZ，已调制信号

    ucComMF522Buf [ 0 ] = ucReq_code;       //存入 卡片命令字

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 1, ucComMF522Buf, & ulLen ); //寻卡

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )    //寻卡成功返回卡类型，ullen长度是指位数
    {    
       * pTagType = ucComMF522Buf [ 0 ];//接受返回的数据
       * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
    }

    else
     cStatus = MI_ERR;

    return cStatus;

}

/*
 * ???:PcdAnticoll
 * ??  :防冲撞
 * ??  :pSnr,卡片序列号。4字节
 * 返回  :状态值
 *         = MI_OK,成功
 * ??  :????
 */
char PcdAnticoll ( u8 * pSnr )
{
    char cStatus;
    u8 uc, ucSnr_check = 0;
    u8 ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;

    ClearBitMask ( Status2Reg, 0x08 );      //清MFCryptol On位 只有成功执行MFAuthent命令后，该位才能置位
    WriteRawRC ( BitFramingReg, 0x00);      //清理寄存器，停止收发
    ClearBitMask ( CollReg, 0x80 );         //清ValuesAfterColl所有接受的位在冲突后被清除

    ucComMF522Buf [ 0 ] = 0x93; //卡片防冲撞命令
    ucComMF522Buf [ 1 ] = 0x20;//写入空闲命令清除上一条命令

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//与卡片通信

    if ( cStatus == MI_OK)      //通信成功
    {
        for ( uc = 0; uc < 4; uc ++ )
        {
            * ( pSnr + uc )  = ucComMF522Buf [ uc ];            //读出UID
            ucSnr_check ^= ucComMF522Buf [ uc ];
        }

        if ( ucSnr_check != ucComMF522Buf [ uc ] )
                cStatus = MI_ERR;    

    }

    SetBitMask ( CollReg, 0x80 );

    return cStatus;

}

/*
 * ???:CalulateCRC
 * ??  :用RC522计算CRC16
 * ??  :pIndata,计算CRC16的数组
 *         ucLen,?计算CRC16的数组字节长度
 *         pOutData,存放计算结果的首地址
 * ??  : ?
 * ??  :????
 */
void CalulateCRC ( u8 * pIndata, u8 ucLen, u8 * pOutData )
{
    u8 uc, ucN;

    ClearBitMask(DivIrqReg,0x04);//0x05

    WriteRawRC(CommandReg,PCD_IDLE);//0x00,取消当前命令

    SetBitMask(FIFOLevelReg,0x80);//0x0a

    for ( uc = 0; uc < ucLen; uc ++)
        WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );   //0x09

    WriteRawRC ( CommandReg, PCD_CALCCRC );//0x03,crc计算

    uc = 0xFF;

    do 
    {
        ucN = ReadRawRC ( DivIrqReg );//0x05
        uc --;
    } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );

    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );//0x22
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );//0x21

}

/*
 * ???:PcdSelect
 * ??  ：选定卡片
 * ??  :pSnr,卡片序列号，4字节
 * ??  : 状态值
 *         = MI_OK,成功
 * ??  :????
 */
char PcdSelect ( u8 * pSnr )
{
    char ucN;
    u8 uc;
      u8 ucComMF522Buf [ MAXRLEN ]; 
    u32  ulLen;

    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;//0x93，防冲撞
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;

    for ( uc = 0; uc < 4; uc ++ )
    {
        ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
        ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }

    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );

    ClearBitMask ( Status2Reg, 0x08 );//0x08

    ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );//发送接受数据

    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
      ucN = MI_OK;  
    else
      ucN = MI_ERR;    

    return ucN;

}

/*
 * ???:PcdAuthState
 * ??  :验证卡片密码
 * ??  :ucAuth_mode,密码已验证模式
 *                     = 0x60,验证A秘钥
 *                     = 0x61,验证B秘钥
 *         u8 ucAddr,块地址
 *         pKey,密码
 *         pSnr,卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK,??
 * ??  :????
 */
char PcdAuthState ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr )
{
    char cStatus;
      u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;

    for ( uc = 0; uc < 6; uc ++ )
        ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );   

    for ( uc = 0; uc < 6; uc ++ )
        ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );   

    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );//0x0x,验证秘钥

    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
        {
            
            cStatus = MI_ERR; 
        }

    return cStatus;

}

/*
 * ???:PcdWrite
 * ??  :写数据到M1卡一块
 * ??  :u8 ucAddr,块地址
 *         pData,写入的数据,16字节
 * 返回  : 状态值
 *         = MI_OK,??
 * ??  :????
 */
char PcdWrite ( u8 ucAddr, u8 * pData )
{
    char cStatus;
      u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ucComMF522Buf [ 0 ] = PICC_WRITE;//0xa0,写块
    ucComMF522Buf [ 1 ] = ucAddr;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );//0x0c,发送数据

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
      cStatus = MI_ERR;   

    if ( cStatus == MI_OK )
    {
      //      暂时先屏蔽
      //      memcpy(ucComMF522Buf, pData, 16);//看名字和变量可能是将缓冲区数据放入pdata
      for ( uc = 0; uc < 16; uc ++ )           //应该可以实现上边函数的功能
              ucComMF522Buf [ uc ] = * ( pData + uc );  

      CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );

      cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );

            if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
        cStatus = MI_ERR;   

    } 

    return cStatus;

}

/*
 * ???:PcdRead
 * ??  :读取M1卡一块数据
 * ??  :u8 ucAddr,块地址
 *         pData,读出的数据，16字节
 * ??  : ???
 *         = MI_OK,??
 * ??  :????
 */
char PcdRead ( u8 ucAddr, u8 * pData )
{
    char cStatus;
      u8 uc, ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;

    ucComMF522Buf [ 0 ] = PICC_READ;//0X30,读块
    ucComMF522Buf [ 1 ] = ucAddr;//块地址

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
            for ( uc = 0; uc < 16; uc ++ )
        * ( pData + uc ) = ucComMF522Buf [ uc ];   //得到数据块中的内容
    }

    else
      cStatus = MI_ERR;   

    return cStatus;

}

/*
 * ???:PcdHalt
 * ??  :命令卡片进入休眠状态
 * ??  :?
 * 返回  : 状态值
 *         = MI_OK,??
 * ??  :????
 */
char PcdHalt( void )
{
    u8 ucComMF522Buf [ MAXRLEN ]; 
    u32  ulLen;

    ucComMF522Buf [ 0 ] = PICC_HALT;//0X50，休眠
    ucComMF522Buf [ 1 ] = 0;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
        PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );//0X0C,发送并接受数据

    return MI_OK;

}

void IC_CMT ( u8 * UID, u8 * KEY, u8 RW, u8 * Dat )
{
    u8 ucArray_ID [ 4 ] = { 0 };//先后存放ic卡的类型和UID(IC卡序列号)

    PcdRequest ( 0x52, ucArray_ID );//寻卡

    PcdAnticoll ( ucArray_ID );//防冲撞

    PcdSelect ( UID );//选定卡

    PcdAuthState ( 0x60, 0x10, KEY, UID );//校验

    if ( RW )//读写选择，1是读，0是写
        PcdRead ( 0x10, Dat );

    else 
        PcdWrite ( 0x10, Dat );

    PcdHalt ();  

}

void ShowID(u16 x,u16 y, u8 *p, u16 charColor, u16 bkColor)  //显示卡的卡号，16字节
{
    u8 num[9];
    u8 i;

    for(i=0;i<4;i++)
    {
        num[i*2]=p[i]/16;
        num[i*2]>9?(num[i*2]+='7'):(num[i*2]+='0');
        num[i*2+1]=p[i]%16;
        num[i*2+1]>9?(num[i*2+1]+='7'):(num[i*2+1]+='0');
    }
    num[8]=0;
}
