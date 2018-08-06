#include "common.h"//706
#include "include.h"

int16 l_result,r_result,l_error,r_error,result;
//int16 result,l_output,r_output;                            //���ҵ��ת��ƽ��ֵ
float motor_increment = 0;      
//����ʽPID���������
int16 motor_output;//������
extern int Expect;//���� ������ ��ʱ���ж���
//���PID����������
sPID SPID;
uint8 Mid_error = 0;                             //�����ٶȿ�������ƫ��
extern PD_Diff PD_diff;

extern int Actual_speed;//����

extern float motor_kp;
extern float motor_ki;
extern float motor_kd;
extern int motor_except;//�������


void Motor_init()
{
    ftm_pwm_init(MOTOR_FTM, MOTOR1_PWM,MOTOR_HZ,5000);      //��ʼ�� ��� PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR2_PWM,MOTOR_HZ,5000);      //��ʼ�� ��� PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR3_PWM,MOTOR_HZ,5000);      //��ʼ�� ��� PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR4_PWM,MOTOR_HZ,5000);      //��ʼ�� ��� PWM
}
void Motor_test()
{
        int i = 3000;
        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,i);
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,0);
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,0);
        ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,i);
}

//΢������PID�Ĳ���
void spid_init(sPID *spid)                           //�ٶ�PID�ĳ�ʼ��
{
    spid->sp_motor =motor_except;                                            //����趨ֵ
  
    spid->Kp_motor = motor_kp;                                                 //Kp����
    spid->Ki_motor = motor_ki;                                                 //Ki����
    spid->Kd_motor = motor_kd;                                                  //Kd����

    spid->error = 0;                                                   //����ƫ��
    spid->last_error = 0;                                            //��һ��ƫ��
    spid->pre_error = 0;                                             //���ϴ�ƫ��
    
    spid->output = 0;
    spid->last_output = 0;
    spid->pre_output = 0;
    
    spid->PD_Diff_output = 0;                                     //�������Ϊ0
} 

//΢�����е�PID�㷨
void pid_calculation(sPID *spid,int8 Mid,int16 vertical)
{
  //  spid->sp_motor=3800-vertical*60;
 // if(vertical>140){spid->sp_motor=200;}
 // else {spid->sp_motor=160-4.5*vertical;}
  if(vertical<140){  spid->sp_motor=30;}
 // else 
  else {spid->sp_motor=20;}//40 20    140 350
    Expect=spid->sp_motor;
 //   spid->l_result=-(ftm_quad_get(FTM2));
  //  l_result=-ftm_quad_get(FTM2);
  //  spid->r_result=(ftm_quad_get(FTM1));
  //  r_result=ftm_quad_get(FTM1);
   // ftm_quad_clean(FTM1);
   // ftm_quad_clean(FTM2);
    l_result=-ftm_quad_get(FTM2);
     ftm_quad_clean(FTM2);
    r_result=ftm_quad_get(FTM1);
    ftm_quad_clean(FTM1);

    spid->l_result=l_result;
 
    spid->r_result=r_result;
    spid->result=(spid->l_result+spid->r_result)/2;
    Actual_speed=spid->result;
    spid->l_error = spid->sp_motor-spid->l_result;
    spid->r_error = spid->sp_motor-spid->r_result;
    
//    spid->r_output = spid->r_output+spid->Kp_motor*spid->r_error;
//    spid->l_output = spid->l_output+spid->Kp_motor*spid->l_error;
//    ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,spid->l_output);
//    l_result=spid->l_result;
//    r_result=spid->r_result;

#if 0//20
    ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,0);
    ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,0);
    ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,2000);
    ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,2097);

#else     
    spid->error = spid->sp_motor - spid->result; 
                       //�趨ֵ-����ֵ 
//    if(spid->error<=0){spid->Kp_motor=0.5;}
  //  else {spid->Kp_motor = motor_kp; }
    if(spid->error > Integration_Trh)  
        spid->motor_increment = spid->Kp_motor * spid->error
                    - spid->Ki_motor * spid->integral*0.8;
                  //      + spid->Kd_motor *(spid->error-spid->last_error);
    else
        spid->motor_increment = spid->Kp_motor * spid->error
                 -spid->Ki_motor * spid->integral*0.8;
                 //       + spid->Kd_motor *(spid->error-spid->last_error);
    //motor_duty = (int16)((float)motor_duty + motor_increment);
    //motor_duty = (int16)((float)motor_duty + motor_increment);
    //spid->output = motor_duty;                                       //����޷�����
    
    spid->output = (int16)((float)spid->last_output + spid->motor_increment);
    
    motor_output=spid->output;
    
            //��������ֵ
    spid ->pre_error = spid ->last_error;
    spid ->last_error = spid ->error;
    spid ->pre_output = spid->last_output;
    spid ->last_output = spid->output;
    spid->integral+=spid->error;
    
      if(spid->integral>200)
      {
        spid->integral=200;
      }
      else if(spid->integral<-200)
      {
        spid->integral=-200;
      } 
    if(spid->output >8200)     
        spid->output = 8200;     
    if(spid->output <0)      
        spid->output =0;      

        spid->PD_Diff_output = PD_Diff_calculation(Mid);

    if(spid->output - spid->PD_Diff_output >= 0 && spid->output + spid->PD_Diff_output >= 0)                                         //��ת
    {
         //����
         ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,              0);
         ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,   spid->output - spid->PD_Diff_output);
         //�ҵ��
         ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,   spid->output + spid->PD_Diff_output);
         ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,              0);
    }
    else if(spid->output - spid->PD_Diff_output >= 0 && spid->output + spid->PD_Diff_output <= 0)                                         //��ת
    {    
        //                                                                                            
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,                0);
        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,     spid->output - spid->PD_Diff_output);
        //
        ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,                0);      
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,    -(spid->output + spid->PD_Diff_output));
    }
    else if(spid->output - spid->PD_Diff_output <= 0 && spid->output + spid->PD_Diff_output >= 0)                                         //��ת
    {    
        //
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,      -(spid->output - spid->PD_Diff_output));          
        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,                0);
        //
        ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,      spid->output + spid->PD_Diff_output);      
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,                0);
    }
    else
    {    
        //
        ftm_pwm_duty(FTM0, MOTOR2_PWM,     -(spid->output - spid->PD_Diff_output)); 
        ftm_pwm_duty(FTM0, MOTOR1_PWM,                0);
        //
        ftm_pwm_duty(FTM0, MOTOR4_PWM,                0);      
        ftm_pwm_duty(FTM0, MOTOR3_PWM,    -(spid->output + spid->PD_Diff_output));
    }
#endif
//��������ʾ�����������ʾ
    

    
}

