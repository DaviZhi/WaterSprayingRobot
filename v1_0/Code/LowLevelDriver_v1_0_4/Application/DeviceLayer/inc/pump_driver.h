#ifndef PUMP_DRIVER_H
#define PUMP_DRIVER_H

#include "gpio.h"
#include "tim.h"

#include "dev.h"

/* Private enum---------*/
typedef enum
{
	PUMP_SLEEP = 0,
	PUMP_ACTIVE = 1,
	PUMP_BRAKE = 2,
	
}pump_modeset_e;

/* Private struct----------*/
typedef struct
{
	uint16_t flowrate_set;
	GPIO_PinState pump_in1_set;
	dev_status_e pump_status;
	
}pump_set_t;

/* Pump_Imported function------------------------------------------------------*/
static void Pump_EMO(pump_set_t* pump_set);

/* Pump_Exported function------------------------------------------------------*/
void Pump_Init(pump_set_t* pump_set);
void Pump_SetFlowrate(pump_set_t* pump_set, uint16_t flwrt_set);
void Pump_SetMode(pump_set_t* pump_set, pump_modeset_e pump_mdset);
void Pump_Start(pump_set_t* pump_set);

#endif
