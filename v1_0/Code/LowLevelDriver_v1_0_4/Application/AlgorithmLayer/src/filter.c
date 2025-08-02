#include "filter.h"

uint16_t Filter_LowPass(uint16_t sample_new, float alpha)
{
	static float result_prev = 0;
	
	float result_new = alpha * (float)sample_new + (1 - alpha) * (float)result_prev;
	result_prev = result_new;
	
	return (uint16_t)result_new;
}
