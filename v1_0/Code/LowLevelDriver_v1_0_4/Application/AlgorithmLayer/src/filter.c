#include "filter.h"

uint16_t Filter_LowPass(uint16_t sample_new, float alpha)
{
	static float result_prev = 0;
	
	float result_new = alpha * (float)sample_new + (1 - alpha) * (float)result_prev;
	result_prev = result_new;
	
	return (uint16_t)result_new;
}

uint16_t Filter_Limiting(uint16_t data, uint16_t limit_threshold)
{
	static uint16_t result_prev = 0, result_new = 0;
	
	if((uint16_t)abs(data - result_prev) > limit_threshold)
	{
		result_new = result_prev;
	}
	else if((uint16_t)abs(data - result_prev) <= limit_threshold)
	{
		result_new = data;
	}
	result_prev = result_new;
	
	return result_new;
}
