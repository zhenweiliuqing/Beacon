#ifndef _IMAGE_PROCESSING_H_
#define _IMAGE_PROCESSING_H_

#define WHITE 255
#define BLACK 0

typedef struct 
{
    int row_st[60];
    int row_end[60];
    int row_mid[60];
} Record;

void Image_Processing(uint8 *img ,int row ,int col);

#endif