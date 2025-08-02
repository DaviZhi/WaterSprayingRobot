#ifndef FILTER_H
#define FILTER_H

#include "stdint.h"

uint16_t Filter_LowPass(uint16_t sample_new, float alpha);

#endif
