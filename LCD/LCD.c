#include "common.h"
#include "ST7735.h"
void main()
{
    Site_t site = {0,0};
    Size_t size;

    LCD_init();
    LCD_str(site, "Cam init ing", FCOLOUR, BCOLOUR);

    size.H = LCD_H;
    size.W = LCD_W;
    while (1)
    {
        
    }
}