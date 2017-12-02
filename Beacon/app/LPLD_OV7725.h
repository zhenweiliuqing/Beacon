#ifndef _LPLD_OV7725_H_
#define _LPLD_OV7725_H_

//配置摄像头的特性
//#define CAMERA_USE_HREF     0               //是否使用 行中断 (0 为 不使用，1为使用)
//#define CAMERA_COLOR        0               //摄像头输出颜色 ， 0 为 黑白二值化图像 ，1 为 灰度 图像 ，2 为 RGB565 图像
//#define CAMERA_POWER        0               //摄像头 电源选择， 0 为 3.3V ,1 为 5V

//配置摄像头顶层接口
#define camera_init()           OV7725_Init()
extern void OV7725_Init(void);

#define camera_get_img()        ov7725_eagle_get_img()
#define camera_vsync()          ov7725_eagle_vsync()
#define camera_dma()            ov7725_eagle_dma()
extern void ov7725_eagle_get_img(void);
extern void ov7725_eagle_vsync(void);
extern void ov7725_eagle_dma(void);
extern void ov7725_delay(void);

#define ARR_SIZE(a) (sizeof((a)) / sizeof(((a)[0])))
//配置 摄像头 参数
#define CAMERA_DMA_CH       DMA_CH0         //定义摄像头的DMA采集通道
#define CAMERA_W            80             //定义摄像头图像宽度
#define CAMERA_H            60              //定义摄像头图像高度
#define CAMERA_SIZE         ( CAMERA_H * CAMERA_W/8 )          //图像占用空间大小
#define CAMERA_DMA_NUM      CAMERA_SIZE        //DMA采集次数


//内部函数声明
extern uint8 ov7725_eagle_reg_init(void); //ov7725寄存器初始化

extern void OV7725_GPIO_Init(void); //ov7725GPIO初始化 PTA27pclk 29vsync
extern void OV7725_DMA_Init(void);  //ov7725DMA初始化
extern void NVIC_Init(void);
extern void UART_Init(void);

extern void porta_isr();    //vsync中断函数
extern void LPLD_DMA_Isr(); //DMA中断函数

extern void lpld_sending(void *imgaddr, int32 imgsize);
extern void img_extract(void *dst, void *src, uint32 srclen);



typedef struct {
    uint8 addr; /*寄存器地址*/
    uint8 val;  /*寄存器值*/
}reg_s;

//定义图像采集状态
typedef enum {
    IMG_NOTINIT = 0,
    IMG_FINISH, //图像采集完毕
    IMG_FAIL,   //图像采集失败(采集行数少了)
    IMG_GATHER, //图像采集中
    IMG_START,  //开始采集图像
    IMG_STOP,   //禁止图像采集
}IMG_STATUS_e;

#endif

