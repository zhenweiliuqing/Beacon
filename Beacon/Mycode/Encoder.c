#include "include.h"
#include "common.h"



extern int16 result;                            //���ҵ��ת��ƽ��ֵ

void Encoder_init()
{
//    printf("\n*****FTM �������� ����*****\n");

    ftm_quad_init(FTM1);                                    //FTM1 ���������ʼ�������õĹܽſɲ� port_cfg.h ��A12 A13��
    ftm_quad_init(FTM2);                                    //A10  A11��

//    pit_init_ms(PIT0, 500);                                 //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
//   set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
//    NVIC_SetPriority(PIT0_IRQn,1);         //�������ȼ�
 //   enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�

 //   while(1);
}

/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
/*
void PIT0_IRQHandler(void)
{

    int16 right;
    int16 left;
    right = ftm_quad_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
    left = ftm_quad_get(FTM2);          //��ȡFTM �������� ��������(������ʾ������)
    ftm_quad_clean(FTM1);
    ftm_quad_clean(FTM2);

    if(left>=0)
    {
        printf("\n���ַ�ת��%d",left);
    }
    else
    {
        printf("\n������ת��%d",-left);
    }
    if(right>=0)
    {
        printf("\n������ת��%d",right);
    }
    else
    {
        printf("\n���ַ�ת��%d",-right);
    }

    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}
*/
