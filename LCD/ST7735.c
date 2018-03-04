#include "common.h"
#include "ST7735.h"

#define ST7735R_H 128
#define ST7735R_W 128
#define LCD_H ST7735R_get_h() //高
#define LCD_W ST7735R_get_w() //宽

uint16 st7735r_h = ST7735R_H;
uint16 st7735r_w = ST7735R_W;

void LCD_init()
{
    Site_t site = {0, 0};
    Size_t size;

    LCD_ST7735_init(void); //初始化LCD

    size.W = LCD_W;
    size.H = LCD_H;
    LCD_rectangle(site, size, BCOLOUR); //初始化背景
}
void LCD_ST7735_init(void)
{
    uint8 n;
    GPIO_InitTypeDef gpio_init_struct;

    //管脚定义
    gpio_init_struct.GPIO_PTx = PTC;
    gpio_init_struct.GPIO_Pins = GPIO_Pin0_7; //数据口
    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;//输出
    gpio_init_struct.GPIO_Output = OUTPUT_L;//输出低电平
    LPLD_GPIO_Init(gpio_init_struct);

    gpio_init_struct.GPIO_PTx = PTC;
    gpio_init_struct.GPIO_Pins = GPIO_Pin9; //WR
    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;   //输出
    gpio_init_struct.GPIO_Output = OUTPUT_L;  //输出低电平
    gpio_init_struct.GPIO_PinControl = OUTPUT_DSH;//高驱动力
    LPLD_GPIO_Init(gpio_init_struct);

    gpio_init_struct.GPIO_PTx = PTC;
    gpio_init_struct.GPIO_Pins = GPIO_Pin10; //RD
    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;   //输出
    gpio_init_struct.GPIO_Output = OUTPUT_H;  //输出高电平
    gpio_init_struct.GPIO_PinControl = OUTPUT_DSH; //高驱动力
    LPLD_GPIO_Init(gpio_init_struct);

    gpio_init_struct.GPIO_PTx = PTC;
    gpio_init_struct.GPIO_Pins = GPIO_Pin11; //CS
    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;   //输出
    gpio_init_struct.GPIO_Output = OUTPUT_H;  //输出高电平
    gpio_init_struct.GPIO_PinControl = OUTPUT_DSH; //高驱动力
    LPLD_GPIO_Init(gpio_init_struct);

    gpio_init_struct.GPIO_PTx = PTC;
    gpio_init_struct.GPIO_Pins = GPIO_Pin12; //RS
    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;   //输出
    gpio_init_struct.GPIO_Output = OUTPUT_L;  //输出低电平
    gpio_init_struct.GPIO_PinControl = OUTPUT_DSH; //高驱动力
    LPLD_GPIO_Init(gpio_init_struct);

    gpio_init_struct.GPIO_PTx = PTC;
    gpio_init_struct.GPIO_Pins = GPIO_Pin13; //RST
    gpio_init_struct.GPIO_Dir = DIR_OUTPUT;   //输出
    gpio_init_struct.GPIO_Output = OUTPUT_L;  //输出低电平
    LPLD_GPIO_Init(gpio_init_struct);

    //初始化总线
    LCD_ST7735R_RST_OUT = 0;
    ST7735R_DELAY();
    LCD_ST7735R_RST_OUT = 1;
    ST7735R_DELAY_MS(500); //上电给足够时间

    LCD_ST7735R_WR_8CMD(0x11); //Sleep out   退出睡眠模式
    ST7735R_DELAY_MS(120);     //Delay 120ms
    //------------------------------------ST7735R Frame Rate-----------------------------------------//
    /* Set the frame frequency of the full colors normal mode. */
    LCD_ST7735R_WR_8CMD(0xB1);  //In Normal Mode (Full Colors)    全屏模式
    LCD_ST7735R_WR_8DATA(0x05); //设置 RTNA Set 1-line  Period  一行周期
    LCD_ST7735R_WR_8DATA(0x3A); //设置 FPA: Front Porch
    LCD_ST7735R_WR_8DATA(0x3A); //设置 BPA: Back Porch
    //Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
    //其中 fosc = 850kHz

    /* Set the frame frequency of the Idle mode.  */
    LCD_ST7735R_WR_8CMD(0xB2); //In Idle Mode (8-colors)
    LCD_ST7735R_WR_8DATA(0x05);
    LCD_ST7735R_WR_8DATA(0x3A);
    LCD_ST7735R_WR_8DATA(0x3A);

    /* Set the frame frequency of the Partial mode/ full colors. */
    LCD_ST7735R_WR_8CMD(0xB3);
    LCD_ST7735R_WR_8DATA(0x05);
    LCD_ST7735R_WR_8DATA(0x3A);
    LCD_ST7735R_WR_8DATA(0x3A);
    LCD_ST7735R_WR_8DATA(0x05);
    LCD_ST7735R_WR_8DATA(0x3A);
    LCD_ST7735R_WR_8DATA(0x3A);

    //------------------------------------End ST7735R Frame Rate-----------------------------------------//
    LCD_ST7735R_WR_8CMD(0xB4); //Display Inversion Control  显示反转控制

    LCD_ST7735R_WR_8DATA(0x07); //LCD_ST7735R_WR_8DATA(0x03); 原来为3，改为7
    // 低三位从高到低，分别为  full colors normal mode 、Idle mode 、
    // full Colors partial mode  的 点反转 或 列反转 ，1为列反转

    LCD_ST7735R_WR_8CMD(0xC0); //Power Control Setting  电源控制设置
    LCD_ST7735R_WR_8DATA(0x28);
    LCD_ST7735R_WR_8DATA(0x08);
    LCD_ST7735R_WR_8DATA(0x84);
    LCD_ST7735R_WR_8CMD(0xC1);
    LCD_ST7735R_WR_8DATA(0XC0);
    LCD_ST7735R_WR_8CMD(0xC2);
    LCD_ST7735R_WR_8DATA(0x0C);
    LCD_ST7735R_WR_8DATA(0x00);
    LCD_ST7735R_WR_8CMD(0xC3);
    LCD_ST7735R_WR_8DATA(0x8C);
    LCD_ST7735R_WR_8DATA(0x2A);
    LCD_ST7735R_WR_8CMD(0xC4);
    LCD_ST7735R_WR_8DATA(0x8A);
    LCD_ST7735R_WR_8DATA(0xEE);
    //---------------------------------End ST7735R Power Sequence-------------------------------------//
    LCD_ST7735R_WR_8CMD(0xC5);  //  VCOM 电压配置
    LCD_ST7735R_WR_8DATA(0x0C); //  -0.725
    //------------------------------------ST7735R Gamma Sequence-----------------------------------------//
    LCD_ST7735R_WR_8CMD(0xE0);
    LCD_ST7735R_WR_8DATA(0x05);
    LCD_ST7735R_WR_8DATA(0x1A);
    LCD_ST7735R_WR_8DATA(0x0C);
    LCD_ST7735R_WR_8DATA(0x0E);
    LCD_ST7735R_WR_8DATA(0x3A);
    LCD_ST7735R_WR_8DATA(0x34);
    LCD_ST7735R_WR_8DATA(0x2D);
    LCD_ST7735R_WR_8DATA(0x2F);
    LCD_ST7735R_WR_8DATA(0x2D);
    LCD_ST7735R_WR_8DATA(0x2A);
    LCD_ST7735R_WR_8DATA(0x2F);
    LCD_ST7735R_WR_8DATA(0x3C);
    LCD_ST7735R_WR_8DATA(0x00);
    LCD_ST7735R_WR_8DATA(0x01);
    LCD_ST7735R_WR_8DATA(0x02);
    LCD_ST7735R_WR_8DATA(0x10);
    LCD_ST7735R_WR_8CMD(0xE1);
    LCD_ST7735R_WR_8DATA(0x04);
    LCD_ST7735R_WR_8DATA(0x1B);
    LCD_ST7735R_WR_8DATA(0x0D);
    LCD_ST7735R_WR_8DATA(0x0E);
    LCD_ST7735R_WR_8DATA(0x2D);
    LCD_ST7735R_WR_8DATA(0x29);
    LCD_ST7735R_WR_8DATA(0x24);
    LCD_ST7735R_WR_8DATA(0x29);
    LCD_ST7735R_WR_8DATA(0x28);
    LCD_ST7735R_WR_8DATA(0x26);
    LCD_ST7735R_WR_8DATA(0x31);
    LCD_ST7735R_WR_8DATA(0x3B);
    LCD_ST7735R_WR_8DATA(0x00);
    LCD_ST7735R_WR_8DATA(0x00);
    LCD_ST7735R_WR_8DATA(0x03);
    LCD_ST7735R_WR_8DATA(0x12);
    //------------------------------------End ST7735R Gamma Sequence-----------------------------------------//

    LCD_ST7735R_WR_8CMD(0x3A); //65k mode
    LCD_ST7735R_WR_8DATA(0x05);
    LCD_ST7735R_WR_8CMD(0x29); //开显示 Display on
    LCD_ST7735R_WR_8CMD(0x2c); //

    LCD_ST7735R_dir(0);//指针扫描方向
}


void LCD_ST7735R_dir(uint8 option) //默认方向为0
{
    ASSERT(option < 4); //0肯定小于4啊 不过这有什么用？

    st7735r_dir = option;
    switch (option)
    {
    case 0:
        LCD_ST7735R_WR_8CMD(0x36);  // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        LCD_ST7735R_WR_8DATA(0xc8); //0xc8  0xA8 0x08 0x68

        LCD_ST7735R_WR_8CMD(0x2a);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(128);

        LCD_ST7735R_WR_8CMD(0x2B);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(50);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(128 + 50);

        st7735r_h = ST7735R_H;
        st7735r_w = ST7735R_W;
        break;
    case 1:
        LCD_ST7735R_WR_8CMD(0x36);  // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        LCD_ST7735R_WR_8DATA(0xA8); //0xc8  0xA8 0x08 0x68

        LCD_ST7735R_WR_8CMD(0x2a);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x03);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x82);

        LCD_ST7735R_WR_8CMD(0x2B);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x02);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x81);

        st7735r_h = ST7735R_W;
        st7735r_w = ST7735R_H;
        break;
    case 2:
        LCD_ST7735R_WR_8CMD(0x36);  // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        LCD_ST7735R_WR_8DATA(0x08); //0xc8  0xA8 0x08 0x68

        LCD_ST7735R_WR_8CMD(0x2a);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x02);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x81);

        LCD_ST7735R_WR_8CMD(0x2B);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x03);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x82);

        st7735r_h = ST7735R_H;
        st7735r_w = ST7735R_W;
        break;
    case 3:
        LCD_ST7735R_WR_8CMD(0x36);  // 内存数据访问控制  MX 列地址顺序, MY 行地址顺序 ，MV 行列交换 ，ML 垂直刷新顺序 ,RGB  RGB-BGA顺序
        LCD_ST7735R_WR_8DATA(0x68); //0xc8  0xA8 0x08 0x68

        LCD_ST7735R_WR_8CMD(0x2a);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x03);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x82);

        LCD_ST7735R_WR_8CMD(0x2B);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(0x00);
        LCD_ST7735R_WR_8DATA(128);

        st7735r_h = ST7735R_W;
        st7735r_w = ST7735R_H;
        break;
    default:
        break;
    }
}

void LCD_rectangle(Site_t site, Size_t size, uint16 rgb565)
{
    uint32 n, temp;

    LCD_ST7735R_ptlon(site, size); //开窗

    temp = (uint32)size.W * size.H;
    LCD_RAMWR(); //写内存
    for (n = 0; n < temp; n++)
    {
        LCD_WR_DATA(rgb565); //写数据
    }
}

/*!
 *  @brief      设置 ST7735R 开窗
 *  @param      site        左上角坐标位置
 *  @param      size        开窗大小
 *  @since      v5.0
 */
void LCD_ST7735R_ptlon(Site_t site, Size_t size)
{

    if (st7735r_dir & 0x01)
    {
        site.x += 32; //液晶需要偏移一下，避免四周看不到的行
        //site.y += 2;
    }
    else
    {
        //site.x += 2;     //液晶需要偏移一下，避免四周看不到的行
        site.y += 32;
    }

    LCD_ST7735R_WR_8CMD(0x2a);                  //Partial Mode On  局部模式
    LCD_ST7735R_WR_8DATA((uint8)(site.x >> 8)); //高8位 Sx
    LCD_ST7735R_WR_8DATA((uint8)site.x);        //低8位 Sx
    LCD_ST7735R_WR_8DATA((uint8)((site.x + size.W - 1) >> 8));
    LCD_ST7735R_WR_8DATA((uint8)(site.x + size.W - 1));

    LCD_ST7735R_WR_8CMD(0x2B); //Row Address Set  行地址设置
    LCD_ST7735R_WR_8DATA((uint8)(site.y >> 8));
    LCD_ST7735R_WR_8DATA((uint8)site.y);
    LCD_ST7735R_WR_8DATA((uint8)((site.y + size.H - 1) >> 8));
    LCD_ST7735R_WR_8DATA((uint8)(site.y + size.H - 1));
}

/*!
 *  @brief      获取 ST7735R 高度
 *  @return     ILI9341 高度
 *  @since      v5.0
 */
uint16 ST7735R_get_h()
{
    return st7735r_h;
}

/*!
 *  @brief      获取 ST7735R 宽度
 *  @return     ILI9341 宽度
 *  @since      v5.0
 */
uint16 ST7735R_get_w()
{
    return st7735r_w;
}

/*!
 *  @brief      获取 ST7735R 显示方向
 *  @return     ST7735R 方向
 *  @since      v5.0
 */
uint8 ST7735R_get_dir()
{
    return st7735r_dir;
}

void ST7735R_DELAY(void)
{
    uint16 i, n;
    for (i = 0; i < 10; i++)
    {
        for (n = 0; n < 100; n++)
        {
            asm("nop");
        }
    }
}

void ST7735R_DELAY_MS(uint16 n)
{
    uint16 i,j,k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 1000; j++)
        {
            for (k = 0; k < 150; k++)
            {
                asm("nop");
            }
        } //1ms
    }
}

/*!
 *  @brief      显示字符串
 *  @param      site    左上角坐标
 *  @param      Str     字符串地址
 *  @param      Color   字体颜色
 *  @param      bkColor 背景颜色
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_str(site,"www.vcan123.com", BLUE,RED);
 */
void LCD_str(Site_t site, uint8 *Str, uint16 Color, uint16 bkColor)
{
#define MAX_CHAR_POSX (LCD_W - 8)
#define MAX_CHAR_POSY (LCD_H - 16)
    while (*Str != '\0')
    {
        if (site.x > MAX_CHAR_POSX)
        {
            //换行
            site.x = 0;
            site.y += 16;
        }
        if (site.y > MAX_CHAR_POSY)
        {
            //一屏
            site.y = 0;
            site.x = 0;
        }

        if (*Str == '\n')
        {
            //换行
            site.x = 0;
            site.y += 16;
            Str++;
        }
        else if (*Str == '\r')
        {
            site.x = 0;
            Str++;
        }
        else if (*Str == '\t')
        {
            LCD_char(site, ' ', Color, bkColor);
            site.x += 8;
            Str++;
        }
        else
        {
            LCD_char(site, *Str, Color, bkColor);
            site.x += 8;
            Str++;
        }
    }
#undef MAX_CHAR_POSX
#undef MAX_CHAR_POSY
}

/*!
 *  @brief      显示数字
 *  @param      site    左上角坐标
 *  @param      num     数字
 *  @param      Color   字体颜色
 *  @param      bkColor 背景颜色
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_num(site,123, BLUE,RED);
 */
void LCD_num(Site_t site, uint32 num, uint16 Color, uint16 bkColor)
{
    uint32 res = num;
    uint8 t = 0;
    Site_t sitetemp;
    sitetemp.y = site.y;

    if (num == 0)
    {
        LCD_char(site, '0', Color, bkColor);
        return;
    }
    while (res) /*得到数字长度t*/
    {
        res /= 10;
        t++;
    }

    while (num)
    {
        sitetemp.x = site.x + (8 * (t--) - 8);
        LCD_char(sitetemp, (num % 10) + '0', Color, bkColor);
        num /= 10;
    }
}

/*!
 *  @brief      显示数字（清空多余的位）
 *  @param      site            左上角坐标
 *  @param      num             数字
 *  @param      max_num_bit     最大的位数
 *  @param      Color           字体颜色
 *  @param      bkColor         背景颜色
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_num_BC(site,123,5, BLUE,RED);
 */
void LCD_num_BC(Site_t site, uint32 num, uint8 max_num_bit, uint16 Color, uint16 bkColor)
{
    uint32 res = num;
    uint8 t = 0;
    Site_t sitetemp;
    Size_t size;

    sitetemp.y = site.y;

    if (num == 0)
    {
        LCD_char(site, '0', Color, bkColor);

        site.x += 8;
        size.H = 16;
        size.W = 8 * (max_num_bit - 1);
        LCD_rectangle(site, size, bkColor);

        return;
    }
    while (res) /*得到数字长度t*/
    {
        res /= 10;
        t++;
    }
    if (t >= max_num_bit) //限制最大长度
    {
        t = max_num_bit;
    }

    res = t;

    while (t != 0)
    {
        sitetemp.x = site.x + (8 * (t--) - 8);
        LCD_char(sitetemp, (num % 10) + '0', Color, bkColor);
        num /= 10;
    }

    if (res != max_num_bit)
    {
        size.W = 8 * (max_num_bit - res);
        site.x += (8 * res);
        size.H = 16;
        LCD_rectangle(site, size, bkColor);
    }
}

/*!
 *  @brief      灰度图像显示
 *  @param      site            左上角坐标
 *  @param      size            显示图像大小
 *  @param      img             图像地址
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};      //x = 10 ,y = 20
                        Size_t size = {320,240};    //W = 320,H = 240
                        LCD_Img_gray(site, size, img);
 */
void LCD_Img_gray(Site_t site, Size_t size, uint8 *img)
{
    uint32 total = (size.H * size.W);
    uint16 imgtemp;
    uint8 *pimg = (uint8 *)img;

    LCD_PTLON(site, size); //开窗
    LCD_RAMWR();           //写内存

    while (total--)
    {
        imgtemp = (uint16) * (pimg++);
        imgtemp = GRAY_2_RGB565(imgtemp);
        LCD_WR_DATA(imgtemp); //写图像数据
    }
}

/*!
 *  @brief      缩放灰度图像显示
 *  @param      site            左上角坐标
 *  @param      size            显示图像大小
 *  @param      img             图像地址
 *  @param      imgsize         图像大小
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};          //x = 10 ,y = 20
                        Size_t size = {80,60};          //W = 80,H = 60
                        Size_t imgsize = {320,240};     //W = 320,H = 240
                        LCD_Img_gray_Z(site, size, img,imgsize);
 */
void LCD_Img_gray_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize)
{

    uint32 temp, tempY;
    uint16 x, y;
    uint16 X, Y;
    uint8 *pimg = (uint8 *)img;
    uint16 rgb;

    LCD_PTLON(site, size); //开窗

    LCD_RAMWR(); //写内存

    for (y = 0; y < size.H; y++)
    {
        Y = ((y * imgsize.H) / size.H);
        tempY = Y * imgsize.W;

        for (x = 0; x < size.W; x++)
        {
            X = (x * imgsize.W) / size.W;
            temp = tempY + X;
            rgb = GRAY_2_RGB565(pimg[temp]); //
            LCD_WR_DATA(rgb);
        }
    }
}

void LCD_Img_Binary(Site_t site, Size_t size, uint8 *img)
{
    uint32 total = (size.H * size.W) / 8;
    uint8 imgtemp;
    uint8 bitindex;
    uint8 *pimg = (uint8 *)img;

    LCD_PTLON(site, size); //开窗

    LCD_RAMWR(); //写内存

    while (total--)
    {
        imgtemp = *(pimg++);
        bitindex = 8;
        while (bitindex--)
        {
            if (imgtemp & (0x01 << bitindex))
            {
                LCD_WR_DATA(BINARY_COLOR); //写图像数据
            }
            else
            {
                LCD_WR_DATA(BINARY_BGCOLOR); //写图像数据
            }
        }
    }
}

void LCD_Img_Binary_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize)
{

    uint32 temp, tempY;
    uint16 x, y;
    uint16 X, Y;
    uint8 *pimg = (uint8 *)img;

    LCD_PTLON(site, size); //开窗

    LCD_RAMWR(); //写内存

    for (y = 0; y < size.H; y++)
    {
        Y = ((y * imgsize.H) / size.H);
        tempY = Y * imgsize.W;

        for (x = 0; x < size.W; x++)
        {
            X = ((x * imgsize.W) / size.W);
            temp = tempY + X;
            if ((pimg[temp >> 3] & (1 << (7 - (temp & 0x07)))) == 0)
            {
                LCD_WR_DATA(BINARY_BGCOLOR); //写图像数据
            }
            else
            {
                LCD_WR_DATA(BINARY_COLOR); //写图像数据
            }
        }
    }
}

void LCD_wave(Site_t site, Size_t size, uint8 *img, uint8 maxval, uint16 Color, uint16 bkColor)
{

    uint8 h;
    uint16 y = site.y + size.H - 1;

    LCD_rectangle(site, size, bkColor);
    site.x += size.W;
    img += (size.W - 1);
    while (size.W--)
    {
        if (*img >= maxval)
        {
            h = size.H - 1;
        }
        else
        {
            h = ((*img) * size.H) / maxval;
        }
        site.y = y - h;
        site.x--;
        img--;
        LCD_point(site, Color);
    }
}

void LCD_wave_display(Site_t site, Size_t size, uint8 *img, uint8 maxval, uint16 Color)
{

    uint8 h;
    uint16 y = site.y + size.H - 1;

    site.x += size.W;
    img += (size.W - 1);
    while (size.W--)
    {
        if (*img >= maxval)
        {
            h = size.H - 1;
        }
        else
        {
            h = ((*img) * size.H) / maxval;
        }
        site.y = y - h;
        site.x--;
        img--;
        LCD_point(site, Color);
    }
}