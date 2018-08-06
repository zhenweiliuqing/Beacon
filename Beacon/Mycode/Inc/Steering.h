#ifndef _STEERING_H_
#define _STEERING_H_
#define S3010_FTM   FTM0
#define S3010_CH    FTM_CH1//C2
#define S3010_HZ    (100)

#define DUTY_MAX  2340
#define DUTY_MIN  1940      
#define DUTY_MID  2140
#define Coefficient_Trh    10               //�������ƫ��ϵ����ֵ 

typedef struct PD {
 
     unsigned char setpoint;          //�趨ֵ
     
     float Proportion_1;        //����ϵ��
     float Derivative_1;        //΢��ϵ��
     
     float Proportion_2;        //���ϵ��  
     float Derivative_2;        //���ϵ��
     
     int16      error;         //ƫ��
     int16 last_error;        //��һ��ƫ��
     int Gyro_error;
     int duty;             //ռ�ձȵ�ֵ
}PD;

void Steering_init();
void Steering_test();

//��ʼ��PD����
void PD_init(PD *pdvar);
//PD�ļ���
void PD_calculation(PD *pdvar,int8 Mid);

#endif