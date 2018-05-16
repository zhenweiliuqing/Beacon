#include "InitHandler.h"
#include "common.h"
#include "include.h"

void PIT1_IRQHandler(void)
{
    Flag_5ms++;
    Flag_10ms++;
    Flag_20ms++;
    Flag_50ms++;
    Flag_100ms++;
    Flag_200ms++;

    if (Flag_20ms == 20)
    {
        if ((rtdis < 505) && (rtdis != 0))
            m = 1;
        else
            m = 0;
    }

    if (m == 0)
    {
        if (Flag_5ms == 5)
        {
            ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM, 2000);
            ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM, 0);
            ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM, 0);
            ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM, 2000);
        }
        if (Flag_10ms == 10)
        {
            //printf("���ߵĺ�����Ϊ��%d\r\n",mid_3);
            PD_calculation(&pd_var, mid_3);
        }
        if (Flag_50ms == 50)
        {
            gpio_turn(PTB20);
            gpio_turn(PTB21);
            gpio_turn(PTB22);
            gpio_turn(PTB23);
        }
    }
    else if (m == 1)
    {
        if (Flag_5ms == 5)
        {
            ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM, 2000);
            ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM, 0);
            ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM, 0);
            ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM, 2000);
        }
        if (Flag_10ms == 10)
        {
            ftm_pwm_init(S3010_FTM, S3010_CH, S3010_HZ, 2340);
        }
        if (Flag_50ms == 50)
        {
            gpio_turn(PTB20);
            gpio_turn(PTB21);
            gpio_turn(PTB22);
            gpio_turn(PTB23);
        }
    }

    if (Flag_5ms == 5)
        Flag_5ms = 0;
    if (Flag_10ms == 10)
        Flag_10ms = 0;
    if (Flag_20ms == 20)
        Flag_20ms = 0;
    if (Flag_50ms == 50)
        Flag_50ms = 0;
    if (Flag_100ms == 100)
        Flag_100ms = 0;
    if (Flag_200ms == 200)
        Flag_200ms = 0;
    PIT_Flag_Clear(PIT1); //���жϱ�־λ
}

/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler(void)
{
    uint8 n = 0; //引脚号
    uint32 flag = PORTA_ISFR;
    PORTA_ISFR = ~0; //清中断标志位

    n = 29;              //场中断
    if (flag & (1 << n)) //PTA29触发中断
    {
        camera_vsync();
    }
#if 0 //鹰眼直接全速采集，不需要行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif
}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler(void)
{
    camera_dma();
}