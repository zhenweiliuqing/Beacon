#include "common.h"
#include "Image_processing.h"
#WHY

void Image_Processing(uint8 *img ,int row ,int col)
{
    int i,j;
    Record loc;

    for (i = 0;i < row;i++)
    {
        loc.row_st[i] = 0;
        loc.row_mid[i] = 0;
        loc.row_end[i] = 0;
    }

    for (i = 0;i < row;i++)
    {
        const uint8 *rowdata = &img[i * col];
        
        //if (rowdata[0] == WHITE)
        //{
          //  loc.row_st[i] = 0;
        //}

        for (j = 1;j < col;j++)
        {
            if (rowdata[j - 1] == BLACK && rowdata[j] == WHITE)
            {
                loc.row_st[i] = j;
            }
            else if (rowdata[j - 1] == WHITE && rowdata[j] == BLACK)
            {
                loc.row_end[j] = j;
            }
        }
        loc.row_mid[i] = (loc.row_st[i] + loc.row_end[i])/2;
    }//get all 

    int count = 0;
    int midx[60] = {0};//ÿһ���а�ɫ�ŵ���ֵ ������һ���а�ɫ���� ���¼��������һ�� ����Ϊ0 
    int midy[60] = {0};//ÿһ�а�ɫ�ŵ�����ֵ ����ɫ���ص���λy���� ���ȫ����Ϊ0
    int midx_sum = 0;
    int x, y;
    x = y = 0;
    
    for (i = 1;i < row;i++)//�ٴα���ͼ�� �õ�������������
    {
        if (loc.row_mid[i - 1] != 0 && loc.row_mid[i] != 0)
        {
            count++;
            midx[i - 1] = i - 1;
            midy[i - 1] = loc.row_mid[i - 1];
        }
        else 
        {
            midx[i - 1] = 0;
            midy[i - 1] = 0;
        }
    }
    
    int max_y = 0;
    for (i = 0; i < row; i++)
    {
        midx_sum += midx[i];
        if (max_y < midy[i])
        {
            max_y = midy[i];
        }
    }
    
    x = (int)midx_sum / count;
    y = max_y;
    
    for (i = 0; i < row; i++)
    {
        //printf("%d\t%d\n",i,midy[i]);
    }
    
    //printf("%d\t%d\n\n\n", x, y);

    img[col * x + y] = BLACK;
    
}