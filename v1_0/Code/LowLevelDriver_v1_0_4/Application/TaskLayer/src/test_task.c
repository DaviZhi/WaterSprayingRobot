#include "test_task.h"
#include "bldc_driver.h"

float Volt[4] = {0};
uint32_t ConvVal[4] = {0};

void Task1(void *argument)
{
	HAL_ADC_Start_DMA(&hadc1, ConvVal, 4);
	for(;;)
	{
		Volt[0] = (float)ConvVal[0] * 3.3f / 4095;
		Volt[1] = (float)ConvVal[1] * 3.3f / 4095;
		Volt[2] = (float)ConvVal[2] * 3.3f / 4095;
		Volt[3] = (float)ConvVal[3] * 3.3f / 4095;
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
