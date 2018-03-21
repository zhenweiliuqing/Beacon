#ifndef _STEER_CONTROL_H_
#define _STEER_CONTROL_H_

#include "VCAN_OV7725_Eagle.h"
#include "common.h"

typedef struct _PD        //λ��ʽPD
{    
    float KP;     
    //�������� Proportional Const
    float KD;     
    //΢�ֳ��� Derivative Const
    
    int SetPoint;         
    //�趨Ŀ�� Desired V alue
    int Error_0;
    int Error_1;        

}PD;
extern void steerParm_Init(void);
extern void steer_Calculation(int16 NowPoint);

#endif
