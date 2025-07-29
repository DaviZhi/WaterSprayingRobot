#include "test_task.h"
#include "bldc_driver.h"

bldc_set_t BLDC_Set[4];

void Task1(void *argument)
{
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
	bldc_set_t bldc_set;
	BLDC_SpeedSet(&bldc_set, RF, 500);
	
	for(;;)
	{
		osDelay(1);
	}
}
