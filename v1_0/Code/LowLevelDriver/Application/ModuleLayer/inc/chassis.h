#ifndef BIGZ_CHASSIS_H
#define BIGZ_CHASSIS_H

#include "rmt_driver.h"
#include "bldc_driver.h"
#include "bldc_xdefine.h"

#define CHASSIS_FACTOR	1

typedef enum
{
	CHASSIS_REVO_CCW,
	CHASSIS_REVO_CW,
	
}chassis_revo_set_e;

typedef struct
{
	bldc_set_t chassis_bldc_set[BLDC_NUM];
	uint16_t chassis_vx_set;
	uint16_t chassis_vy_set;
	uint16_t chassis_vz_set;

}chassis_set_t;

#endif
