#include "common.h"
#include "image_processing.h"

typedef struct {
    uint8_t x;
    uint8_t y;
}Location;

void image_process(uint8_t **imaddr);
Location location[3];
void image_process(uint8_t**image,Location *loc)
{
    uint16_t i,j;
    uint16_t num;//黑点数目
    uint32_t xsum,ysum;//xy坐标值
    uint8_t xaver,yaver;
    num = xsum = ysum = 0;
    for (i = 0; i < CAMERA_H; i++)
    {
        for (j = 0; j < CAMERA_W; j++)
        {
            if(image[i][j] == BLACK)
            {
                num++;
                xsum += j;
                ysum += i;
            }
        }
    }
    xaver = xsum/num;
    yaver = ysum/num;
    loc->x = xaver;
    loc->y = yaver;
}