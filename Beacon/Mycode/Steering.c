#include "common.h"
#include "include.h"


extern int GyrozGet;

//PD ��������
PD pd_var;  
extern int steering_output;//������

void PD_init(PD *pdvar)
{
    pdvar->setpoint = 40;  
    pdvar->error = 0;
    pdvar->last_error = 0;
    pdvar->duty = 2140;
    
    pdvar->Proportion_1 = 5.0;
    pdvar->Derivative_1 = 0.1;
      
    pdvar->Proportion_2 = 1.0;
    pdvar->Derivative_2 = 8.0;
    
}

void Steering_init()
{
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,2140);      //��ʼ�� ��� PWM
}

/**************************************************/
/*                    PD�����ļ���                */
/*************************************************/
void PD_calculation(PD *pdvar,int8 Mid)
{

    pdvar->error = pdvar->setpoint - Mid;   
 //   pdvar->Gyro_error=(GetData(GYRO_XOUT_H)>>3)+5;
    
    //if(Speed_UP == 1 || Speed_Mid == 1)
    //{
        pd_var.duty = pdvar->Proportion_1 * pdvar->error
              //      - pdvar->Derivative_1*pdvar->Gyro_error
          -GyrozGet*pdvar->Derivative_1
                      + DUTY_MID;
                      //pdvar->Derivative_1 * (pdvar->error - pdvar->last_error)+ DUTY_MID;
               //     + DUTY_MID-0.1*GyrozGet;
     
    //}
#if 0
    else if(Speed_Down == 1)
    {
        pd_var.duty = pdvar->Proportion_2 * pdvar->error
                    + 
                      pdvar->Derivative_2 * (pdvar->error - pdvar->last_error)
                    + DUTY_MID;
    }
#endif
    
//    pdvar->last_error = pdvar->error;
    
   if(pd_var.duty >= DUTY_MAX)                                //���PID��ֹ��ߺ���������
     pd_var.duty = DUTY_MAX;
   else if(pd_var.duty <= DUTY_MIN)
      pd_var.duty = DUTY_MIN; 
    steering_output= pd_var.duty;
   ftm_pwm_duty(S3010_FTM,S3010_CH,(uint32)pd_var.duty); 

}

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