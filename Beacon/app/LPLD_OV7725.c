#include "common.h"
#include "LPLD_OV7725.h"
#include "LPLD_SCCB.h"
#include "OV7725_REG.h"

uint8 imgbuff[CAMERA_SIZE];
uint8 img[CAMERA_W * CAMERA_H];

volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_FINISH;   //图像状态

/*       鹰眼ov7725初始化        */

void OV7725_Init(void)
{
    UART_Init();
    NVIC_Init();
    while(ov7725_eagle_reg_init() == 0);
    OV7725_GPIO_Init();
    OV7725_DMA_Init();
}//OK
void OV7725_GPIO_Init(void)
{
   GPIO_InitTypeDef gpio_init_struct;

   gpio_init_struct.GPIO_PTx = PTA;
   gpio_init_struct.GPIO_Pins = GPIO_Pin27;//PCLK
   gpio_init_struct.GPIO_Dir = DIR_INPUT;
   gpio_init_struct.GPIO_PinControl = INPUT_PULL_DOWN|IRQC_DMAFA;
   LPLD_GPIO_Init(gpio_init_struct);

   //disable_irq(PORTA_IRQn);//关闭PTA的中断  
   gpio_init_struct.GPIO_PTx = PTA;
   gpio_init_struct.GPIO_Pins = GPIO_Pin29;//VSYNC
   gpio_init_struct.GPIO_Dir = DIR_INPUT;
   gpio_init_struct.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN|INPUT_PF_EN;
   gpio_init_struct.GPIO_Isr = porta_isr;
   LPLD_GPIO_Init(gpio_init_struct);
    
   gpio_init_struct.GPIO_PTx = PTB;
   gpio_init_struct.GPIO_Pins = GPIO_Pin0_7;
   gpio_init_struct.GPIO_Dir = DIR_INPUT;
   LPLD_GPIO_Init(gpio_init_struct);

}//初始化OK

void OV7725_DMA_Init(void)
{
    DMA_InitTypeDef dma_init_struct;

    dma_init_struct.DMA_CHx = DMA_CH0;    
    dma_init_struct.DMA_Req = PORTA_DMAREQ;       
    dma_init_struct.DMA_PeriodicTriggerEnable = FALSE;
    dma_init_struct.DMA_MajorLoopCnt = CAMERA_SIZE; 
    dma_init_struct.DMA_MinorByteCnt = 1; 
    dma_init_struct.DMA_SourceDataSize = DMA_SRC_8BIT;
    dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;       
    dma_init_struct.DMA_SourceAddrOffset = 0;
    dma_init_struct.DMA_LastSourceAddrAdj = 0;
    dma_init_struct.DMA_DestAddr = (uint32)imgbuff;      
    dma_init_struct.DMA_DestDataSize = DMA_DST_8BIT;
    dma_init_struct.DMA_DestAddrOffset = 1;       
    dma_init_struct.DMA_LastDestAddrAdj = 0;
    dma_init_struct.DMA_AutoDisableReq = TRUE;    
    dma_init_struct.DMA_MajorCompleteIntEnable = TRUE;
    dma_init_struct.DMA_MajorHalfCompleteIntEnable = FALSE;
    dma_init_struct.DMA_Isr = LPLD_DMA_Isr;

    LPLD_DMA_Init(dma_init_struct);
    //LPLD_DMA_DisEnableIrq(dma_init_struct);
    DMA0->INT |= 0x1u << 0;//清除通道传输标志位

    LPLD_DMA_EnableIrq(dma_init_struct);

}//DMAOK

void NVIC_Init(void)
{
    NVIC_InitTypeDef nvic_init_struct;
    //配置PORTA的NVIC分组
    nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
    nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
    nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
    LPLD_NVIC_Init(nvic_init_struct);
    //配置DMA0的NVIC分组
    nvic_init_struct.NVIC_IRQChannel = DMA0_DMA16_IRQn;
    nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
    nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
    
    LPLD_NVIC_Init(nvic_init_struct);
}

void UART_Init(void)
{
    UART_InitTypeDef uart5_init_struct;

    uart5_init_struct.UART_Uartx = UART5;     //使用UART5
    uart5_init_struct.UART_BaudRate = 115200; //设置波特率115200
    uart5_init_struct.UART_RxPin = PTE9;      //接收引脚为PTE9
    uart5_init_struct.UART_TxPin = PTE8;      //发送引脚为PTE8
                                                  //初始化UART
    LPLD_UART_Init(uart5_init_struct);
}
void porta_isr(void)
{
    if (LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin29))
    {
        if (ov7725_eagle_img_flag == IMG_START)                   
        {
            ov7725_eagle_img_flag = IMG_GATHER;          
            disable_irq(PORTA_IRQn);
            PORTA->ISFR = 1 << 27;            //清空PCLK标志位
            DMA0->ERQ |= DMA_ERQ_ERQ0_MASK << 0;
            PORTA->ISFR = 1 << 27;            
            DMA0->TCD[0].DADDR = DMA_DADDR_DADDR(imgbuff);
        }
        else
        {
            disable_irq(PORTA_IRQn);
            ov7725_eagle_img_flag = IMG_FAIL;
        }
    }
}

void LPLD_DMA_Isr(void)
{
    ov7725_eagle_img_flag = IMG_FINISH;
    DMA0->INT |= 0x1u << 0;//清除通道传输中断标志位
}

/*!
 *  @brief      鹰眼ov7725采集图像（采集到的数据存储在 初始化时配置的地址上）
 *  @since      v5.0
 */
void ov7725_eagle_get_img()
{
    
    ov7725_eagle_img_flag = IMG_START;                   //开始采集图像
    PORTA->ISFR = ~0;                        //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
    enable_irq(PORTA_IRQn);                         //允许PTA的中断
    while(ov7725_eagle_img_flag != IMG_FINISH)           //等待图像采集完毕
    {
        if(ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
        {
            ov7725_eagle_img_flag = IMG_START;           //开始采集图像
            PORTA->ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
            enable_irq(PORTA_IRQn);                 //允许PTA的中断
        }
    }
}


/*OV7725初始化配置表*/
reg_s ov7725_eagle_reg[] =
{
    //寄存器，寄存器值次
    {OV7725_COM4         , 0xC1},
    {OV7725_CLKRC        , 0x00},
    {OV7725_COM2         , 0x03},
    {OV7725_COM3         , 0xD0},
    {OV7725_COM7         , 0x40},
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 60 )
    {OV7725_VOutSize     , 0x1E},
#elif (CAMERA_H == 120 )
    {OV7725_VOutSize     , 0x3c},
#elif (CAMERA_H == 180 )
    {OV7725_VOutSize     , 0x5a},
#elif (CAMERA_H == 240 )
    {OV7725_VOutSize     , 0x78},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86},
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x00},
    {OV7725_CNST         , 0xFF},
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*结构体数组成员数目*/


/*鹰眼ov7725寄存器 初始化*/
uint8 ov7725_eagle_reg_init()
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    SCCB_GPIO_Init();

    ov7725_delay();
    if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) ) /*复位sensor */
    {
        return 0 ;
    }

    ov7725_delay();
    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER ) )    /* 读取sensor ID号*/
    {
        return 0;
    }

    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

void img_extract(void *dst, void *src, uint32 srclen)
{
    uint8_t colour[2] = {255, 0}; //0 和 1 分别对应的颜色
    uint8_t *mdst = dst;
    uint8_t *msrc = src;
    //注：山外的摄像头 0 表示 白色，1表示 黑色
    uint8_t tmpsrc;
    while (srclen--)
    {
        tmpsrc = *msrc++;
        *mdst++ = colour[(tmpsrc >> 7) & 0x01];
        *mdst++ = colour[(tmpsrc >> 6) & 0x01];
        *mdst++ = colour[(tmpsrc >> 5) & 0x01];
        *mdst++ = colour[(tmpsrc >> 4) & 0x01];
        *mdst++ = colour[(tmpsrc >> 3) & 0x01];
        *mdst++ = colour[(tmpsrc >> 2) & 0x01];
        *mdst++ = colour[(tmpsrc >> 1) & 0x01];
        *mdst++ = colour[(tmpsrc >> 0) & 0x01];
    }
}
void lpld_sending(void *imgaddr, int32 imgsize)
{
#define CMD_IMG 1
    int8 cmdf[2] = {CMD_IMG, ~CMD_IMG}; //山外上位机 使用的命令
    int8 cmdr[2] = {~CMD_IMG, CMD_IMG}; //山外上位机 使用的命令

    LPLD_UART_PutCharArr(UART5, cmdf, sizeof(cmdf)); //先发送命令

    LPLD_UART_PutCharArr(UART5, (int8 *)imgaddr, imgsize); //再发送图像

    LPLD_UART_PutCharArr(UART5, cmdr, sizeof(cmdr)); //先发送命令
}

void ov7725_delay(void)
{
    uint16 i, n;
    for (i = 0; i < 30000; i++)
    {
        for (n = 0; n < 200; n++)
        {
            asm("nop");
        }
    }
}