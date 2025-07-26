#include "test_task.h"
#include "bldc_driver.h"

void StopTask(void *argument)
{
	bldc_set_t bldc_set;
	for(;;)
	{
		BLDC_SpeedSet(&bldc_set, RF, 200);
		osDelay(100);
	}
}

void StartDefaultTask(void const * argument)
{
	bldc_set_t bldc_set;
//	BLDC_SpeedSet(&bldc_set, RF, 400);
	for(;;)
	{
		BLDC_SpeedSet(&bldc_set, RF, 800);
		BLDC_Start(RF);
		osDelay(10);
	}
}
