///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       02/Dec/2017  10:48:02
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\LPLD_OV7725.c
//    Command line =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\LPLD_OV7725.c
//        -D LPLD_K60 -D USE_K60F12 -lCN
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\FLASH\List\
//        -lB
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\FLASH\List\
//        -o
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=VFPv4_sp --dlib_config
//        E:\IAR\File\arm\INC\c\DLib_Config_Normal.h -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\app\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\CPU\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\common\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\LPLD\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\FatFs\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\USB\common\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\..\..\..\lib\USB\class\
//        -Ol -I E:\IAR\File\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\FLASH\List\LPLD_OV7725.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_DMA_EnableIrq
        EXTERN LPLD_DMA_Init
        EXTERN LPLD_GPIO_Init
        EXTERN LPLD_NVIC_Init
        EXTERN LPLD_UART_Init
        EXTERN LPLD_UART_PutCharArr
        EXTERN SCCB_GPIO_Init
        EXTERN SCCB_ReadByte
        EXTERN SCCB_WriteByte
        EXTERN __aeabi_memcpy4

        PUBLIC LPLD_DMA_Isr
        PUBLIC NVIC_Init
        PUBLIC OV7725_DMA_Init
        PUBLIC OV7725_GPIO_Init
        PUBLIC OV7725_Init
        PUBLIC UART_Init
        PUBLIC img
        PUBLIC img_extract
        PUBLIC imgbuff
        PUBLIC lpld_sending
        PUBLIC ov7725_delay
        PUBLIC ov7725_eagle_cfgnum
        PUBLIC ov7725_eagle_get_img
        PUBLIC ov7725_eagle_img_flag
        PUBLIC ov7725_eagle_reg
        PUBLIC ov7725_eagle_reg_init
        PUBLIC porta_isr

// E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\LPLD_OV7725.c
//    1 #include "common.h"

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// static __interwork __softfp void NVIC_EnableIRQ(IRQn_Type)
NVIC_EnableIRQ:
        MOVS     R1,#+1
        ANDS     R2,R0,#0x1F
        LSLS     R1,R1,R2
        LDR.W    R2,??DataTable10  ;; 0xe000e100
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        LSRS     R0,R0,#+5
        STR      R1,[R2, R0, LSL #+2]
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// static __interwork __softfp void NVIC_DisableIRQ(IRQn_Type)
NVIC_DisableIRQ:
        MOVS     R1,#+1
        ANDS     R2,R0,#0x1F
        LSLS     R1,R1,R2
        LDR.W    R2,??DataTable10_1  ;; 0xe000e180
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        LSRS     R0,R0,#+5
        STR      R1,[R2, R0, LSL #+2]
        BX       LR               ;; return
//    2 #include "LPLD_OV7725.h"
//    3 #include "LPLD_SCCB.h"
//    4 #include "OV7725_REG.h"
//    5 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    6 uint8 imgbuff[CAMERA_SIZE];
imgbuff:
        DS8 600

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    7 uint8 img[CAMERA_W * CAMERA_H];
img:
        DS8 4800
//    8 

        SECTION `.data`:DATA:REORDER:NOROOT(0)
//    9 volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_FINISH;   //图像状态
ov7725_eagle_img_flag:
        DATA
        DC8 1
//   10 
//   11 /*       鹰眼ov7725初始化        */
//   12 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   13 void OV7725_Init(void)
//   14 {
OV7725_Init:
        PUSH     {R7,LR}
//   15     UART_Init();
        BL       UART_Init
//   16     NVIC_Init();
        BL       NVIC_Init
//   17     while(ov7725_eagle_reg_init() == 0);
??OV7725_Init_0:
        BL       ov7725_eagle_reg_init
        CMP      R0,#+0
        BEQ.N    ??OV7725_Init_0
//   18     OV7725_GPIO_Init();
        BL       OV7725_GPIO_Init
//   19     OV7725_DMA_Init();
        BL       OV7725_DMA_Init
//   20 }//OK
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   21 void OV7725_GPIO_Init(void)
//   22 {
OV7725_GPIO_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   23    GPIO_InitTypeDef gpio_init_struct;
//   24 
//   25    gpio_init_struct.GPIO_PTx = PTA;
        LDR.W    R0,??DataTable10_2  ;; 0x400ff000
        STR      R0,[SP, #+4]
//   26    gpio_init_struct.GPIO_Pins = GPIO_Pin27;//PCLK
        MOVS     R0,#+134217728
        STR      R0,[SP, #+8]
//   27    gpio_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//   28    gpio_init_struct.GPIO_PinControl = INPUT_PULL_DOWN|IRQC_DMAFA;
        MOVS     R0,#+131074
        STR      R0,[SP, #+12]
//   29    LPLD_GPIO_Init(gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   30 
//   31    //disable_irq(PORTA_IRQn);//关闭PTA的中断  
//   32    gpio_init_struct.GPIO_PTx = PTA;
        LDR.N    R0,??DataTable10_2  ;; 0x400ff000
        STR      R0,[SP, #+4]
//   33    gpio_init_struct.GPIO_Pins = GPIO_Pin29;//VSYNC
        MOVS     R0,#+536870912
        STR      R0,[SP, #+8]
//   34    gpio_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//   35    gpio_init_struct.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN|INPUT_PF_EN;
        LDR.N    R0,??DataTable10_3  ;; 0x90012
        STR      R0,[SP, #+12]
//   36    gpio_init_struct.GPIO_Isr = porta_isr;
        ADR.W    R0,porta_isr
        STR      R0,[SP, #+20]
//   37    LPLD_GPIO_Init(gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   38     
//   39    gpio_init_struct.GPIO_PTx = PTB;
        LDR.N    R0,??DataTable10_4  ;; 0x400ff040
        STR      R0,[SP, #+4]
//   40    gpio_init_struct.GPIO_Pins = GPIO_Pin0_7;
        MOVS     R0,#+255
        STR      R0,[SP, #+8]
//   41    gpio_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//   42    LPLD_GPIO_Init(gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   43 
//   44 }//初始化OK
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   45 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   46 void OV7725_DMA_Init(void)
//   47 {
OV7725_DMA_Init:
        PUSH     {LR}
        SUB      SP,SP,#+76
//   48     DMA_InitTypeDef dma_init_struct;
//   49 
//   50     dma_init_struct.DMA_CHx = DMA_CH0;    
        MOVS     R0,#+0
        STRB     R0,[SP, #+28]
//   51     dma_init_struct.DMA_Req = PORTA_DMAREQ;       
        MOVS     R0,#+49
        STRB     R0,[SP, #+29]
//   52     dma_init_struct.DMA_PeriodicTriggerEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+30]
//   53     dma_init_struct.DMA_MajorLoopCnt = CAMERA_SIZE; 
        MOV      R0,#+600
        STRH     R0,[SP, #+32]
//   54     dma_init_struct.DMA_MinorByteCnt = 1; 
        MOVS     R0,#+1
        STR      R0,[SP, #+36]
//   55     dma_init_struct.DMA_SourceDataSize = DMA_SRC_8BIT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+44]
//   56     dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;       
        LDR.N    R0,??DataTable10_5  ;; 0x400ff050
        STR      R0,[SP, #+40]
//   57     dma_init_struct.DMA_SourceAddrOffset = 0;
        MOVS     R0,#+0
        STRH     R0,[SP, #+46]
//   58     dma_init_struct.DMA_LastSourceAddrAdj = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+48]
//   59     dma_init_struct.DMA_DestAddr = (uint32)imgbuff;      
        LDR.N    R0,??DataTable10_6
        STR      R0,[SP, #+52]
//   60     dma_init_struct.DMA_DestDataSize = DMA_DST_8BIT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+56]
//   61     dma_init_struct.DMA_DestAddrOffset = 1;       
        MOVS     R0,#+1
        STRH     R0,[SP, #+58]
//   62     dma_init_struct.DMA_LastDestAddrAdj = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+60]
//   63     dma_init_struct.DMA_AutoDisableReq = TRUE;    
        MOVS     R0,#+1
        STRB     R0,[SP, #+64]
//   64     dma_init_struct.DMA_MajorCompleteIntEnable = TRUE;
        MOVS     R0,#+1
        STRB     R0,[SP, #+65]
//   65     dma_init_struct.DMA_MajorHalfCompleteIntEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+66]
//   66     dma_init_struct.DMA_Isr = LPLD_DMA_Isr;
        ADR.W    R0,LPLD_DMA_Isr
        STR      R0,[SP, #+68]
//   67 
//   68     LPLD_DMA_Init(dma_init_struct);
        ADD      R1,SP,#+28
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+44
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_DMA_Init
//   69     //LPLD_DMA_DisEnableIrq(dma_init_struct);
//   70     DMA0->INT |= 0x1u << 0;//清除通道传输标志位
        LDR.N    R0,??DataTable10_7  ;; 0x40008024
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable10_7  ;; 0x40008024
        STR      R0,[R1, #+0]
//   71 
//   72     LPLD_DMA_EnableIrq(dma_init_struct);
        ADD      R1,SP,#+28
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+44
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_DMA_EnableIrq
//   73 
//   74 }//DMAOK
        ADD      SP,SP,#+76
        POP      {PC}             ;; return
//   75 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   76 void NVIC_Init(void)
//   77 {
NVIC_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   78     NVIC_InitTypeDef nvic_init_struct;
//   79     //配置PORTA的NVIC分组
//   80     nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
        MOVS     R0,#+87
        STRB     R0,[SP, #+4]
//   81     nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   82     nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
        MOVS     R0,#+2
        STR      R0,[SP, #+12]
//   83     nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+16]
//   84     nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   85     LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   86     //配置DMA0的NVIC分组
//   87     nvic_init_struct.NVIC_IRQChannel = DMA0_DMA16_IRQn;
        MOVS     R0,#+0
        STRB     R0,[SP, #+4]
//   88     nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   89     nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//   90     nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+16]
//   91     nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   92     
//   93     LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   94 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   95 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   96 void UART_Init(void)
//   97 {
UART_Init:
        PUSH     {LR}
        SUB      SP,SP,#+44
//   98     UART_InitTypeDef uart5_init_struct;
//   99 
//  100     uart5_init_struct.UART_Uartx = UART5;     //使用UART5
        LDR.N    R0,??DataTable10_8  ;; 0x400eb000
        STR      R0,[SP, #+12]
//  101     uart5_init_struct.UART_BaudRate = 115200; //设置波特率115200
        MOVS     R0,#+115200
        STR      R0,[SP, #+16]
//  102     uart5_init_struct.UART_RxPin = PTE9;      //接收引脚为PTE9
        MOVS     R0,#+133
        STRB     R0,[SP, #+21]
//  103     uart5_init_struct.UART_TxPin = PTE8;      //发送引脚为PTE8
        MOVS     R0,#+132
        STRB     R0,[SP, #+20]
//  104                                                   //初始化UART
//  105     LPLD_UART_Init(uart5_init_struct);
        ADD      R1,SP,#+12
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+28
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_UART_Init
//  106 }
        ADD      SP,SP,#+44
        POP      {PC}             ;; return

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  107 void porta_isr(void)
//  108 {
porta_isr:
        PUSH     {R7,LR}
//  109     if (LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin29))
        LDR.N    R0,??DataTable10_9  ;; 0x400490a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+2
        BPL.N    ??porta_isr_0
//  110     {
//  111         if (ov7725_eagle_img_flag == IMG_START)                   
        LDR.N    R0,??DataTable10_10
        LDRB     R0,[R0, #+0]
        CMP      R0,#+4
        BNE.N    ??porta_isr_1
//  112         {
//  113             ov7725_eagle_img_flag = IMG_GATHER;          
        MOVS     R0,#+3
        LDR.N    R1,??DataTable10_10
        STRB     R0,[R1, #+0]
//  114             disable_irq(PORTA_IRQn);
        MOVS     R0,#+87
        BL       NVIC_DisableIRQ
//  115             PORTA->ISFR = 1 << 27;            //清空PCLK标志位
        MOVS     R0,#+134217728
        LDR.N    R1,??DataTable10_9  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  116             DMA0->ERQ |= DMA_ERQ_ERQ0_MASK << 0;
        LDR.N    R0,??DataTable10_11  ;; 0x4000800c
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable10_11  ;; 0x4000800c
        STR      R0,[R1, #+0]
//  117             PORTA->ISFR = 1 << 27;            
        MOVS     R0,#+134217728
        LDR.N    R1,??DataTable10_9  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  118             DMA0->TCD[0].DADDR = DMA_DADDR_DADDR(imgbuff);
        LDR.N    R0,??DataTable10_6
        LDR.N    R1,??DataTable10_12  ;; 0x40009010
        STR      R0,[R1, #+0]
        B.N      ??porta_isr_0
//  119         }
//  120         else
//  121         {
//  122             disable_irq(PORTA_IRQn);
??porta_isr_1:
        MOVS     R0,#+87
        BL       NVIC_DisableIRQ
//  123             ov7725_eagle_img_flag = IMG_FAIL;
        MOVS     R0,#+2
        LDR.N    R1,??DataTable10_10
        STRB     R0,[R1, #+0]
//  124         }
//  125     }
//  126 }
??porta_isr_0:
        POP      {R0,PC}          ;; return
//  127 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  128 void LPLD_DMA_Isr(void)
//  129 {
//  130     ov7725_eagle_img_flag = IMG_FINISH;
LPLD_DMA_Isr:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable10_10
        STRB     R0,[R1, #+0]
//  131     DMA0->INT |= 0x1u << 0;//清除通道传输中断标志位
        LDR.N    R0,??DataTable10_7  ;; 0x40008024
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable10_7  ;; 0x40008024
        STR      R0,[R1, #+0]
//  132 }
        BX       LR               ;; return
//  133 
//  134 /*!
//  135  *  @brief      鹰眼ov7725采集图像（采集到的数据存储在 初始化时配置的地址上）
//  136  *  @since      v5.0
//  137  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  138 void ov7725_eagle_get_img()
//  139 {
ov7725_eagle_get_img:
        PUSH     {R7,LR}
//  140     
//  141     ov7725_eagle_img_flag = IMG_START;                   //开始采集图像
        MOVS     R0,#+4
        LDR.N    R1,??DataTable10_10
        STRB     R0,[R1, #+0]
//  142     PORTA->ISFR = ~0;                        //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
        MOVS     R0,#-1
        LDR.N    R1,??DataTable10_9  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  143     enable_irq(PORTA_IRQn);                         //允许PTA的中断
        MOVS     R0,#+87
        BL       NVIC_EnableIRQ
        B.N      ??ov7725_eagle_get_img_0
//  144     while(ov7725_eagle_img_flag != IMG_FINISH)           //等待图像采集完毕
//  145     {
//  146         if(ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
??ov7725_eagle_get_img_1:
        LDR.N    R0,??DataTable10_10
        LDRB     R0,[R0, #+0]
        CMP      R0,#+2
        BNE.N    ??ov7725_eagle_get_img_0
//  147         {
//  148             ov7725_eagle_img_flag = IMG_START;           //开始采集图像
        MOVS     R0,#+4
        LDR.N    R1,??DataTable10_10
        STRB     R0,[R1, #+0]
//  149             PORTA->ISFR = ~0;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
        MOVS     R0,#-1
        LDR.N    R1,??DataTable10_9  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  150             enable_irq(PORTA_IRQn);                 //允许PTA的中断
        MOVS     R0,#+87
        BL       NVIC_EnableIRQ
//  151         }
//  152     }
??ov7725_eagle_get_img_0:
        LDR.N    R0,??DataTable10_10
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??ov7725_eagle_get_img_1
//  153 }
        POP      {R0,PC}          ;; return
//  154 
//  155 
//  156 /*OV7725初始化配置表*/

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//  157 reg_s ov7725_eagle_reg[] =
ov7725_eagle_reg:
        DATA
        DC8 13, 193, 17, 0, 9, 3, 12, 208, 18, 64, 23, 63, 24, 80, 25, 3, 26
        DC8 120, 50, 0, 160, 10, 99, 224, 172, 255, 101, 12, 102, 0, 103, 0, 41
        DC8 20, 44, 30, 42, 0, 126, 12, 127, 22, 128, 42, 129, 78, 130, 97, 131
        DC8 111, 132, 123, 133, 134, 134, 142, 135, 151, 136, 164, 137, 175
        DC8 138, 197, 139, 215, 140, 232, 141, 32, 74, 0, 73, 19, 71, 8, 75, 20
        DC8 76, 23, 70, 5, 34, 153, 35, 3, 166, 4, 155, 0, 156, 255, 171, 6
        DC8 158, 17, 159, 2, 0, 0
//  158 {
//  159     //寄存器，寄存器值次
//  160     {OV7725_COM4         , 0xC1},
//  161     {OV7725_CLKRC        , 0x00},
//  162     {OV7725_COM2         , 0x03},
//  163     {OV7725_COM3         , 0xD0},
//  164     {OV7725_COM7         , 0x40},
//  165     {OV7725_HSTART       , 0x3F},
//  166     {OV7725_HSIZE        , 0x50},
//  167     {OV7725_VSTRT        , 0x03},
//  168     {OV7725_VSIZE        , 0x78},
//  169     {OV7725_HREF         , 0x00},
//  170     {OV7725_SCAL0        , 0x0A},
//  171     {OV7725_AWB_Ctrl0    , 0xE0},
//  172     {OV7725_DSPAuto      , 0xff},
//  173     {OV7725_DSP_Ctrl2    , 0x0C},
//  174     {OV7725_DSP_Ctrl3    , 0x00},
//  175     {OV7725_DSP_Ctrl4    , 0x00},
//  176 
//  177 #if (CAMERA_W == 80)
//  178     {OV7725_HOutSize     , 0x14},
//  179 #elif (CAMERA_W == 160)
//  180     {OV7725_HOutSize     , 0x28},
//  181 #elif (CAMERA_W == 240)
//  182     {OV7725_HOutSize     , 0x3c},
//  183 #elif (CAMERA_W == 320)
//  184     {OV7725_HOutSize     , 0x50},
//  185 #else
//  186 
//  187 #endif
//  188 
//  189 #if (CAMERA_H == 60 )
//  190     {OV7725_VOutSize     , 0x1E},
//  191 #elif (CAMERA_H == 120 )
//  192     {OV7725_VOutSize     , 0x3c},
//  193 #elif (CAMERA_H == 180 )
//  194     {OV7725_VOutSize     , 0x5a},
//  195 #elif (CAMERA_H == 240 )
//  196     {OV7725_VOutSize     , 0x78},
//  197 #else
//  198 
//  199 #endif
//  200 
//  201     {OV7725_EXHCH        , 0x00},
//  202     {OV7725_GAM1         , 0x0c},
//  203     {OV7725_GAM2         , 0x16},
//  204     {OV7725_GAM3         , 0x2a},
//  205     {OV7725_GAM4         , 0x4e},
//  206     {OV7725_GAM5         , 0x61},
//  207     {OV7725_GAM6         , 0x6f},
//  208     {OV7725_GAM7         , 0x7b},
//  209     {OV7725_GAM8         , 0x86},
//  210     {OV7725_GAM9         , 0x8e},
//  211     {OV7725_GAM10        , 0x97},
//  212     {OV7725_GAM11        , 0xa4},
//  213     {OV7725_GAM12        , 0xaf},
//  214     {OV7725_GAM13        , 0xc5},
//  215     {OV7725_GAM14        , 0xd7},
//  216     {OV7725_GAM15        , 0xe8},
//  217     {OV7725_SLOP         , 0x20},
//  218     {OV7725_LC_RADI      , 0x00},
//  219     {OV7725_LC_COEF      , 0x13},
//  220     {OV7725_LC_XC        , 0x08},
//  221     {OV7725_LC_COEFB     , 0x14},
//  222     {OV7725_LC_COEFR     , 0x17},
//  223     {OV7725_LC_CTR       , 0x05},
//  224     {OV7725_BDBase       , 0x99},
//  225     {OV7725_BDMStep      , 0x03},
//  226     {OV7725_SDE          , 0x04},
//  227     {OV7725_BRIGHT       , 0x00},
//  228     {OV7725_CNST         , 0xFF},
//  229     {OV7725_SIGN         , 0x06},
//  230     {OV7725_UVADJ0       , 0x11},
//  231     {OV7725_UVADJ1       , 0x02},
//  232 
//  233 };
//  234 

        SECTION `.data`:DATA:REORDER:NOROOT(0)
//  235 uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*结构体数组成员数目*/
ov7725_eagle_cfgnum:
        DATA
        DC8 49
//  236 
//  237 
//  238 /*鹰眼ov7725寄存器 初始化*/

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  239 uint8 ov7725_eagle_reg_init()
//  240 {
ov7725_eagle_reg_init:
        PUSH     {R4,LR}
        SUB      SP,SP,#+8
//  241     uint16 i = 0;
        MOVS     R4,#+0
//  242     uint8 Sensor_IDCode = 0;
        MOVS     R0,#+0
        STRB     R0,[SP, #+0]
//  243     SCCB_GPIO_Init();
        BL       SCCB_GPIO_Init
//  244 
//  245     ov7725_delay();
        BL       ov7725_delay
//  246     if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) ) /*复位sensor */
        MOVS     R1,#+128
        MOVS     R0,#+18
        BL       SCCB_WriteByte
        CMP      R0,#+0
        BNE.N    ??ov7725_eagle_reg_init_0
//  247     {
//  248         return 0 ;
        MOVS     R0,#+0
        B.N      ??ov7725_eagle_reg_init_1
//  249     }
//  250 
//  251     ov7725_delay();
??ov7725_eagle_reg_init_0:
        BL       ov7725_delay
//  252     if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER ) )    /* 读取sensor ID号*/
        MOVS     R2,#+11
        MOVS     R1,#+1
        ADD      R0,SP,#+0
        BL       SCCB_ReadByte
        CMP      R0,#+0
        BNE.N    ??ov7725_eagle_reg_init_2
//  253     {
//  254         return 0;
        MOVS     R0,#+0
        B.N      ??ov7725_eagle_reg_init_1
//  255     }
//  256 
//  257     if(Sensor_IDCode == OV7725_ID)
??ov7725_eagle_reg_init_2:
        LDRB     R0,[SP, #+0]
        CMP      R0,#+33
        BNE.N    ??ov7725_eagle_reg_init_3
//  258     {
//  259         for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
        MOVS     R4,#+0
        B.N      ??ov7725_eagle_reg_init_4
??ov7725_eagle_reg_init_5:
        ADDS     R4,R4,#+1
??ov7725_eagle_reg_init_4:
        LDR.N    R0,??DataTable10_13
        LDRB     R0,[R0, #+0]
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R4,R0
        BCS.N    ??ov7725_eagle_reg_init_6
//  260         {
//  261             if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
        LDR.N    R0,??DataTable10_14
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADDS     R0,R0,R4, LSL #+1
        LDRB     R1,[R0, #+1]
        LDR.N    R0,??DataTable10_14
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        LDRB     R0,[R0, R4, LSL #+1]
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        BL       SCCB_WriteByte
        CMP      R0,#+0
        BNE.N    ??ov7725_eagle_reg_init_5
//  262             {
//  263                 return 0;
        MOVS     R0,#+0
        B.N      ??ov7725_eagle_reg_init_1
//  264             }
//  265         }
//  266     }
//  267     else
//  268     {
//  269         return 0;
//  270     }
//  271     return 1;
??ov7725_eagle_reg_init_6:
        MOVS     R0,#+1
        B.N      ??ov7725_eagle_reg_init_1
??ov7725_eagle_reg_init_3:
        MOVS     R0,#+0
??ov7725_eagle_reg_init_1:
        POP      {R1,R2,R4,PC}    ;; return
//  272 }
//  273 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  274 void img_extract(void *dst, void *src, uint32 srclen)
//  275 {
img_extract:
        PUSH     {R3-R5}
//  276     uint8_t colour[2] = {255, 0}; //0 和 1 分别对应的颜色
        LDR.N    R3,??DataTable10_15
        LDRH     R3,[R3, #+0]
        STRH     R3,[SP, #+0]
//  277     uint8_t *mdst = dst;
//  278     uint8_t *msrc = src;
        B.N      ??img_extract_0
//  279     //注：山外的摄像头 0 表示 白色，1表示 黑色
//  280     uint8_t tmpsrc;
//  281     while (srclen--)
//  282     {
//  283         tmpsrc = *msrc++;
??img_extract_1:
        LDRB     R3,[R1, #+0]
        ADDS     R1,R1,#+1
//  284         *mdst++ = colour[(tmpsrc >> 7) & 0x01];
        ADD      R4,SP,#+0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ASRS     R5,R3,#+7
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  285         *mdst++ = colour[(tmpsrc >> 6) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+6,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  286         *mdst++ = colour[(tmpsrc >> 5) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+5,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  287         *mdst++ = colour[(tmpsrc >> 4) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+4,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  288         *mdst++ = colour[(tmpsrc >> 3) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+3,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  289         *mdst++ = colour[(tmpsrc >> 2) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+2,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  290         *mdst++ = colour[(tmpsrc >> 1) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+1,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  291         *mdst++ = colour[(tmpsrc >> 0) & 0x01];
        ADD      R4,SP,#+0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ANDS     R3,R3,#0x1
        LDRB     R3,[R3, R4]
        STRB     R3,[R0, #+0]
        ADDS     R0,R0,#+1
//  292     }
??img_extract_0:
        MOVS     R3,R2
        SUBS     R2,R3,#+1
        CMP      R3,#+0
        BNE.N    ??img_extract_1
//  293 }
        POP      {R0,R4,R5}
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  294 void lpld_sending(void *imgaddr, int32 imgsize)
//  295 {
lpld_sending:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//  296 #define CMD_IMG 1
//  297     int8 cmdf[2] = {CMD_IMG, ~CMD_IMG}; //山外上位机 使用的命令
        LDR.N    R0,??DataTable10_16
        LDRH     R0,[R0, #+0]
        STRH     R0,[SP, #+2]
//  298     int8 cmdr[2] = {~CMD_IMG, CMD_IMG}; //山外上位机 使用的命令
        LDR.N    R0,??DataTable10_17
        LDRH     R0,[R0, #+0]
        STRH     R0,[SP, #+0]
//  299 
//  300     LPLD_UART_PutCharArr(UART5, cmdf, sizeof(cmdf)); //先发送命令
        MOVS     R2,#+2
        ADD      R1,SP,#+2
        LDR.N    R0,??DataTable10_8  ;; 0x400eb000
        BL       LPLD_UART_PutCharArr
//  301 
//  302     LPLD_UART_PutCharArr(UART5, (int8 *)imgaddr, imgsize); //再发送图像
        MOVS     R2,R5
        MOVS     R1,R4
        LDR.N    R0,??DataTable10_8  ;; 0x400eb000
        BL       LPLD_UART_PutCharArr
//  303 
//  304     LPLD_UART_PutCharArr(UART5, cmdr, sizeof(cmdr)); //先发送命令
        MOVS     R2,#+2
        ADD      R1,SP,#+0
        LDR.N    R0,??DataTable10_8  ;; 0x400eb000
        BL       LPLD_UART_PutCharArr
//  305 }
        POP      {R0,R4,R5,PC}    ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10:
        DC32     0xe000e100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_1:
        DC32     0xe000e180

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_2:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_3:
        DC32     0x90012

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_4:
        DC32     0x400ff040

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_5:
        DC32     0x400ff050

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_6:
        DC32     imgbuff

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_7:
        DC32     0x40008024

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_8:
        DC32     0x400eb000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_9:
        DC32     0x400490a0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_10:
        DC32     ov7725_eagle_img_flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_11:
        DC32     0x4000800c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_12:
        DC32     0x40009010

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_13:
        DC32     ov7725_eagle_cfgnum

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_14:
        DC32     ov7725_eagle_reg

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_15:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_16:
        DC32     ?_1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_17:
        DC32     ?_2
//  306 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  307 void ov7725_delay(void)
//  308 {
//  309     uint16 i, n;
//  310     for (i = 0; i < 30000; i++)
ov7725_delay:
        MOVS     R0,#+0
        B.N      ??ov7725_delay_0
//  311     {
//  312         for (n = 0; n < 200; n++)
//  313         {
//  314             asm("nop");
??ov7725_delay_1:
        nop
//  315         }
        ADDS     R1,R1,#+1
??ov7725_delay_2:
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        CMP      R1,#+200
        BLT.N    ??ov7725_delay_1
        ADDS     R0,R0,#+1
??ov7725_delay_0:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVW     R1,#+30000
        CMP      R0,R1
        BGE.N    ??ov7725_delay_3
        MOVS     R1,#+0
        B.N      ??ov7725_delay_2
//  316     }
//  317 }
??ov7725_delay_3:
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(1)
?_0:
        DATA
        DC8 255, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(1)
?_1:
        DATA
        DC8 1, -2

        SECTION `.rodata`:CONST:REORDER:NOROOT(1)
?_2:
        DATA
        DC8 -2, 1

        END
// 
// 5 400 bytes in section .bss
//   102 bytes in section .data
//     6 bytes in section .rodata
// 1 072 bytes in section .text
// 
// 1 072 bytes of CODE  memory
//     6 bytes of CONST memory
// 5 502 bytes of DATA  memory
//
//Errors: none
//Warnings: none
