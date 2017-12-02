#ifndef _LPLD_SCCB_H_
#define _LPLD_SCCB_H_

#define SCCB_SCL PTA26_O
#define SCCB_SDA PTA25_O

#define SCL_H()         SCCB_SCL = 1
#define SCL_L()         SCCB_SCL = 0
//#define SCL_DDR_OUT()   DDRA26 = 1
//#define SCL_DDR_IN()    DDRA26 = 0

#define SDA_H()         SCCB_SDA = 1
#define SDA_L()         SCCB_SDA = 0
#define SDA_DDR_OUT()   DDRA25 = 1
#define SDA_DDR_IN()    DDRA25 = 0
#define SDA_IN()        PTA25_I

#define ADDR_OV7725 0x42
#define ADDR_OV7620 0x42

#define DEV_ADR ADDR_OV7725
#define SCCB_DELAY() SCCB_delay(400)

extern void SCCB_GPIO_Init(void);
extern int SCCB_WriteByte(uint16 WriteAddress,uint8 SendByte);
extern int SCCB_ReadByte(uint8 *pBuffer,uint16 length,uint8 ReadAddress);

#endif