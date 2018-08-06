#ifndef	_SCREEN_H_
#define _SCREEN_H_

#define RESET  PTA24_OUT
#define DC     PTA19_OUT
#define D1     PTB22_OUT
#define D0     PTB21_OUT

 typedef unsigned char byte;
 typedef unsigned int word;
 extern byte beyond96x64[512];
 void LCD_WrDat(uint8 data);
 
 void LCD_Set_Pos(byte x, byte y);
 void LCD_Set_Pos1(byte x, byte y);
   
 void LCD_Init(void);
 void LCD_CLS(void);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void Draw_BMP1(byte x0,byte y0,byte x1,byte y1,uint8 bmp[]);
   
 void LCD_Fill(byte dat);
 void Display(int16 i,uint8 x,uint8 y);
 void DisplayFloat(int16 i,uint8 x,uint8 y);
#endif