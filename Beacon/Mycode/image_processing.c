#include "common.h"
#include "Image_processing.h"

#define WHITE 255
#define BLACK 0


int Image_Processing(uint8 *img ,int row ,int col,Light *light)
{
    int i,j;
    Record loc;//记录每一行白块开头 结尾的位置
    i = j = 0;
    
    for (i = 0;i < row;i++)
    {
        loc.row_st[i] = 0;//start
        loc.row_mid[i] = 0;//mid
        loc.row_end[i] = 0;//end
    }
    
    for (i = 0; i < CON_NUM; i++)
    {
        loc.nnect[i].num = 0;
        loc.nnect[i].start = 0;
        loc.nnect[i].end = 0;
    }

    for (i = 0;i < row;i++)
    {
        const uint8 *rowdata = &img[i * col];
        
        //if (rowdata[0] == WHITE)
        //{
          //  loc.row_st[i] = 0;
        //}

        for (j = 1;j < col; j++)
        {
            if (rowdata[j - 1] == BLACK && rowdata[j] == WHITE)//左黑右白 白块开始
            {
                loc.row_st[i] = j;
            }
            else if (rowdata[j - 1] == WHITE && rowdata[j] == BLACK)//左白右黑  白块结束
            {
                loc.row_end[i] = j;
            }
        }
        loc.row_mid[i] = (loc.row_st[i] + loc.row_end[i])/2;//这一行白块的中值
    }//get all 

    int count = 0;
    char FLAG_CONNECT_START = 0;
    char FLAG_CONNECT_END = 0;
    int connect_num = 0;
    int midx[60] = {0};//
    int midy[60] = {0};//
    
    for (i = 1;i < row;i++)//
    {
        if (loc.row_mid[i - 1] != 0 && loc.row_mid[i] != 0 && connect_num <= CON_NUM)//两行白块相连 且 连通域的数量小于设定值(主要是为了防止出现干扰) 保证取最大的白色的连通域
        {
            FLAG_CONNECT_START = 1;
            count++;//记录这个白色连通域的行数
            midx[i - 1] = i - 1;
            midy[i - 1] = loc.row_mid[i - 1];
        }
        else if (FLAG_CONNECT_START == 1)//白块已经不相连了
        {
            FLAG_CONNECT_END = 1;//结束标志
            loc.nnect[connect_num].num = count;
            loc.nnect[connect_num].start = i - count;
            loc.nnect[connect_num].end = i;
        }
        
        if (FLAG_CONNECT_START == 1 && FLAG_CONNECT_END == 1)//一个白色连通域结束 
        {
            connect_num++;//记录数量
            count = 0;
            FLAG_CONNECT_START = FLAG_CONNECT_END = 0;
        }
        
        if (connect_num > CON_NUM)
            break;
    }
    
    int max_x = 0;
    int min_x = 0;
    int max_count = 0;
    int x, y;
    x = y = 0;
    int max_y = 0;
    
    for (i = 0; i < CON_NUM; i++)
    {
         if (loc.nnect[i].num > max_count)//选择行数最多的白色连通域
         {
             max_count = loc.nnect[i].num;
             min_x = loc.nnect[i].start;//白块开始行
             max_x = loc.nnect[i].end;//白块结束行
         }
    }
    
    for (i = 1; i < row; i++)
    {   
        /*if (midx[i - 1] == 0 && midx[i] != 0)
        {
            min_x = i;
        }
        if (midx[i - 1] != 0 && midx[i] == 0)
        {
            max_x = i;
        }*/
        
        if (max_y < midy[i])
        {
            max_y = midy[i];//求得所有白块中值的最大值 
        }
    }
    
    x = (int)(min_x + max_x) / 2;//求行的中间值
    y = max_y;//列的中间值
    
    for (i = 0; i < row; i++)
    {
        //printf("%d\t%d\t%d\t%d\n",i,midy[i],loc.row_st[i],loc.row_end[i]);
    }
    
    //printf("%d\t%d\n\n\n", x, y);

    img[col * x + y] = BLACK;
    
    return y;
    //printf("%d",light->x);
    
}