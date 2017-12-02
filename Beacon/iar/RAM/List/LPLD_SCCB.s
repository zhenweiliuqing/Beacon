///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       01/Dec/2017  15:29:33
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\LPLD_SCCB.c
//    Command line =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\LPLD_SCCB.c
//        -D LPLD_K60 -D USE_K60F12 -lCN
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\RAM\List\
//        -lB
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\RAM\List\
//        -o
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\RAM\Obj\
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
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\RAM\List\LPLD_SCCB.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_GPIO_Init
        EXTERN __aeabi_memcpy4

        PUBLIC SCCB_GPIO_Init
        PUBLIC SCCB_ReadByte
        PUBLIC SCCB_WriteByte

// E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\LPLD_SCCB.c
//    1 #include "common.h"
//    2 #include "LPLD_SCCB.h"
//    3 
//    4 static void SCCB_delay(uint16 i);

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    5 static void SCCB_delay(volatile uint16 i)
//    6 {
SCCB_delay:
        PUSH     {R0}
        B.N      ??SCCB_delay_0
//    7     while(i)
//    8     {
//    9         i--;
??SCCB_delay_1:
        LDRH     R0,[SP, #+0]
        SUBS     R0,R0,#+1
        STRH     R0,[SP, #+0]
//   10     }
??SCCB_delay_0:
        LDRH     R0,[SP, #+0]
        CMP      R0,#+0
        BNE.N    ??SCCB_delay_1
//   11 }
        ADD      SP,SP,#+4
        BX       LR               ;; return
//   12 
//   13 
//   14 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   15 void SCCB_GPIO_Init(void)
//   16 {
SCCB_GPIO_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   17    GPIO_InitTypeDef gpio_init_struct;
//   18     /*璁剧疆涓篜ULLUP*/
//   19    gpio_init_struct.GPIO_PTx = PTA;
        LDR.N    R0,??DataTable7  ;; 0x400ff000
        STR      R0,[SP, #+4]
//   20    gpio_init_struct.GPIO_Pins = GPIO_Pin25|GPIO_Pin26;
        MOVS     R0,#+100663296
        STR      R0,[SP, #+8]
//   21    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//   22    gpio_init_struct.GPIO_Output = OUTPUT_H; //锟斤拷始锟斤拷锟斤拷锟轿拷撸锟�
        MOVS     R0,#+1
        STRB     R0,[SP, #+17]
//   23    gpio_init_struct.GPIO_PinControl = OUTPUT_OD_EN|INPUT_PULL_UP;
        MOVS     R0,#+35
        STR      R0,[SP, #+12]
//   24    
//   25    LPLD_GPIO_Init(gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   26 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   27 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   28 static uint8 SCCB_Start(void)
//   29 {
SCCB_Start:
        PUSH     {R7,LR}
//   30     SDA_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   31     SCL_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//   32     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   33 
//   34     SDA_DDR_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//   35     if(!SDA_IN())
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??SCCB_Start_0
//   36     {
//   37         SDA_DDR_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//   38         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_Start_1
//   39     }
//   40     SDA_DDR_OUT();
??SCCB_Start_0:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//   41     SDA_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   42 
//   43     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   44     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   45 
//   46     if(SDA_IN())
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??SCCB_Start_2
//   47     {
//   48         SDA_DDR_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//   49         return 0;   /* SDA绾夸负楂樼數骞冲垯鎬荤嚎鍑洪敊,閫€鍑� */
        MOVS     R0,#+0
        B.N      ??SCCB_Start_1
//   50     }
//   51     //SDA_DDR_OUT();
//   52     //SDA_L();
//   53     //SCCB_delay();
//   54     return 1;
??SCCB_Start_2:
        MOVS     R0,#+1
??SCCB_Start_1:
        POP      {R1,PC}          ;; return
//   55 }
//   56 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   57 static void SCCB_Stop(void)
//   58 {
SCCB_Stop:
        PUSH     {R7,LR}
//   59     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   60     //SCCB_DELAY();
//   61     SDA_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   62     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   63     SCL_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//   64     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   65     SDA_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   66     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   67 }
        POP      {R0,PC}          ;; return
//   68 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   69 static void SCCB_Ack(void)
//   70 {
SCCB_Ack:
        PUSH     {R7,LR}
//   71     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   72     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   73     SDA_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   74     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   75     SCL_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//   76     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   77     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   78     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   79 }
        POP      {R0,PC}          ;; return
//   80 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   81 static void SCCB_NoAck(void)
//   82 {
SCCB_NoAck:
        PUSH     {R7,LR}
//   83     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   84     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   85     SDA_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   86     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   87     SCL_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//   88     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   89     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   90     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//   91 }
        POP      {R0,PC}          ;; return
//   92 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   93 static int SCCB_WaitAck(void)
//   94 {
SCCB_WaitAck:
        PUSH     {R7,LR}
//   95     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//   96     //SDA_H();
//   97     SDA_DDR_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//   98 
//   99     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//  100     SCL_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  101 
//  102     SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//  103 
//  104     if(SDA_IN())           //搴旂瓟涓洪珮鐢靛钩锛屽紓甯革紝閫氫俊澶辫触
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??SCCB_WaitAck_0
//  105     {
//  106         SDA_DDR_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  107         SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  108         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_WaitAck_1
//  109     }
//  110     SDA_DDR_OUT();
??SCCB_WaitAck_0:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  111     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  112     return 1;
        MOVS     R0,#+1
??SCCB_WaitAck_1:
        POP      {R1,PC}          ;; return
//  113 }
//  114 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  115 static void SCCB_SendByte(uint8 SendByte)
//  116 {
SCCB_SendByte:
        PUSH     {R3-R5,LR}
        MOVS     R5,R0
//  117     uint8 i = 8;
        MOVS     R4,#+8
        B.N      ??SCCB_SendByte_0
//  118     while(i--)
//  119     {
//  120 
//  121         if(SendByte & 0x80)     //SDA 杈撳嚭鏁版嵁
//  122         {
//  123             SDA_H();
//  124         }
//  125         else
//  126         {
//  127             SDA_L();
??SCCB_SendByte_1:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  128         }
//  129         SendByte <<= 1;
??SCCB_SendByte_2:
        LSLS     R5,R5,#+1
//  130         SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//  131         SCL_H();                //SCL 鎷夐珮锛岄噰闆嗕俊鍙�
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  132         SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//  133         SCL_L();                //SCL 鏃堕挓绾挎媺浣�
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
??SCCB_SendByte_0:
        MOVS     R0,R4
        SUBS     R4,R0,#+1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??SCCB_SendByte_3
        LSLS     R0,R5,#+24
        BPL.N    ??SCCB_SendByte_1
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
        B.N      ??SCCB_SendByte_2
//  134         //SCCB_DELAY();
//  135     }
//  136     //SCL_L();
//  137 }
??SCCB_SendByte_3:
        POP      {R0,R4,R5,PC}    ;; return
//  138 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  139 static int SCCB_ReceiveByte(void)
//  140 {
SCCB_ReceiveByte:
        PUSH     {R3-R5,LR}
//  141     uint8 i = 8;
        MOVS     R4,#+8
//  142     uint8 ReceiveByte = 0;
        MOVS     R5,#+0
//  143 
//  144     //SDA_H();
//  145     //SCCB_DELAY();
//  146     SDA_DDR_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
        B.N      ??SCCB_ReceiveByte_0
//  147 
//  148     while(i--)
//  149     {
//  150         ReceiveByte <<= 1;
??SCCB_ReceiveByte_1:
        LSLS     R5,R5,#+1
//  151         SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  152         SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//  153         SCL_H();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  154         SCCB_DELAY();
        MOV      R0,#+400
        BL       SCCB_delay
//  155 
//  156         if(SDA_IN())
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??SCCB_ReceiveByte_0
//  157         {
//  158             ReceiveByte |= 0x01;
        ORRS     R5,R5,#0x1
//  159         }
//  160 
//  161 
//  162     }
??SCCB_ReceiveByte_0:
        MOVS     R0,R4
        SUBS     R4,R0,#+1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BNE.N    ??SCCB_ReceiveByte_1
//  163     SDA_DDR_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  164     SCL_L();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  165     return ReceiveByte;
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R0,R5
        POP      {R1,R4,R5,PC}    ;; return
//  166 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DC32     0x43fe0064

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DC32     0x43fe0068

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_3:
        DC32     0x43fe02e4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_4:
        DC32     0x43fe0264
//  167 
//  168 static int SCCB_WriteByte_one( uint16 WriteAddress , uint8 SendByte );
//  169 
//  170 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  171 int SCCB_WriteByte( uint16 WriteAddress , uint8 SendByte )            //鑰冭檻鍒扮敤sccb鐨勭鑴氭ā鎷燂紝姣旇緝瀹规槗澶辫触锛屽洜姝ゅ璇曞嚑娆�
//  172 {
SCCB_WriteByte:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//  173     uint8 i = 0;
        MOVS     R6,#+0
//  174     while( 0 == SCCB_WriteByte_one ( WriteAddress, SendByte ) )
??SCCB_WriteByte_0:
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        BL       SCCB_WriteByte_one
        CMP      R0,#+0
        BNE.N    ??SCCB_WriteByte_1
//  175     {
//  176         i++;
        ADDS     R6,R6,#+1
//  177         if(i == 20)
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        CMP      R6,#+20
        BNE.N    ??SCCB_WriteByte_0
//  178         {
//  179             return 0 ;
        MOVS     R0,#+0
        B.N      ??SCCB_WriteByte_2
//  180         }
//  181     }
//  182     return 1;
??SCCB_WriteByte_1:
        MOVS     R0,#+1
??SCCB_WriteByte_2:
        POP      {R4-R6,PC}       ;; return
//  183 }
//  184 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  185 int SCCB_WriteByte_one( uint16 WriteAddress , uint8 SendByte )
//  186 {
SCCB_WriteByte_one:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//  187     if(!SCCB_Start())
        BL       SCCB_Start
        CMP      R0,#+0
        BNE.N    ??SCCB_WriteByte_one_0
//  188     {
//  189         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_WriteByte_one_1
//  190     }
//  191     SCCB_SendByte( DEV_ADR );                    /* 鍣ㄤ欢鍦板潃 */
??SCCB_WriteByte_one_0:
        MOVS     R0,#+66
        BL       SCCB_SendByte
//  192     if( !SCCB_WaitAck() )
        BL       SCCB_WaitAck
        CMP      R0,#+0
        BNE.N    ??SCCB_WriteByte_one_2
//  193     {
//  194         SCCB_Stop();
        BL       SCCB_Stop
//  195         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_WriteByte_one_1
//  196     }
//  197     SCCB_SendByte((uint8)(WriteAddress & 0x00FF));   /* 璁剧疆浣庤捣濮嬪湴鍧€ */
??SCCB_WriteByte_one_2:
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       SCCB_SendByte
//  198     SCCB_WaitAck();
        BL       SCCB_WaitAck
//  199     SCCB_SendByte(SendByte);
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       SCCB_SendByte
//  200     SCCB_WaitAck();
        BL       SCCB_WaitAck
//  201     SCCB_Stop();
        BL       SCCB_Stop
//  202     return 1;
        MOVS     R0,#+1
??SCCB_WriteByte_one_1:
        POP      {R1,R4,R5,PC}    ;; return
//  203 }
//  204 
//  205 static int SCCB_ReadByte_one(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress);
//  206 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  207 int SCCB_ReadByte(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress)
//  208 {
SCCB_ReadByte:
        PUSH     {R3-R7,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  209     uint8 i = 0;
        MOVS     R7,#+0
//  210     while( 0 == SCCB_ReadByte_one(pBuffer, length, ReadAddress) )
??SCCB_ReadByte_0:
        MOVS     R2,R6
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R1,R5
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R0,R4
        BL       SCCB_ReadByte_one
        CMP      R0,#+0
        BNE.N    ??SCCB_ReadByte_1
//  211     {
//  212         i++;
        ADDS     R7,R7,#+1
//  213         if(i == 30)
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R7,#+30
        BNE.N    ??SCCB_ReadByte_0
//  214         {
//  215             return 0 ;
        MOVS     R0,#+0
        B.N      ??SCCB_ReadByte_2
//  216         }
//  217     }
//  218     return 1;
??SCCB_ReadByte_1:
        MOVS     R0,#+1
??SCCB_ReadByte_2:
        POP      {R1,R4-R7,PC}    ;; return
//  219 }
//  220 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  221 int SCCB_ReadByte_one(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress)
//  222 {
SCCB_ReadByte_one:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  223     if(!SCCB_Start())
        BL       SCCB_Start
        CMP      R0,#+0
        BNE.N    ??SCCB_ReadByte_one_0
//  224     {
//  225         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_ReadByte_one_1
//  226     }
//  227     SCCB_SendByte( DEV_ADR );         /* 鍣ㄤ欢鍦板潃 */
??SCCB_ReadByte_one_0:
        MOVS     R0,#+66
        BL       SCCB_SendByte
//  228     if( !SCCB_WaitAck() )
        BL       SCCB_WaitAck
        CMP      R0,#+0
        BNE.N    ??SCCB_ReadByte_one_2
//  229     {
//  230         SCCB_Stop();
        BL       SCCB_Stop
//  231         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_ReadByte_one_1
//  232     }
//  233     SCCB_SendByte( ReadAddress );           /* 璁剧疆浣庤捣濮嬪湴鍧€ */
??SCCB_ReadByte_one_2:
        MOVS     R0,R6
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       SCCB_SendByte
//  234     SCCB_WaitAck();
        BL       SCCB_WaitAck
//  235     SCCB_Stop();
        BL       SCCB_Stop
//  236 
//  237     if(!SCCB_Start())
        BL       SCCB_Start
        CMP      R0,#+0
        BNE.N    ??SCCB_ReadByte_one_3
//  238     {
//  239         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_ReadByte_one_1
//  240     }
//  241     SCCB_SendByte( DEV_ADR + 1 );               /* 鍣ㄤ欢鍦板潃 */
??SCCB_ReadByte_one_3:
        MOVS     R0,#+67
        BL       SCCB_SendByte
//  242 
//  243     if(!SCCB_WaitAck())
        BL       SCCB_WaitAck
        CMP      R0,#+0
        BNE.N    ??SCCB_ReadByte_one_4
//  244     {
//  245         SCCB_Stop();
        BL       SCCB_Stop
//  246         return 0;
        MOVS     R0,#+0
        B.N      ??SCCB_ReadByte_one_1
//  247     }
//  248     while(length)
//  249     {
//  250         *pBuffer = SCCB_ReceiveByte();
//  251         if(length == 1)
//  252         {
//  253             SCCB_NoAck();
//  254         }
//  255         else
//  256         {
//  257             SCCB_Ack();
??SCCB_ReadByte_one_5:
        BL       SCCB_Ack
//  258         }
//  259         pBuffer++;
??SCCB_ReadByte_one_6:
        ADDS     R4,R4,#+1
//  260         length--;
        SUBS     R5,R5,#+1
??SCCB_ReadByte_one_4:
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        CMP      R5,#+0
        BEQ.N    ??SCCB_ReadByte_one_7
        BL       SCCB_ReceiveByte
        STRB     R0,[R4, #+0]
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        CMP      R5,#+1
        BNE.N    ??SCCB_ReadByte_one_5
        BL       SCCB_NoAck
        B.N      ??SCCB_ReadByte_one_6
//  261     }
//  262     SCCB_Stop();
??SCCB_ReadByte_one_7:
        BL       SCCB_Stop
//  263     return 1;
        MOVS     R0,#+1
??SCCB_ReadByte_one_1:
        POP      {R4-R6,PC}       ;; return
//  264 }

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
// 
// 880 bytes in section .text
// 
// 880 bytes of CODE memory
//
//Errors: none
//Warnings: none
