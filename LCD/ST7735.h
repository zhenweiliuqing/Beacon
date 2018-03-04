#ifndef _ST7735_H_
#define _ST7735_H_

#include "common.h"

#define RED 0XF800   //红色
#define GREEN 0X07E0 //绿色
#define BLUE 0X001F  //蓝色
#define BRED 0XF81F
#define GRED 0XFFE0   //灰色
#define GBLUE 0X07FF  //
#define BLACK 0X0000  //黑色
#define WHITE 0XFFFF  //白色
#define YELLOW 0xFFE0 //黄色

#define FCOLOUR BLUE //定义字体颜色
#define BCOLOUR RED  //定义背景颜色

//LCD 的管脚定义
#define LCD_ST7735R_WR PTC9
#define LCD_ST7735R_RD PTC10
#define LCD_ST7735R_CS PTC11
#define LCD_ST7735R_RS PTC12
#define LCD_ST7735R_RST PTC13

#define LCD_ST7735R_P0 PTC_B0_OUT
#define PTC_B0_OUT PT_BYTE(C, 0, PDOR)

#define LCD_ST7735R_WR_OUT PTC9_O
#define LCD_ST7735R_RD_OUT PTC10_O
#define LCD_ST7735R_CS_OUT PTC11_O
#define LCD_ST7735R_RS_OUT PTC12_O
#define LCD_ST7735R_RST_OUT PTC13_O

#define PT(X, n, REG) BITBAND_REG(PT##X##_BASE_PTR->##REG, n) //位操作
#define PT_BYTE(X, n, REG) (((Dtype *)(&(PT##X##_BASE_PTR->##REG)))->B[n]) 
//等价于PTX_BASE_PTR->REG->B[n]
//Dtype 为什么就可以实现官方文件里的内容？

#define LCD_RAMWR() LCD_ST7735R_WR_8CMD(0x2C) //写模式
#define LCD_WR_DATA(data)                           \
    do                                              \
    {                                               \
        LCD_ST7735R_WR_8DATA((uint8)((data) >> 8)); \
        LCD_ST7735R_WR_8DATA((uint8)(data));        \
    } while (0) //写数据
#define LCD_ST7735R_WR_8CMD(cmd)       \
    do                                 \
    {                                  \
        LCD_ST7735R_RD_OUT = 1;        \
        LCD_ST7735R_RS_OUT = 0;        \
        LCD_ST7735R_CS_OUT = 0;        \
        LCD_ST7735R_P0 = (uint8)(cmd); \
        LCD_ST7735R_WR_OUT = 0;        \
        LCD_ST7735R_WR_OUT = 1;        \
        LCD_ST7735R_CS_OUT = 1;        \
    } while (0) //LCD_WR=0;LCD_WR=1;产生一个上升沿

#define LCD_ST7735R_WR_8DATA(data)      \
    do                                  \
    {                                   \
        LCD_ST7735R_RD_OUT = 1;         \
        LCD_ST7735R_RS_OUT = 1;         \
        LCD_ST7735R_CS_OUT = 0;         \
        LCD_ST7735R_P0 = (uint8)(data); \
        LCD_ST7735R_WR_OUT = 0;         \
        LCD_ST7735R_WR_OUT = 1;         \
        LCD_ST7735R_CS_OUT = 1;         \
    } while (0) //LCD_WR=0;在这里写入数据到RAM

/*
 * 定义带位域的联合体类型
 */
typedef union {
    uint32 DW;
    uint16 W[2];
    uint8 B[4];
    struct
    {
        uint32 b0 : 1;
        uint32 b1 : 1;
        uint32 b2 : 1;
        uint32 b3 : 1;
        uint32 b4 : 1;
        uint32 b5 : 1;
        uint32 b6 : 1;
        uint32 b7 : 1;
        uint32 b8 : 1;
        uint32 b9 : 1;
        uint32 b10 : 1;
        uint32 b11 : 1;
        uint32 b12 : 1;
        uint32 b13 : 1;
        uint32 b14 : 1;
        uint32 b15 : 1;
        uint32 b16 : 1;
        uint32 b17 : 1;
        uint32 b18 : 1;
        uint32 b19 : 1;
        uint32 b20 : 1;
        uint32 b21 : 1;
        uint32 b22 : 1;
        uint32 b23 : 1;
        uint32 b24 : 1;
        uint32 b25 : 1;
        uint32 b26 : 1;
        uint32 b27 : 1;
        uint32 b28 : 1;
        uint32 b29 : 1;
        uint32 b30 : 1;
        uint32 b31 : 1;
    };
} Dtype; //sizeof(Dtype) 为 4

typedef struct
{
    uint16 x;
    uint16 y;
}Site_t;

/*
 * 定义矩形大小结构体
 */
typedef struct
{
    uint16 W; //宽
    uint16 H; //高
} Size_t;

void LCD_init(void);//爸爸
void LCD_INIT();//儿子
void LCD_ST7735_init(void);//儿子

void ST7735R_DELAY();
void ST7735R_DELAY_MS(uint16);
#endif