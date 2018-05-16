//Time:2018-5-12
//Function:a new mode
//

#include "include.h"


typedef enum
{
  Mode1 = 1,
  Mode2,
} Mode;

uint8 imgbuff[CAMERA_SIZE]; //定义存储接收图像的数组
uint8 img[CAMERA_W * CAMERA_H];

void send_img(int mode);

void main()
{
    DisableInterrupts; 
    Beacon_Init();
    EnableInterrupts;

    while (1)
    {
        camera_get_img(); //摄像头获取图像
        img_extract(img, imgbuff, CAMERA_SIZE); //解压图像
        Image_Processing(img, 60, 80);     
        LCD_Display();
        //send_img(Mode2);
    }
}

void send_img(int mode)
{
     if (mode == Mode1)
     {
         vcan_sendimg(imgbuff, CAMERA_SIZE); //发送到上位机
     }
     else if (mode == Mode2)
     {
         img_extract(img, imgbuff, CAMERA_SIZE); //解压图像
         vcan_sendimg(img, CAMERA_W * CAMERA_H); //发送到上位机
     }
}