#include "All_Init.h"
#include "include.h"
#include "common.h"
#include "Steering.h"

#define NVIC_PriorityGroup_0          ((uint32)0x7) /* 0 bits for pre-emption priority                                                      4 bits for subpriority */#define NVIC_PriorityGroup_1          ((uint32)0x6) /* 1 bits for pre-emption priority                                                      3 bits for subpriority */#define NVIC_PriorityGroup_2          ((uint32)0x5) /* 2 bits for pre-emption priority                                                      2 bits for subpriority */#define NVIC_PriorityGroup_3          ((uint32)0x4) /* 3 bits for pre-emption priority                                                      1 bits for subpriority */#define NVIC_PriorityGroup_4          ((uint32)0x3) /* 4 bits for pre-emption priority                                                      0 bits for subpriority */
#define NVIC_PriorityGroup_1          ((uint32)0x6) /* 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PriorityGroup_2          ((uint32)0x5) /* 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PriorityGroup_3          ((uint32)0x4) /* 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PriorityGroup_4          ((uint32)0x3) /* 4 bits for pre-emption priority*/

extern uint8 imgbuff[CAMERA_SIZE]; //定义存储接收图像的数组
extern sPID SPID;

void NVIC_Init();
void OLED_init(void);
void GPIO_init(void);
void PORTD_IRQHandler(void);
void Key_IrqPTD7(void);
void Key_IrqPTD5(void);
void Key_IrqPTD3(void);
void TestInterrupt_Init();

void Beacon_Init()
{
    //GPIO_init();//LED灯 按键 遥控 拨码开关 
    //LCD_init();
          NVIC_Init();

    camera_init(imgbuff);

    //TestInterrupt_Init();
    //led_init(LED0);
    //led_init(LED1);
    //led_init(LED2);
    //led_init(LED3);
    //gpio_init(PTD5,GPI,1);//6
    //Steering_init();//舵机初始化 需要添加
    //spid_init(&SPID);            //电机PID参数的初始化
    //Motor_init();//电机初始化 需要添加
    //OLED_init();//OLED初始化 需要添加

    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn, PORTA_IRQHandler); //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn, DMA0_IRQHandler);   //设置DMA0的中断服务函数为 DMA0_IRQHandler
     
    //定时器中断初始化
    pit_init_ms(PIT1, 20);                              
    set_vector_handler(PIT1_VECTORn, PIT1_IRQHandler); 
    enable_irq(PIT1_IRQn);
    
    //NVIC_SetPriority(PIT1_IRQn,1);
    //NVIC_SetPriority(PORTA_IRQn,2);
    //NVIC_SetPriority(DMA0_IRQn,3);
    //按键中断初始化 LED初始化
    //set_vector_handler(PORTD_VECTORn ,PORTD_IRQHandler);    //设置PORTE的中断服务函数为 PORTE_IRQHandler
    //enable_irq (PORTD_IRQn);
    //set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler_KEY);    //设置PORTA的中断服务函数为 PORTA_IRQHandler
    //enable_irq (PORTA_IRQn); 
    //set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler_KEY);    //设置PORTE的中断服务函数为 PORTE_IRQHandler
    //enable_irq (PORTE_IRQn); 
}

void NVIC_Init()
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
    NVIC_SetPriority(PIT1_IRQn,5);
    NVIC_SetPriority(PORTA_IRQn,2);
    NVIC_SetPriority(DMA0_IRQn,0);
    NVIC_EnableIRQ(PIT1_IRQn);
    NVIC_EnableIRQ(PORTA_IRQn);
    NVIC_EnableIRQ(DMA0_IRQn);
}

void GPIO_init(void)
{
    gpio_init(PTB20,GPO,1);//灯
    gpio_init(PTB21,GPO,1);//重复
    gpio_init(PTB22,GPO,1);//重复
    gpio_init(PTB23,GPO,1);//灯
    
    gpio_init(PTA5,GPI,1);//5
    gpio_init(PTA7,GPI,1);//4
    gpio_init(PTA8,GPI,1);//2
    gpio_init(PTA9,GPI,1);//1
    gpio_init(PTE25,GPI,1);//3
    gpio_init(PTE27,GPI,1);//6
    
    port_init(PTD12, ALT1 | IRQ_RISING | PULLUP );//遥控 
    port_init(PTD13, ALT1 | IRQ_RISING | PULLUP ); 
    port_init(PTD14, ALT1 | IRQ_RISING | PULLUP );    
    
    
    port_init(PTA5, ALT1 | IRQ_FALLING | PULLUP );//key 
    port_init(PTA7, ALT1 | IRQ_FALLING | PULLUP );
    port_init(PTA8, ALT1 | IRQ_FALLING | PULLUP );
    port_init(PTA9, ALT1 | IRQ_FALLING | PULLUP );
    port_init(PTE25, ALT1 | IRQ_FALLING | PULLUP );
    port_init(PTE27, ALT1 | IRQ_FALLING | PULLUP );
}

void TestInterrupt_Init()//外部中断 换个引脚就行了
{
    port_init(PTD7,ALT1 | IRQ_FALLING | PULLUP);//下降沿中断
    //port_init(PTD3,ALT1 | IRQ_ZERO | PULLUP);//高电平中断
    //port_init(PTD5,ALT1 | IRQ_ZERO | PULLUP);//低电平中断
    set_vector_handler(PORTD_VECTORn,PORTD_IRQHandler);
    enable_irq (PORTD_IRQn);
}

void PORTD_IRQHandler()
{
    PORT_FUNC(D,7,Key_IrqPTD7);
    //PORT_FUNC(D,3,Key_IrqPTD3); 
    //PORT_FUNC(D,5,Key_IrqPTD5);
}

void Key_IrqPTD7()
{
    DELAY_MS(100);
    if (gpio_get(PTD7) == 0)//按键按下为低电平 若检测到低电平
    {
        led_turn(LED1);
    }
      
}

void Key_IrqPTD3()
{
    DELAY_MS(100);
    if (gpio_get(PTD3) == 1)//按键按下为低电平 若检测到低电平
    {
        led(LED2,LED_ON);    
    }
      
}

void Key_IrqPTD5()
{
    DELAY_MS(100);
    if (gpio_get(PTD5) == 0)//按键按下为低电平 若检测到低电平
    {
        led(LED3,LED_OFF);
    }
    else if(gpio_get(PTD5) == 1)
    {
        led(LED3,LED_ON);
    }
      
}
void OLED_init(void)
{
     LCD_Init();
     LCD_CLS();
}