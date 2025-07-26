#ifndef PUMP_DRIVER_H
#define PUMP_DRIVER_H

#include "gpio.h"
#include "tim.h"

typedef enum
{
	PUMP_SLEEP = 0,
	PUMP_ACTIVE = 1,
	PUMP_BRAKE = 2,
	
}pump_modeset_e;

typedef struct
{
	uint16_t flowrate_set;
	GPIO_PinState pump_in1_set;
	
}pump_set_t;

void Pump_EMO(pump_set_t* pump_set);

void Pump_Init(pump_set_t* pump_set);
void Pump_FlowRateSet(pump_set_t* pump_set, uint16_t flwrt_set);
void Pump_ModeSet(pump_set_t* pump_set, pump_modeset_e pump_mdset);
void Pump_Start(void);

#endif
