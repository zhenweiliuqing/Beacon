//Time:2018-5-12
//Function:a new mode
//

#include "include.h"

void delay200ns();
void  delay1us();
void  delay10us();
void  delay100us();
void delay10ms();
typedef enum
{
  Mode1 = 1,
  Mode2,
} Mode;

#define NUM 5

uint8 imgbuff[CAMERA_SIZE]; //定义存储接收图像的数组
uint8 img[CAMERA_W * CAMERA_H];
Light *light;
int lox;
int save[NUM] = {0};
int final_x;

void send_img(int mode);
int correct_x(int x);

int correct_x(int x)
{
    int i;
    //int result;
    
    for (i = 0; i < NUM - 1; i++)
    {
         save[i] = save[i + 1]; 
    }
    save[NUM - 1] = x;
    
    for (i =0 ;i < NUM;i++)
    {
        if (save[i] != 0)
        {
            final_x = save[i];
            break;
        }
    }
    
    for (i = 0; i < NUM; i++)
    {
        //printf("%d\t",save[i]);
    }
    //printf("%d\n",final_x);
    
    return final_x;
}

void main()
{
    DisableInterrupts; 
    Beacon_Init();
    EnableInterrupts;
    //uint16 duty = 1800;
    while (1)
    {
        /*
        ftm_pwm_init(FTM0, FTM_CH1, 100, duty);
        delay10ms();
        delay10ms();
        duty += 10;
        if (duty == 2340)
            duty = 1800;
        printf("%d\n",duty);*/
        camera_get_img(); //摄像头获取图像
        //vcan_sendimg(imgbuff, CAMERA_SIZE); //发送到上位机

        img_extract(img, imgbuff, CAMERA_SIZE); //解压图像
        lox = Image_Processing(img, 60, 80,light);  
        lox = correct_x(lox);
        //printf("%d\t",lox);
        vcan_sendimg(img, CAMERA_W * CAMERA_H); //发送到上位机
        //PD_calculation((uint8)lox);

        /*
        if (lox <= 30)
        {
               ftm_pwm_init(FTM0, FTM_CH1, 100, 2000);
        }
        else if (lox <= 55)
        {
               ftm_pwm_init(FTM0, FTM_CH1, 100, 2140);
        }
        else 
        {
               ftm_pwm_init(FTM0, FTM_CH1, 100, 2280);
        }
         */
        //LCD_Display();
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

void  delay200ns()
{
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");//һ��asm("nop")��8ns;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}
void  delay1us()
{
    delay200ns();delay200ns();delay200ns();delay200ns();delay200ns();

}
void  delay10us()
{
    delay1us();delay1us();delay1us();delay1us();delay1us();
    delay1us();delay1us();delay1us();delay1us();delay1us();
}
void  delay100us()
{
    delay10us();delay10us();delay10us();delay10us();delay10us();
    delay10us();delay10us();delay10us();delay10us();delay10us();
}

void delay10ms()
{
    int i;
    for ( i = 0; i < 100; i++)
    delay100us();
}