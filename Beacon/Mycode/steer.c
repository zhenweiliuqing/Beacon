
#include "steer_control.h"
#include "math.h"
#include "include.h"

#define Steer_HZ 100
PD PDSteer;
//舵机PD结构体
uint16 DutySteer;
//舵机占空比
float duty=1480;
//初始舵机占空比


/*******************************************************/
/*                    舵机PD初始化                     */
/*******************************************************/
void PDSteer_Init(void)
{
    PDSteer.KP = 5.0;
    PDSteer.KD = 8.0;
    //微分常数 Derivative Const

    PDSteer.Error_0 = 0;
    //Error[0]
    PDSteer.Error_1 = 0;
    //Error[-1]

    PDSteer.SetPoint = OV7725_EAGLE_W/2 ;
    //理论中线 64
}

/*******************************************************/
/*                      舵机PD计算                     */
/*******************************************************/
void PDSteer_Calculation(int16 NowPoint)      //现在的中线
{
    /************************* 舵机位置式PD ***************************/
    PDSteer.Error_0 = NowPoint - PDSteer.SetPoint; /// SetPoint = 64
    //差值  正值偏左往右转，负值偏右往左转

    duty = PDSteer.KP * PDSteer.Error_0
         + PDSteer.KD *(PDSteer.Error_0 - PDSteer.Error_1)
         + 1460;
    //占空比增量

    PDSteer.Error_1 = PDSteer.Error_0;

    /* 舵机打脚限幅 */
    if(duty<1280)
        duty=1280;
    if(duty>1640)
        duty=1640;

    DutySteer = (uint16) duty;
    ftm_pwm_init(FTM1, FTM_CH0, Steer_HZ, DutySteer);
    //舵机PWM输出
}