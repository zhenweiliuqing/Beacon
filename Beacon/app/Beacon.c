/**
 * --------------基于"拉普兰德K60底层库V3"的工程（Beacon）-----------------
 * @file Beacon.c
 * @version 0.0
 * @date 2013-9-29
 * @brief 关于该工程的描述
 *
 * 版权所有:北京拉普兰德电子技术有限公司
 * http://www.lpld.cn
 * mail:support@lpld.cn
 * 硬件平台:  LPLD K60 Card / LPLD K60 Nano
 *
 * 本工程基于"拉普兰德K60底层库V3"开发，
 * 所有开源代码均在"lib"文件夹下，用户不必更改该目录下代码，
 * 所有用户工程需保存在"project"文件夹下，以工程名定义文件夹名，
 * 底层库使用方法见相关文档。 
 *
 */
#include "common.h"
#include "LPLD_OV7725.h"
#include "LPLD_SCCB.h"
extern uint8 imgbuff[CAMERA_SIZE];

void main (void)
{
  camera_init();

  while(1)
  {
      camera_get_img();
      #if 1
      lpld_sending(imgbuff,CAMERA_SIZE);
      #else 
      img_extract(img,imgbuff,CAMERA_SIZE);
      lpld_sending(img,CAMERA_W*CAMERA_H);
      #endif
  } 
}
/*
void Get_Img_Start(void)
{
	ov7725_eagle_img_flag = IMG_START;
	PORTA->ISFR = ~0;//写1清中断标志位
	enable_irq((IRQn_Type)(PORTA_IRQn));//使能中断
}

void Get_Img_Wait(void)
{
	while (ov7725_eagle_img_flag != IMG_FINISH)
	{
		if (ov7725_eagle_img_flag == IMG_FAIL)
		{
			ov7725_eagle_img_flag = IMG_START;
			PORTA->ISFR = 0xFFFFFFFFu;
			enable_irq(PORTA_IRQn);
		}
	}
}*/