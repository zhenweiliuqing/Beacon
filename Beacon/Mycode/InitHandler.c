#include "InitHandler.h"
#include "common.h"
#include "include.h"

uint8 Flag_20ms = 0;
extern int lox;
extern PD pdvar;
int num = 0;
extern uint8 imgbuff[CAMERA_SIZE]; 

void PIT1_IRQHandler(void)
{
    
        //uint32 time = 0;
        //pit_time_start  (PIT0);
    
    
        camera_get_img(); //摄像头获取图像
        vcan_sendimg(imgbuff, CAMERA_SIZE); //发送到上位机
        //time = pit_time_get_ms    (PIT0);
        //printf("%dms\n",time);
    PIT_Flag_Clear(PIT1); 
}



/*
void PORTD_IRQHandler(void)
{
  //  PORT_FUNC(D,11,key_handler1);
    PORT_FUNC(D,12,key_handler2);
    PORT_FUNC(D,13,key_handler3);
    PORT_FUNC(D,14,key_handler4);

}

void key_handler2(void)
{
   //j+=1;gpio_turn(PTB22);if(j>4)j=1;
}

void key_handler3(void)
{
    disable_irq(PIT1_IRQn);
    ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,0);
    ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,0);
    ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,0);
    ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,0);
}

void key_handler4(void)
{
    enable_irq(PIT1_IRQn); 
}

void PORTA_IRQHandler_KEY(void)
{
    PORT_FUNC(A,5,ZKkey5);//5
    PORT_FUNC(A,7,ZKkey4);//4
    PORT_FUNC(A,8,ZKkey2);//2
    PORT_FUNC(A,9,ZKkey1);//1
}

void PORTE_IRQHandler_KEY(void)
{
    PORT_FUNC(E,25,ZKkey3);//3
    PORT_FUNC(E,27,ZKkey6);//6
}
*/

void PORTA_IRQHandler_KEY(void)
{
    //PORT_FUNC(A,5,ZKkey5);//5
    //PORT_FUNC(A,7,ZKkey4);//4
    //PORT_FUNC(A,8,ZKkey2);//2
    PORT_FUNC(A,9,ZKkey1);//1
}

void ZKkey1(void)
{
  while(!gpio_get(PTA9));
         num+=1;
  //pdvar.Kp1 += 0.1;
  
  //DisplayFloat((pdvar.Kp1*1000),66,0);
  
  //gpio_turn (PTB20);
}
/*
void ZKkey2(void)
{
  while(!gpio_get(PTA8));
  Proportion_1-=0.1;
  DisplayFloat((Proportion_1*1000),66,0);
  PD_init(&pd_var);      //鑸垫満鍙傛暟鍒濆鍖�
  gpio_turn (PTB23);
}

void ZKkey3(void)
{
  while(!gpio_get(PTE25));
  Derivative_1+=0.1;
  DisplayFloat((Derivative_1*1000),66,2);
  PD_init(&pd_var);      //鑸垫満鍙傛暟鍒濆鍖�
  gpio_turn (PTB20);
}

void ZKkey4(void)
{
  while(!gpio_get(PTA7));
  Derivative_1-=0.1;
  DisplayFloat((Derivative_1*1000),66,2);
  PD_init(&pd_var);      //鑸垫満鍙傛暟鍒濆鍖�
  gpio_turn (PTB23);
}

void ZKkey5(void)
{
  while(!gpio_get(PTA5));
  Kp_motor+=0.1;
  DisplayFloat((Kp_motor*1000),66,4);
  spid_init(&SPID);            //鐢垫満PID鍙傛暟鐨勫垵濮嬪寲
  gpio_turn (PTB20);
}

void ZKkey6(void)
{
  while(!gpio_get(PTE27));
  Kp_motor-=0.1;
  DisplayFloat((Kp_motor*1000),66,4);
  spid_init(&SPID);            //鐢垫満PID鍙傛暟鐨勫垵濮嬪寲
  gpio_turn (PTB23);
}
*/

/*void PIT1_IRQHandler(void)
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
            //printf("锟斤拷锟竭的猴拷锟斤拷锟斤拷为锟斤拷%d\r\n",mid_3);
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
    PIT_Flag_Clear(PIT1); //锟斤拷锟叫断憋拷志位
}*/

/*!
 *  @brief      PORTA涓柇鏈嶅姟鍑芥暟
 *  @since      v5.0
 */
void PORTA_IRQHandler(void)
{
    uint8 n = 0; //寮曡剼鍙�
    uint32 flag = PORTA_ISFR;
    PORTA_ISFR = ~0; //娓呬腑鏂爣蹇椾綅

    n = 29;              //鍦轰腑鏂�
    if (flag & (1 << n)) //PTA29瑙﹀彂涓柇
    {
        camera_vsync();
    }
#if 0 //楣扮溂鐩存帴鍏ㄩ€熼噰闆嗭紝涓嶉渶瑕佽涓柇
    n = 28;
    if(flag & (1 << n))                                 //PTA28瑙﹀彂涓柇
    {
        camera_href();
    }
#endif
}

/*!
 *  @brief      DMA0涓柇鏈嶅姟鍑芥暟
 *  @since      v5.0
 */
void DMA0_IRQHandler(void)
{
    camera_dma();
}