///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       02/Dec/2017  09:26:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\Beacon.c
//    Command line =  
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\Beacon.c
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
//        E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\iar\RAM\List\Beacon.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN OV7725_Init
        EXTERN imgbuff
        EXTERN lpld_sending
        EXTERN ov7725_eagle_get_img

        PUBLIC main

// E:\K60singlechip\Code\LPLD_OSKinetis_V3\LPLD_Beacon\Beacon\app\Beacon.c
//    1 /**
//    2  * --------------基于"拉普兰德K60底层库V3"的工程（Beacon）-----------------
//    3  * @file Beacon.c
//    4  * @version 0.0
//    5  * @date 2013-9-29
//    6  * @brief 关于该工程的描述
//    7  *
//    8  * 版权所有:北京拉普兰德电子技术有限公司
//    9  * http://www.lpld.cn
//   10  * mail:support@lpld.cn
//   11  * 硬件平台:  LPLD K60 Card / LPLD K60 Nano
//   12  *
//   13  * 本工程基于"拉普兰德K60底层库V3"开发，
//   14  * 所有开源代码均在"lib"文件夹下，用户不必更改该目录下代码，
//   15  * 所有用户工程需保存在"project"文件夹下，以工程名定义文件夹名，
//   16  * 底层库使用方法见相关文档。 
//   17  *
//   18  */
//   19 #include "common.h"
//   20 #include "LPLD_OV7725.h"
//   21 #include "LPLD_SCCB.h"
//   22 extern uint8 imgbuff[CAMERA_SIZE];
//   23 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   24 void main (void)
//   25 {
main:
        PUSH     {R7,LR}
//   26   camera_init();
        BL       OV7725_Init
//   27 
//   28   while(1)
//   29   {
//   30       camera_get_img();
??main_0:
        BL       ov7725_eagle_get_img
//   31       #if 1
//   32       lpld_sending(imgbuff,CAMERA_SIZE);
        MOV      R1,#+600
        LDR.N    R0,??main_1
        BL       lpld_sending
        B.N      ??main_0
        Nop      
        DATA
??main_1:
        DC32     imgbuff
//   33       #else 
//   34       img_extract(img,imgbuff,CAMERA_SIZE);
//   35       lpld_sending(img,CAMERA_W*CAMERA_H);
//   36       #endif
//   37   } 
//   38 }

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   39 /*
//   40 void Get_Img_Start(void)
//   41 {
//   42 	ov7725_eagle_img_flag = IMG_START;
//   43 	PORTA->ISFR = ~0;//写1清中断标志位
//   44 	enable_irq((IRQn_Type)(PORTA_IRQn));//使能中断
//   45 }
//   46 
//   47 void Get_Img_Wait(void)
//   48 {
//   49 	while (ov7725_eagle_img_flag != IMG_FINISH)
//   50 	{
//   51 		if (ov7725_eagle_img_flag == IMG_FAIL)
//   52 		{
//   53 			ov7725_eagle_img_flag = IMG_START;
//   54 			PORTA->ISFR = 0xFFFFFFFFu;
//   55 			enable_irq(PORTA_IRQn);
//   56 		}
//   57 	}
//   58 }*/
// 
// 28 bytes in section .text
// 
// 28 bytes of CODE memory
//
//Errors: none
//Warnings: none
