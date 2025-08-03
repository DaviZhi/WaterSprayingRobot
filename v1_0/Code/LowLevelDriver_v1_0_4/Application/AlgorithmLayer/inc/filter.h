#ifndef FILTER_H
#define FILTER_H

#include "stdint.h"
#include "stdlib.h"

uint16_t Filter_LowPass(uint16_t sample_new, float alpha);
uint16_t Filter_Limiting(uint16_t data, uint16_t limit_threshold);

#endif
