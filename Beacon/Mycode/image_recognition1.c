#include "common.h"
#include "include.h"
#include "math.h"

extern uint8 imgbuff[CAMERA_SIZE]; 
uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
                    //������Ҫ��ά���飬ֻ��Ҫ�ĳ� uint8 img[CAMERA_H][CAMERA_W];
                    //imgbuff�ǲɼ��Ļ�������img�ǽ�ѹ��Ļ�������imgbuff���ڲɼ�ͼ��img����ͼ����.
uint8 img_buf[60][80]; 
uint32 Lookingforabeacon()
{
      int i=0,j=0,k=0;
      int mid_1=0,mid_2=0;
      camera_get_img();                                   //����ͷ��ȡͼ��
      img_extract((uint8 *)img_buf,(uint8 *)imgbuff, CAMERA_W*CAMERA_H/8);        //��ѹΪ�Ҷ�ͼ�񣬷��㷢�͵���λ����
      for(i=5;i<40;i++)
        { 
          for(j=0;j<79;j++)
            {
              if(img_buf[i][j]!=img_buf[i][j+1])
                {
                  // printf("�ҵ�����㣺%d\r\n",j);
                  k++;
                  mid_1+=j;
                  }             
            }
        }
      mid_2=mid_1/k;
      //printf("���ߵĺ�����Ϊ��%d\r\n",mid_2);
      return(mid_2);

}