#ifndef FILTER_H
#define FILTER_H

#include "stdint.h"
#include "stdlib.h"
#include "math.h"

//uint16_t Filter_LowPass(uint16_t sample_new, float alpha);
//uint16_t Filter_Limiting(uint16_t data, uint16_t limit_threshold);

typedef struct
{
	float prev_value;
	float new_value;
	
}filter_info_t;

uint16_t Filter_LowPass(filter_info_t* filter_info, float sample_new, float alpha);
uint16_t Filter_Limiting(filter_info_t* filter_info, float data, float limit_threshold);

#endif
