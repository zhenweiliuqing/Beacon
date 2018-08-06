#include "common.h"
#include "DifSpeed.h"

//PD���ٱ���������
PD_Diff PD_diff;

void PD_Diff_init()
{
    PD_diff.Diff_Kp = 10;           //����Kpֵ
    PD_diff.Diff_Kd = 0;            //����Kdֵ
    
    PD_diff.error = 0;              //����ƫ��ֵ
    PD_diff.last_error = 0;         //������һ��ƫ��ֵ
    
    PD_diff.Diff_output = 0;        //�������ֵ 
}

int16 PD_Diff_calculation(uint8 Mid)         //����PID�ļ���--����CCD����ֵ
{
    PD_diff.error = 40 - Mid;                 //�õ�ƫ��ֵ
   //λ��ʽPD����
    PD_diff.Diff_output = (int16)(PD_diff.Diff_Kp * PD_diff.error
                                + PD_diff.Diff_Kd * (PD_diff.error - PD_diff.last_error));
    //��������ֵ
    PD_diff.last_error = PD_diff.error;
    //�޷�����
    if(PD_diff.Diff_output >= Diff_Output_Max)   PD_diff.Diff_output = Diff_Output_Max;
    if(PD_diff.Diff_output <= -Diff_Output_Max)  PD_diff.Diff_output = -Diff_Output_Max;
    
    return PD_diff.Diff_output;
}
