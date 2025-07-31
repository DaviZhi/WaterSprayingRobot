#include "test_task.h"
#include "bldc_driver.h"
#include "rmt_driver.h"

bldc_set_t BLDC_Set[4];
rmt_info_t Rmt_Info;

void Task1(void* argument)
{
	BLDC_Init(BLDC_Set);
	BLDC_SpeedSet(BLDC_Set, RF, 400);
	BLDC_SpeedSet(BLDC_Set, LF, 400);
	BLDC_Start(RF);
	BLDC_Start(LF);
	BLDC_xQueueCreate();

	for(;;)
	{
		BLDC_SpeedSend();
		BLDC_SpeedReceive(BLDC_Set);
		
		osDelay(1);
	}
}

void StartDefaultTask(void const * argument)
{
	
	for(;;)
	{
		Remote_ChannelGet(&Rmt_Info);
		osDelay(1);
	}
}
