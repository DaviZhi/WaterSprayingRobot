#include "test_task.h"
#include "bldc_driver.h"
#include "rmt_driver.h"

bldc_set_t BLDC_Set[4];
rmt_info_t Rmt_Info;

void Task1(void* argument)
{
	for(;;)
	{	
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void RemoteTask(void* argument)
{
	Remote_Init(&Rmt_Info);
	
	for(;;)
	{
		Remote_ChannelGet(&Rmt_Info);
		Remote_ChannelOneToFour_Handler(&Rmt_Info);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
