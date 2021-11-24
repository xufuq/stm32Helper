#include "RC522.h"

unsigned char CT[2];//������
unsigned char SN[4]; //����
unsigned char RFID[16];         //���RFID 
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

unsigned char BEEP;//��������־λ

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

    status = PcdRequest(PICC_REQALL,CT);//Ѱ��,0x52��Ѱ������ȫ������ct�ǿ�������
    //CT��Ϊ����ֵ��ʾ����������

    if(status==MI_OK)//Ѱ���ɹ���������ֵΪ0
    {
         status=MI_ERR;
         status = PcdAnticoll(SN);//����ײ������SN�Ƿ���ֵ
    }

    if (status==MI_OK)//����ײ�ɹ����ж϶������ſ�
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
        status =PcdSelect(SN);//��ν����ײ�ǵ�����һ�ſ�֮���ٶ������Ŀ�

    }
    else
    {

        BEEP=0;// BEEP  on
    }
    if(status==MI_OK)//ѡ���ɹ�
    {

        status=MI_ERR; //2
        status =PcdAuthState(0x60,0x09,KEY,SN);//��֤����
     }
    if(status==MI_OK)//��֤�ɹ�
    {
        status=MI_ERR;
        status=PcdRead(s,RFID);//��������
    }

    if(status==MI_OK)//�����ɹ�
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

void SPI1_Init(void)    //spiͨ�����ų�ʼ��
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );//PORTB???? 

    // CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //IO�ٶ�50MHz
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
 * ??  :��RC522����1 Byte ���ݣ�mcu�����������
 * ����  :byte,Ҫ���������
 * ����  : RC522���ص�����
 * ����  :�ڲ����ã���Ӧ��ʱ���漰
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

            RC522_SCK_0 (); //�����ػ��½��ط���

            RC522_DELAY();

            RC522_SCK_1();

            RC522_DELAY();

            byte <<= 1; 

    } 

}


/*
 * ???:SPI_RC522_ReadByte
 * ??  :��RC522����1 Byte ����
 * ??  :?�����ط��ͽ�������
 * ����  : RC522���ص�����
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

            if ( RC522_MISO_GET() == 1)//��ȡ���ŵ�ǰ��ƽ״̬
                    SPI_Data |= 0x01;

            RC522_DELAY();

            RC522_SCK_1 ();

            RC522_DELAY();

    }
    return SPI_Data;
}


/*
 * ???:ReadRawRC
 * ??  :��RC522�Ĵ���
 * ??  :ucAddress,�Ĵ�����ַ
 * ����  : �Ĵ����ĵ�ǰֵ
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
 * ??  :дRC522�Ĵ���
 * ??  :ucAddress,�Ĵ�����ַ
 *      ucValue,д��Ĵ�����ֵ
 * ??  : ?
 * ??  :????
 */
void WriteRawRC ( u8 ucAddress, u8 ucValue )
{  
    u8 ucAddr;

    ucAddr = ( ucAddress << 1 ) & 0x7E;//��ַ�ļ��㷽��

    RC522_CS_Enable();

    SPI_RC522_SendByte ( ucAddr );//spi���Ͱ�λ���ݣ���ַ

    SPI_RC522_SendByte ( ucValue );//������

    RC522_CS_Disable(); 
}

/*
 * ???:SetBitMask
 * ??  :��RC522�Ĵ�����λ
 * ??  :ucReg,�Ĵ�����ַ
 *         ucMask,��λֵ
 * ??  : ?
 * ??  :????
 */
void SetBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;

    ucTemp = ReadRawRC ( ucReg );         //��ȡ��ǰ�Ĵ�����ֵ

    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask��ֻ�ı����޸�ֵ�����಻��

}

/*
 * ???:ClearBitMask
 * ??  :��RC522�Ĵ�����λ
 * ??  :ucReg,?????
 *         ucMask,???
 * ??  : ?
 * ??  :????
 */
void ClearBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;

    ucTemp = ReadRawRC ( ucReg );//��ȡ��ǰ�ļĴ���ֵ

    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask


}


/*
 * ???:PcdAntennaOn
 * ??  :��������
 * ??  :?
 * ??  : ?
 * ??  :????
 */
void PcdAntennaOn ( void )
{
    u8 uc;

    uc = ReadRawRC ( TxControlReg );//0x14,Ӧ�������߶�Ӧ�Ĵ���ֵ

    if ( ! ( uc & 0x03 ) )      //�����Ӧλ����1����λ
            SetBitMask(TxControlReg, 0x03);

}

/*
 * ???:PcdAntennaOff
 * ??  :�ر�����
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
 * ??  :��λRC522 
 * ??  :?
 * ??  : ?
 * ??  :????
 */
void PcdReset ( void )
{
    RC522_Reset_Disable();//��rstλ��һ

    delay_us ( 1 );

    RC522_Reset_Enable();

    delay_us ( 1 );

    RC522_Reset_Disable();//�����ظ�λ

    delay_us ( 1 );

    WriteRawRC ( CommandReg, 0x0f );

    while ( ReadRawRC ( CommandReg ) & 0x10 );//powerdownΪ0׼����

    delay_us ( 1 );

    WriteRawRC ( ModeReg, 0x3D );            //���巢�ͺͽ��ܳ���ģʽ����MifareͨѶ,CRC��ʼֵ0x6363

    WriteRawRC ( TReloadRegL, 30 );          //16λ��ʱ����λ
    WriteRawRC ( TReloadRegH, 0 );               //16λ��ʱ����λ������30��ʱ

    WriteRawRC ( TModeReg, 0x8D );                 //�����ڲ���ʱ��������

    WriteRawRC ( TPrescalerReg, 0x3E );          //���ö�ʱ����Ƶϵ��

    WriteRawRC ( TxAutoReg, 0x40 );                //???????100%ASK 


}

/*
 * ???:M500PcdConfigISOType
 * ??  :����RC522�Ĺ�����ʽ
 * ??  :ucType,������ʽ
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

        WriteRawRC ( TPrescalerReg, 0x3E );//���ö�ʱ����Ƶϵ��

        delay_us ( 2 );

        PcdAntennaOn ();//������

   }

}


/*
 * ???:PcdComMF522
 * ??  :ͨ��RC522��ISO14443��ͨ��
 * ??  :ucCommand,RC522������
 *         pInData,ͨ��RC522���͵���Ƭ������
 *         ucInLenByte,�������ݵ��ֽڳ���
 *         pOutData,���յ��Ŀ�Ƭ��������
 *         pOutLenBit,�������ݵ�λ����
 * ??  : ����ֵ
 *         = MI_OK,�ɹ�
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
       case PCD_AUTHENT:        //Mifare��֤��0x0e,��֤��Կ
          ucIrqEn   = 0x12;     //��������ж�����ErrIEn  ��������ж�IdleIEn
          ucWaitFor = 0x10;     //��֤Ѱ���ȴ�ʱ���ѯ�����жϱ�־
          break;

       case PCD_TRANSCEIVE:     //0x0c    ���Ͳ���������
          ucIrqEn   = 0x77;     //����TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
          ucWaitFor = 0x30;     //Ѱ���ȴ�ʱ���ѯ�����жϱ�־λ������жϱ�־λ
          break;

       default:
         break;

    }

    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );       //IRqInv��λ�ܽ�IRQ��Status1Reg��IRqλ��ֵ�෴
    ClearBitMask ( ComIrqReg, 0x80 );           //Set1��λ����ʱ,CommIRqReg������λ����
    WriteRawRC ( CommandReg, PCD_IDLE );        //д�������0x00,ȡ����ǰ����
    SetBitMask ( FIFOLevelReg, 0x80 );          //��λFlushBuffer����ڲ�FIFO�Ķ���дָ���Լ�ErrReg��BufferOvfl??????

    for ( ul = 0; ul < ucInLenByte; ul ++ )
          WriteRawRC ( FIFODataReg, pInData [ ul ] );           //д���ݽ�FIFOdata�����ݲ����������ת����

    WriteRawRC ( CommandReg, ucCommand );                   //д����


    if ( ucCommand == PCD_TRANSCEIVE )                     //0x0c,���Ͳ���������
            SetBitMask(BitFramingReg,0x80);                 //StartSend��λ�������ݷ���
    //��FIFO�����ݷ��͸��ϱߵ������ּĴ�����ʵ������

    ul = 1000;//����ʱ��Ƶ�ʵ���������M1���ȴ�ʱ��25ms

    do                                                      //��֤��Ѱ���ȴ�ʱ��
    {
         ucN = ReadRawRC ( ComIrqReg);                         //��ѯ�¼��ж�
         ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );       //�˳�ѭ����������ucn���һλ����Ϊ1�����˳�ѭ��
    //����ʱ���ļĴ�����ֵ�ݼ�0ʱ��λ��λ

    ClearBitMask ( BitFramingReg, 0x80 );                   //��������StartSendλ���������ݷ���

    if ( ul != 0 )        //����ϸ�����ִ�гɹ�
    {
        if ( ! (ReadRawRC ( ErrorReg ) & 0x1B ) )            //�������־�Ĵ���BufferOfI CollErr ParityErr ProtocolErr
        {
            cStatus = MI_OK;

            if ( ucN & ucIrqEn & 0x01 )                 //�Ƿ�����ʱ���жϣ����շ��������ִ�й����У����������ʱ���ж�
              cStatus = MI_NOTAGERR;   

            if ( ucCommand == PCD_TRANSCEIVE )          //�շ����ݹ�����
            {
                ucN = ReadRawRC ( FIFOLevelReg );           //��FIFO�б�����ֽ���

                ucLastBits = ReadRawRC ( ControlReg ) & 0x07;   //�����ܵ����ֽڵ���Чλ����ȡ��������������λ��Ϊ��Ч����

                if ( ucLastBits )   //������ǰ�λȫ����Ч
                    * pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;    //N���ֽ�����ȥ1(���һ���ֽ�)+���һλ��λ������ȡ������λ��
                //ǰN-1���ֽ��ǰ�λ�ģ��������һ���ֽڵ���Чλ������λ��
                else
                    * pOutLenBit = ucN * 8;                     //�����ܵ����ֽ������ֽ���Ч

                if ( ucN == 0 ) 
                    ucN = 1;    

                if ( ucN > MAXRLEN )   //18��FIFO�б��������ֽ���
                    ucN = MAXRLEN;   

                for ( ul = 0; ul < ucN; ul ++ )
                  pOutData [ ul ] = ReadRawRC ( FIFODataReg );   //��������Ϣ��������ʱ���2�ֽڵĿ���
            }       
        }
            else
                cStatus = MI_ERR;   
    }

   SetBitMask ( ControlReg, 0x80 );           // stop timer now
   WriteRawRC ( CommandReg, PCD_IDLE );       //�����������

   return cStatus;

}

/*
 * ???:PcdRequest
 * ����  :Ѱ��
 * ??  :ucReq_code,Ѱ����ʽ
 *                     = 0x52,Ѱ��Ӧ�������з���14443A��׼�Ŀ�
 *                     = 0x26,Ѱδ�������ߵĿ�
 *         pTagType,��Ƭ���ʹ���
 *                   = 0x4400,Mifare_UltraLight
 *                   = 0x0400,Mifare_One(S50)
 *                   = 0x0200,Mifare_One(S70)
 *                   = 0x0800,Mifare_Pro(X))
 *                   = 0x4403,Mifare_DESFire
 * ����  : ״ֵ̬
 *         = MI_OK,�ɹ�
 * ??  :????
 */
char PcdRequest( u8 ucReq_code, u8 * pTagType )   //ptagtype����ֵ��code��Ѱȫ�����������߿�
{
    char cStatus;  
    u8 ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;

    ClearBitMask ( Status2Reg, 0x08 );  //����ָʾMIFARECyptol��Ԫ��ͨ�Լ����п������ݣ�status2reg�ǵ�ǰ�����Ĵ���
    //�����������ͷ�������״̬��־��0x08
    WriteRawRC ( BitFramingReg, 0x07 ); //  ���͵����һ���ֽ� ����λ������λ��֡�ĵ��ڣ�000�����λ
    SetBitMask ( TxControlReg, 0x03 );  //TX1,TX2�ܽ�����źŵ�Ƶ������Ϊ13.56MHZ���ѵ����ź�

    ucComMF522Buf [ 0 ] = ucReq_code;       //���� ��Ƭ������

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 1, ucComMF522Buf, & ulLen ); //Ѱ��

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )    //Ѱ���ɹ����ؿ����ͣ�ullen������ָλ��
    {    
       * pTagType = ucComMF522Buf [ 0 ];//���ܷ��ص�����
       * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
    }

    else
     cStatus = MI_ERR;

    return cStatus;

}

/*
 * ???:PcdAnticoll
 * ??  :����ײ
 * ??  :pSnr,��Ƭ���кš�4�ֽ�
 * ����  :״ֵ̬
 *         = MI_OK,�ɹ�
 * ??  :????
 */
char PcdAnticoll ( u8 * pSnr )
{
    char cStatus;
    u8 uc, ucSnr_check = 0;
    u8 ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;

    ClearBitMask ( Status2Reg, 0x08 );      //��MFCryptol Onλ ֻ�гɹ�ִ��MFAuthent����󣬸�λ������λ
    WriteRawRC ( BitFramingReg, 0x00);      //����Ĵ�����ֹͣ�շ�
    ClearBitMask ( CollReg, 0x80 );         //��ValuesAfterColl���н��ܵ�λ�ڳ�ͻ�����

    ucComMF522Buf [ 0 ] = 0x93; //��Ƭ����ײ����
    ucComMF522Buf [ 1 ] = 0x20;//д��������������һ������

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//�뿨Ƭͨ��

    if ( cStatus == MI_OK)      //ͨ�ųɹ�
    {
        for ( uc = 0; uc < 4; uc ++ )
        {
            * ( pSnr + uc )  = ucComMF522Buf [ uc ];            //����UID
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
 * ??  :��RC522����CRC16
 * ??  :pIndata,����CRC16������
 *         ucLen,?����CRC16�������ֽڳ���
 *         pOutData,��ż��������׵�ַ
 * ??  : ?
 * ??  :????
 */
void CalulateCRC ( u8 * pIndata, u8 ucLen, u8 * pOutData )
{
    u8 uc, ucN;

    ClearBitMask(DivIrqReg,0x04);//0x05

    WriteRawRC(CommandReg,PCD_IDLE);//0x00,ȡ����ǰ����

    SetBitMask(FIFOLevelReg,0x80);//0x0a

    for ( uc = 0; uc < ucLen; uc ++)
        WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );   //0x09

    WriteRawRC ( CommandReg, PCD_CALCCRC );//0x03,crc����

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
 * ??  ��ѡ����Ƭ
 * ??  :pSnr,��Ƭ���кţ�4�ֽ�
 * ??  : ״ֵ̬
 *         = MI_OK,�ɹ�
 * ??  :????
 */
char PcdSelect ( u8 * pSnr )
{
    char ucN;
    u8 uc;
      u8 ucComMF522Buf [ MAXRLEN ]; 
    u32  ulLen;

    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;//0x93������ײ
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;

    for ( uc = 0; uc < 4; uc ++ )
    {
        ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
        ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }

    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );

    ClearBitMask ( Status2Reg, 0x08 );//0x08

    ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );//���ͽ�������

    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
      ucN = MI_OK;  
    else
      ucN = MI_ERR;    

    return ucN;

}

/*
 * ???:PcdAuthState
 * ??  :��֤��Ƭ����
 * ??  :ucAuth_mode,��������֤ģʽ
 *                     = 0x60,��֤A��Կ
 *                     = 0x61,��֤B��Կ
 *         u8 ucAddr,���ַ
 *         pKey,����
 *         pSnr,��Ƭ���кţ�4�ֽ�
 * ����  : ״ֵ̬
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

    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );//0x0x,��֤��Կ

    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
        {
            
            cStatus = MI_ERR; 
        }

    return cStatus;

}

/*
 * ???:PcdWrite
 * ??  :д���ݵ�M1��һ��
 * ??  :u8 ucAddr,���ַ
 *         pData,д�������,16�ֽ�
 * ����  : ״ֵ̬
 *         = MI_OK,??
 * ??  :????
 */
char PcdWrite ( u8 ucAddr, u8 * pData )
{
    char cStatus;
      u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;

    ucComMF522Buf [ 0 ] = PICC_WRITE;//0xa0,д��
    ucComMF522Buf [ 1 ] = ucAddr;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );//0x0c,��������

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
      cStatus = MI_ERR;   

    if ( cStatus == MI_OK )
    {
      //      ��ʱ������
      //      memcpy(ucComMF522Buf, pData, 16);//�����ֺͱ��������ǽ����������ݷ���pdata
      for ( uc = 0; uc < 16; uc ++ )           //Ӧ�ÿ���ʵ���ϱߺ����Ĺ���
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
 * ??  :��ȡM1��һ������
 * ??  :u8 ucAddr,���ַ
 *         pData,���������ݣ�16�ֽ�
 * ??  : ???
 *         = MI_OK,??
 * ??  :????
 */
char PcdRead ( u8 ucAddr, u8 * pData )
{
    char cStatus;
      u8 uc, ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;

    ucComMF522Buf [ 0 ] = PICC_READ;//0X30,����
    ucComMF522Buf [ 1 ] = ucAddr;//���ַ

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
            for ( uc = 0; uc < 16; uc ++ )
        * ( pData + uc ) = ucComMF522Buf [ uc ];   //�õ����ݿ��е�����
    }

    else
      cStatus = MI_ERR;   

    return cStatus;

}

/*
 * ???:PcdHalt
 * ??  :���Ƭ��������״̬
 * ??  :?
 * ����  : ״ֵ̬
 *         = MI_OK,??
 * ??  :????
 */
char PcdHalt( void )
{
    u8 ucComMF522Buf [ MAXRLEN ]; 
    u32  ulLen;

    ucComMF522Buf [ 0 ] = PICC_HALT;//0X50������
    ucComMF522Buf [ 1 ] = 0;

    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
        PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );//0X0C,���Ͳ���������

    return MI_OK;

}

void IC_CMT ( u8 * UID, u8 * KEY, u8 RW, u8 * Dat )
{
    u8 ucArray_ID [ 4 ] = { 0 };//�Ⱥ���ic�������ͺ�UID(IC�����к�)

    PcdRequest ( 0x52, ucArray_ID );//Ѱ��

    PcdAnticoll ( ucArray_ID );//����ײ

    PcdSelect ( UID );//ѡ����

    PcdAuthState ( 0x60, 0x10, KEY, UID );//У��

    if ( RW )//��дѡ��1�Ƕ���0��д
        PcdRead ( 0x10, Dat );

    else 
        PcdWrite ( 0x10, Dat );

    PcdHalt ();  

}

void ShowID(u16 x,u16 y, u8 *p, u16 charColor, u16 bkColor)  //��ʾ���Ŀ��ţ�16�ֽ�
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
