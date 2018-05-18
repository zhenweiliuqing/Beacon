#include "common.h"
#include "include.h"
#include "Steering.h"

extern uint8 Speed_UP,Speed_Down,Speed_Mid;

extern uint8 Speed_UP,Speed_Down,Speed_Mid;

//PD ��������
PD pdvar;  

void PD_init()
{
    pdvar.setpoint = 40;  
    pdvar.error = 0;
    pdvar.last_error = 0;
    pdvar.duty = 2140;
    
    pdvar.Proportion_1 = 12;
    pdvar.Derivative_1 = 0;
      
    pdvar.Proportion_2 = 0;
    pdvar.Derivative_2 = 0;
    
}

void Steering_init()
{
    PD_init();
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,2140);      //��ʼ�� ��� PWM
}

/**************************************************/
/*                    PD�����ļ���                */
/*************************************************/

void PD_calculation(const uint8 Mid)
{

    pdvar.error = pdvar.setpoint - Mid;  
    
    pdvar.duty = (uint16)(pdvar.Proportion_1 * pdvar.error + pdvar.Derivative_1 * (pdvar.error - pdvar.last_error) + 2140);
   
    pdvar.last_error = pdvar.error;
    
   if(pdvar.duty >= DUTY_MAX)                                //���PID��ֹ��ߺ���������
     pdvar.duty = DUTY_MAX;
   else if(pdvar.duty <= DUTY_MIN)
     pdvar.duty = DUTY_MIN; 
   
   //ftm_pwm_duty(S3010_FTM,S3010_CH,pdvar.duty); 
   printf("%d\t%d\n",Mid,pdvar.duty);
}


/*******************************************************/
/*                    ���PD��ʼ��                     */
/*******************************************************/

/*
void PDSteer_Init(void)
{
    PDSteer.P1 = 4.5;
    PDSteer.P2 = 7.0;
    //������KP�е�A,C

    PDSteer.KD = 8.0;
    //΢�ֳ��� Derivative Const

    PDSteer.Error_0 = 0;
    //Error[0]
    PDSteer.Error_1 = 0;
    //Error[-1]

    PDSteer.SetPoint = 64 ;
    //�������� 64
}
*/

/*******************************************************/
/*                      ���PD����                     */
/*******************************************************/
#if 0
void PD_calculation(PD *pdvar,uint8 Mid)     //���ڵ�����
{
    /************************* ���λ��ʽPD ***************************/
    PDSteer.Error_0 = NowPoint - PDSteer.SetPoint; /// SetPoint = 64
    //��ֵ  ��ֵƫ������ת����ֵƫ������ת

    if ( fabs(PDSteer.Error_0) <= 10)
    {
        PDSteer.KP = PDSteer.P1;
    }
    if ( fabs(PDSteer.Error_0) > 10)
    {
        PDSteer.KP = PDSteer.P1;
    }
    if ( LeftLose == 2 || RightLose == 2 )
    {
        PDSteer.KP = PDSteer.P2;
        LeftLose = 0;
        RightLose = 0;

    }

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
}
#endif

    
void Steering_test()
{
    int i;



        for(i = 2140;i<2210;i+=20)
        {
            ftm_pwm_duty(S3010_FTM, S3010_CH,i);
            DELAY_MS(1000);
            printf("%d\n",i);
            
        }

        for(;i>2020;i-=20)
        {
            ftm_pwm_duty(S3010_FTM, S3010_CH,i);
            DELAY_MS(1000);
            printf("%d\n",i);
            
        }    
    

}