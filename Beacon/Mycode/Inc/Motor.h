#ifndef _MOTOR_H_
#define _MOTOR_H_
#define MOTOR1_IO   PTE5
#define MOTOR2_IO   PTE6
#define MOTOR3_IO   PTE7
#define MOTOR4_IO   PTE10

#define MOTOR_FTM   FTM3
#define MOTOR1_PWM  FTM_CH0
#define MOTOR2_PWM  FTM_CH1
#define MOTOR3_PWM  FTM_CH2
#define MOTOR4_PWM  FTM_CH5

#define MOTOR1_PWM_IO  FTM3_CH0
#define MOTOR2_PWM_IO  FTM3_CH1
#define MOTOR3_PWM_IO  FTM3_CH2
#define MOTOR4_PWM_IO  FTM3_CH5

//extern uint8 FLAG_STOP;                  //ֹͣ��־
#define MAX_SPEED  8000                //�����ٶ����ֵ
#define MIN_SPEED  2000                //�����ٶ���Сֵ

#define BANG_Trh   50                //���������ֵ
#define WEI_Trh    10                //����΢�����е���ֵ
#define Integration_Trh    50             //��������޷�����ֵ
#define Min_Speed  1200               //������С�ٶ�

#define MOTOR_HZ    (15*1000)
extern int16 l_result,r_result,l_error,r_error,result;
extern int16 motor_output;//������
typedef struct PID{
  int16 sp_motor;             //����趨ֵ
  
  
  float Kp_motor;                //Kp����
  float Ki_motor;                //Ki����
  float Kd_motor;                //Kd����
  
  int16 result;
  int16 l_output;
  int16 r_output;
  
  int16 l_result;
  int16 r_result;
  
  int16 l_error;
  int16 r_error;
  int16 motor_increment;
  
  int16 error;                  //����ƫ��
  int16 last_error;             //��һ��ƫ��
  int16 pre_error;              //���ϴ�ƫ��
  
  int16 integral;                //����
  
  int16 output;                 //�������
  int16 last_output;            //�ϴ����
  int16 pre_output;             //���ϴ����
  
  int16 PD_Diff_output;         //���ٵ����
  
}sPID;
void Motor_init();
void Motor_test();
void spid_init(sPID *spid);
void pid_calculation(sPID *spid,int8 Mid,int16 vertical);
#endif