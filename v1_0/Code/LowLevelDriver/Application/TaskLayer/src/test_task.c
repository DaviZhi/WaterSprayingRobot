#include "test_task.h"
#include "bldc_driver.h"
#include "rmt_driver.h"

bldc_set_t BLDC_Set[4];
rmt_info_t Rmt_Info;

void Task1(void* argument)
{
//	BLDC_Init(BLDC_Set);
//	BLDC_SpeedSet(BLDC_Set, RF, 999);
//	BLDC_SpeedSet(BLDC_Set, LF, 999);
//	BLDC_SpeedSet(BLDC_Set, LB, 999);
//	BLDC_SpeedSet(BLDC_Set, RB, 999);
//	BLDC_Start(RF);
//	BLDC_Start(LF);
//	BLDC_Start(LB);
//	BLDC_Start(RB);
//	BLDC_Stop(RF);
//	BLDC_Stop(LF);
//	BLDC_Stop(LB);
//	BLDC_Stop(RB);
//	BLDC_xQueueCreate();

	for(;;)
	{
//		BLDC_SpeedSend();
//		BLDC_SpeedReceive(BLDC_Set);
		
		osDelay(1);
	}
}

void StartDefaultTask(void* argument)
{
	Remote_Init(&Rmt_Info);
	for(;;)
	{
		Remote_GetChannel(&Rmt_Info);
		Remote_ChannelOneToFour_Handler(&Rmt_Info);
		osDelay(1);
	}
}
