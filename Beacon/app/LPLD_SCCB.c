#include "common.h"
#include "LPLD_SCCB.h"

static void SCCB_delay(uint16 i);
static void SCCB_delay(volatile uint16 i)
{
    while(i)
    {
        i--;
    }
}



void SCCB_GPIO_Init(void)
{
   GPIO_InitTypeDef gpio_init_struct;
    /*璁剧疆涓篜ULLUP*/
   gpio_init_struct.GPIO_PTx = PTA;
   gpio_init_struct.GPIO_Pins = GPIO_Pin25|GPIO_Pin26;
   gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
   gpio_init_struct.GPIO_Output = OUTPUT_H; //锟斤拷始锟斤拷锟斤拷锟轿拷撸锟�
   gpio_init_struct.GPIO_PinControl = OUTPUT_OD_EN|INPUT_PULL_UP;
   
   LPLD_GPIO_Init(gpio_init_struct);
}

static uint8 SCCB_Start(void)
{
    SDA_H();
    SCL_H();
    SCCB_DELAY();

    SDA_DDR_IN();
    if(!SDA_IN())
    {
        SDA_DDR_OUT();
        return 0;
    }
    SDA_DDR_OUT();
    SDA_L();

    SCCB_DELAY();
    SCL_L();

    if(SDA_IN())
    {
        SDA_DDR_OUT();
        return 0;   /* SDA绾夸负楂樼數骞冲垯鎬荤嚎鍑洪敊,閫€鍑� */
    }
    //SDA_DDR_OUT();
    //SDA_L();
    //SCCB_delay();
    return 1;
}//OK

static void SCCB_Stop(void)
{
    SCL_L();
    //SCCB_DELAY();
    SDA_L();
    SCCB_DELAY();
    SCL_H();
    SCCB_DELAY();
    SDA_H();
    SCCB_DELAY();
}

static void SCCB_Ack(void)
{
    SCL_L();
    SCCB_DELAY();
    SDA_L();
    SCCB_DELAY();
    SCL_H();
    SCCB_DELAY();
    SCL_L();
    SCCB_DELAY();
}

static void SCCB_NoAck(void)
{
    SCL_L();
    SCCB_DELAY();
    SDA_H();
    SCCB_DELAY();
    SCL_H();
    SCCB_DELAY();
    SCL_L();
    SCCB_DELAY();
}

static int SCCB_WaitAck(void)
{
    SCL_L();
    //SDA_H();
    SDA_DDR_IN();

    SCCB_DELAY();
    SCL_H();

    SCCB_DELAY();

    if(SDA_IN())           //搴旂瓟涓洪珮鐢靛钩锛屽紓甯革紝閫氫俊澶辫触
    {
        SDA_DDR_OUT();
        SCL_L();
        return 0;
    }//NO
    SDA_DDR_OUT();
    SCL_L();
    return 1;
}

static void SCCB_SendByte(uint8 SendByte)
{
    uint8 i = 8;
    while(i--)
    {

        if(SendByte & 0x80)     //SDA 杈撳嚭鏁版嵁
        {
            SDA_H();
        }
        else
        {
            SDA_L();
        }
        SendByte <<= 1;
        SCCB_DELAY();
        SCL_H();                //SCL 鎷夐珮锛岄噰闆嗕俊鍙�
        SCCB_DELAY();
        SCL_L();                //SCL 鏃堕挓绾挎媺浣�
        //SCCB_DELAY();
    }
    //SCL_L();
}

static int SCCB_ReceiveByte(void)
{
    uint8 i = 8;
    uint8 ReceiveByte = 0;

    //SDA_H();
    //SCCB_DELAY();
    SDA_DDR_IN();

    while(i--)
    {
        ReceiveByte <<= 1;
        SCL_L();
        SCCB_DELAY();
        SCL_H();
        SCCB_DELAY();

        if(SDA_IN())
        {
            ReceiveByte |= 0x01;
        }


    }
    SDA_DDR_OUT();
    SCL_L();
    return ReceiveByte;
}

static int SCCB_WriteByte_one( uint16 WriteAddress , uint8 SendByte );


int SCCB_WriteByte( uint16 WriteAddress , uint8 SendByte )            //鑰冭檻鍒扮敤sccb鐨勭鑴氭ā鎷燂紝姣旇緝瀹规槗澶辫触锛屽洜姝ゅ璇曞嚑娆�
{
    uint8 i = 0;
    while( 0 == SCCB_WriteByte_one ( WriteAddress, SendByte ) )
    {
        i++;
        if(i == 20)
        {
            return 0 ;
        }
    }
    return 1;
}

int SCCB_WriteByte_one( uint16 WriteAddress , uint8 SendByte )
{
    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR );                    /* 鍣ㄤ欢鍦板潃 */
    if( !SCCB_WaitAck() )
    {
        SCCB_Stop();
        return 0;
    }
    SCCB_SendByte((uint8)(WriteAddress & 0x00FF));   /* 璁剧疆浣庤捣濮嬪湴鍧€ */
    SCCB_WaitAck();
    SCCB_SendByte(SendByte);
    SCCB_WaitAck();
    SCCB_Stop();
    return 1;
}

static int SCCB_ReadByte_one(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress);

int SCCB_ReadByte(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress)
{
    uint8 i = 0;
    while( 0 == SCCB_ReadByte_one(pBuffer, length, ReadAddress) )
    {
        i++;
        if(i == 30)
        {
            return 0 ;
        }
    }
    return 1;
}

int SCCB_ReadByte_one(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress)
{
    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR );         /* 鍣ㄤ欢鍦板潃 */
    if( !SCCB_WaitAck() )
    {
        SCCB_Stop();
        return 0;
    }
    SCCB_SendByte( ReadAddress );           /* 璁剧疆浣庤捣濮嬪湴鍧€ */
    SCCB_WaitAck();
    SCCB_Stop();

    if(!SCCB_Start())
    {
        return 0;
    }
    SCCB_SendByte( DEV_ADR + 1 );               /* 鍣ㄤ欢鍦板潃 */

    if(!SCCB_WaitAck())
    {
        SCCB_Stop();
        return 0;
    }
    while(length)
    {
        *pBuffer = SCCB_ReceiveByte();
        if(length == 1)
        {
            SCCB_NoAck();
        }
        else
        {
            SCCB_Ack();
        }
        pBuffer++;
        length--;
    }
    SCCB_Stop();
    return 1;
}
