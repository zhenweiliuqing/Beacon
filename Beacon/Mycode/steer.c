
#include "steer_control.h"
#include "math.h"
#include "include.h"

#define Steer_HZ 100
PD PDSteer;
//���PD�ṹ��
uint16 DutySteer;
//���ռ�ձ�
float duty=1480;
//��ʼ���ռ�ձ�


/*******************************************************/
/*                    ���PD��ʼ��                     */
/*******************************************************/
void PDSteer_Init(void)
{
    PDSteer.KP = 5.0;
    PDSteer.KD = 8.0;
    //΢�ֳ��� Derivative Const

    PDSteer.Error_0 = 0;
    //Error[0]
    PDSteer.Error_1 = 0;
    //Error[-1]

    PDSteer.SetPoint = OV7725_EAGLE_W/2 ;
    //�������� 64
}

/*******************************************************/
/*                      ���PD����                     */
/*******************************************************/
void PDSteer_Calculation(int16 NowPoint)      //���ڵ�����
{
    /************************* ���λ��ʽPD ***************************/
    PDSteer.Error_0 = NowPoint - PDSteer.SetPoint; /// SetPoint = 64
    //��ֵ  ��ֵƫ������ת����ֵƫ������ת

    duty = PDSteer.KP * PDSteer.Error_0
         + PDSteer.KD *(PDSteer.Error_0 - PDSteer.Error_1)
         + 1460;
    //ռ�ձ�����

    PDSteer.Error_1 = PDSteer.Error_0;

    /* �������޷� */
    if(duty<1280)
        duty=1280;
    if(duty>1640)
        duty=1640;

    DutySteer = (uint16) duty;
    ftm_pwm_init(FTM1, FTM_CH0, Steer_HZ, DutySteer);
    //���PWM���
}