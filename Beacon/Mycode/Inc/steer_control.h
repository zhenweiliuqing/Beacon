#ifndef _STEER_CONTROL_H_
#define _STEER_CONTROL_H_

#include "VCAN_OV7725_Eagle.h"
#include "common.h"

typedef struct _PD        //位置式PD
{    
    float KP;     
    //比例常数 Proportional Const
    float KD;     
    //微分常数 Derivative Const
    
    int SetPoint;         
    //设定目标 Desired V alue
    int Error_0;
    int Error_1;        

}PD;
extern void steerParm_Init(void);
extern void steer_Calculation(int16 NowPoint);

#endif
