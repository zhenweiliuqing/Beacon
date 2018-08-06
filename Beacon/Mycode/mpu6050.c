#include "include.h"
#include "common.h"
volatile int16 MPU6050_ACCEL_XOUT_DATA=0;
volatile int16 MPU6050_ACCEL_YOUT_DATA=0;
volatile int16 MPU6050_ACCEL_ZOUT_DATA=0;
volatile int16 MPU6050_TEMP_OUT_DATA=0;
volatile int16 MPU6050_GYRO_XOUT_DATA=0;
volatile int16 MPU6050_GYRO_YOUT_DATA=0;
volatile int16 MPU6050_GYRO_ZOUT_DATA=0;
volatile int var[7];    //�����Ͳ��ε�����
volatile int16 ax=0,ay=0,az=0,angular_x=0,angular_y=0,angular_z=0,temp=0;  //����������
void MPU6050_Init(I2Cn_e i2cn)
{
  i2c_init(i2cn,400*1000);
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_PWR_MGMT_1, 0x00);
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_PWR_MGMT_2, 0x00);
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_CONFIG, 0x06);//��ͨ�˲�������5Hz
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_GYRO_CONFIG, 0x08);//���Լ�   ��500 ��/s
  i2c_write_reg(i2cn, MPU6050_ADDRESS,MPU6050_ACCEL_CONFIG, 0x08);//���Լ�  ��4g
} 

//----------------------------------------------------------------------
/*!
 *  @brief      ��ȡ����
 *  @param      I2Cn_e        I2Cģ��(I2C0��I2C1)
 *  @param      Addr         �ӻ��Ĵ�����ַ
 *  @param      Data        ����
 *  @since      v1.0
 *  Sample usage:       MPU6050_GetDoubleData(MPU6050_I2C_Moudle_1 , MPU6050_GYRO_YOUT)��
 */
int16 MPU6050_GetDoubleData(I2Cn_e i2cn ,uint8 Addr)
{
  uint16 data=0x0000;
  data=i2c_read_reg(i2cn,MPU6050_ADDRESS, Addr);
  data=(uint16)((data<<8)&0xff00);
  data+=i2c_read_reg(i2cn,MPU6050_ADDRESS, Addr+1);
  
  return (int16)data;//�ϳ����ݣ�Ϊ�з���������
  
}
void mpu6050_data()
{
  

  ax=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_ACCEL_XOUT);//��X����ٶ�
  var[0] = ax;
  printf("X����ٶ�Ϊ%d\n",ax);
  DELAY_MS(100);
                
  ay=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_ACCEL_ZOUT);//��Y����ٶ�
  var[1] = ay;
  printf("Y����ٶ�Ϊ%d\n",ay);
  DELAY_MS(100);
                
  az=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_ACCEL_ZOUT);//��Z����ٶ�
  var[2] = az;
  printf("Z����ٶ�Ϊ%d\n",az);
  DELAY_MS(100);
 angular_x=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_GYRO_XOUT);//��X����ٶ�
  var[3] = angular_x;
  printf("X����ٶ�Ϊ%d\n",angular_x);
  DELAY_MS(100);
                
 angular_y=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_GYRO_YOUT);//��Y����ٶ�
  var[4] = angular_y;
  printf("Y����ٶ�Ϊ%d\n",angular_y);
  DELAY_MS(100);
                
angular_z=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_GYRO_ZOUT);//��Z����ٶ�
  var[5] = angular_z;
  printf("Z����ٶ�Ϊ%d\n",angular_z);
  DELAY_MS(100);
                
 temp=MPU6050_GetDoubleData(MPU6050_I2C_Moudle_2,MPU6050_TEMP_OUT);//���¶�
 var[6] = temp;
  printf("�¶�Ϊ%d\n",temp);
  DELAY_MS(100);
}
void systemInit()
{  

  MPU6050_Init(MPU6050_I2C_Moudle_2);
  DELAY_MS(3000);
}