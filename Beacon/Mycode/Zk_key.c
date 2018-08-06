#include "include.h"
#include "common.h"

//float motor_kp=0.5;
float motor_kp=3;
float motor_ki=0.04;
float motor_kd=0.1;
//int motor_except=80;
int motor_except=20;
extern sPID SPID;
extern PD pd_var;
void ZK_keyinit()
{
gpio_init(PTA9,GPI,1);//3
gpio_init(PTA8,GPI,1);//6float motor_kp=0.5;
gpio_init(PTA7,GPI,1);//3
gpio_init(PTA5,GPI,1);//6float motor_kp=0.5;

gpio_init(PTE25,GPI,1);//3
gpio_init(PTE27,GPI,1);//6float motor_kp=0.5;

/*
gpio_init(PTB20,GPO,1);
gpio_init(PTB21,GPO,1);
gpio_init(PTB22,GPO,1);
gpio_init(PTB23,GPO,1);
*/
port_init(PTA9, ALT1 | IRQ_FALLING | PULLUP );
port_init(PTA8, ALT1 | IRQ_FALLING | PULLUP );
port_init(PTA7, ALT1 | IRQ_FALLING | PULLUP );
port_init(PTA5, ALT1 | IRQ_FALLING | PULLUP );

port_init(PTE25, ALT1 | IRQ_FALLING | PULLUP );
port_init(PTE27, ALT1 | IRQ_FALLING | PULLUP );
 //   set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler_KEY);    //设置PORTE的中断服务函数为 PORTE_IRQHandler
 //   enable_irq (PORTA_IRQn); 

    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler_KEY);    //设置PORTE的中断服务函数为 PORTE_IRQHandler
    enable_irq (PORTE_IRQn); 
}
/*
void PORTA_IRQHandler_KEY(void)
{


    PORT_FUNC(A,9,ZKkey1);//1
    PORT_FUNC(A,8,ZKkey2);//2
    PORT_FUNC(A,7,ZKkey4);//4
    PORT_FUNC(A,5,ZKkey5);//5
}
*/
void PORTE_IRQHandler_KEY(void)
{


    PORT_FUNC(E,25,ZKkey3);//3
    PORT_FUNC(E,27,ZKkey6);//6

}
void ZKkey1(void)
{
  while(!gpio_get(PTA9));
  motor_kp+=0.01;
  if(motor_kp>3){motor_kp=3;}
  DisplayFloat((motor_kp*10000),66,0);
  spid_init(&SPID);            //电机PID参数的初始化
  gpio_turn (PTB20);
}
void ZKkey2(void)
{
  while(!gpio_get(PTA8));
  motor_kp-=0.01;
  if(motor_kp<0){motor_kp=0;}
  DisplayFloat((motor_kp*10000),66,0);
  spid_init(&SPID);            //电机PID参数的初始化
  gpio_turn (PTB23);
}
void ZKkey3(void)
{
  while(!gpio_get(PTE25));
  motor_ki+=0.01;
//  motor_except+=5;
  DisplayFloat((motor_ki*10000),66,2);
  spid_init(&SPID);            //电机PID参数的初始化
  gpio_turn (PTB20);
}
void ZKkey4(void)
{
  while(!gpio_get(PTA7));
  motor_ki-=0.01;
  DisplayFloat((motor_ki*10000),66,2);
  spid_init(&SPID);            //电机PID参数的初始化
  gpio_turn (PTB23);
}
void ZKkey5(void)
{
  while(!gpio_get(PTA5));
  motor_except+=20;
  if(motor_except>200){motor_except=200;}
  motor_kd+=0.01;
  DisplayFloat((motor_kd*10000),66,4);
  spid_init(&SPID);            //电机PID参数的初始化
  gpio_turn (PTB20);
}
void ZKkey6(void)
{
  while(!gpio_get(PTE27));
  motor_except-=20;
  if(motor_except<0){motor_except=0;}
  motor_kd-=0.01;
  DisplayFloat((motor_kd*10000),66,4);
  spid_init(&SPID);            //电机PID参数的初始化
  gpio_turn (PTB23);
}