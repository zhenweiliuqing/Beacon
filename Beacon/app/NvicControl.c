#include "common.h"

void NVIC_Init();

void NVIC_Init(void)
{
	NVIC_InitTypeDef nvic_init_struct;
    //配置PORTA的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置DMA0的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = DMA0_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
}
