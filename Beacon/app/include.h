#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 *
#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
#include  "MK60_i2c.h"      //I2C
#include  "MK60_spi.h"      //SPI
#include  "MK60_ftm.h"      //FTM
#include  "MK60_pit.h"      //PIT
#include  "MK60_rtc.h"      //RTC
#include  "MK60_adc.h"      //ADC
#include  "MK60_dac.h"      //DAC
#include  "MK60_dma.h"      //DMA
#include  "MK60_FLASH.h"    //FLASH
*/
#include  "LPLD_LED.H"          //LED
#include  "LPLD_KEY.H"          //KEY
#include  "LPLD_MMA7455.h"      //三轴加速度MMA7455
#include  "LPLD_NRF24L0.h"      //无线模块NRF24L01+
#include  "LPLD_RTC_count.h"    //RTC 时间转换
#include  "LPLD_camera.h"       //摄像头总头文件





#include  "LPLD_computer.h"     //多功能调试助手
#endif  //__INCLUDE_H__
