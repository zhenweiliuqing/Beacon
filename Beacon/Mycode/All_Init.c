#include "All_Init.h"
#include "include.h"
#include "common.h"

extern uint8 imgbuff[CAMERA_SIZE]; //定义存储接收图像的数组


void Beacon_Init()
{
    LCD_init();
    camera_init(imgbuff);
    
    steer_init();//舵机初始化 需要添加
    motor_init();//电机初始化 需要添加
    key_init();//按键初始化 需要添加
    remote_init();//遥控初始化 需要添加
    OLED_init();//OLED初始化 需要添加

    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn, PORTA_IRQHandler); //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn, DMA0_IRQHandler);   //设置DMA0的中断服务函数为 DMA0_IRQHandler

    pit_init_ms(PIT1, 1);                              //
    set_vector_handler(PIT1_VECTORn, PIT1_IRQHandler); //
    enable_irq(PIT1_IRQn);
}
