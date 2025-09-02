#ifndef STPR_DRIVER_H
#define STPR_DRIVER_H

#include "gpio.h"
#include "tim.h"

#include "dev.h"

/* Private enum---------*/
typedef enum
{
	STEP_FULL = 0x0,
	STEP_HALF = 0x1,
	STEP_QUARTER = 0x2,
	STEP_8MICRO = 0x3,
	STEP_16MICRO = 0x4,
	STEP_32MICRO = 0x5,
	
}stpr_microstep_e;

/* Private struct--------------*/
typedef struct
{
	uint8_t fault_flag;
	uint8_t home_flag;
	
}stpr_flag_t;

typedef struct
{
	GPIO_PinState enable_status_set;
	GPIO_PinState sleep_status_set;
	GPIO_PinState reset_status_set;
	
}stpr_status_set_t;

typedef struct
{
	GPIO_PinState direct_set;
	GPIO_PinState decay_set;
	uint8_t microstep_set;
	uint32_t stepfreq_set;
	
	stpr_status_set_t stpr_status_set;
	stpr_flag_t stpr_flag;
	dev_status_e stpr_status;
	
}stpr_set_t;

/* Stepper_Exported function------------------------------------------------------*/
void Stepper_SetDirect(stpr_set_t* stpr_set, GPIO_PinState dir_set);
void Stepper_SetSleep(stpr_set_t* stpr_set, GPIO_PinState slp_set);
void Stepper_SetEnable(stpr_set_t* stpr_set, GPIO_PinState ebl_set);
void Stepper_SetReset(stpr_set_t* stpr_set, GPIO_PinState rst_set);
void Stepper_SetDecay(stpr_set_t* stpr_set, GPIO_PinState dcy_set);
void Stepper_SetMicrostep(stpr_set_t* stpr_set, stpr_microstep_e stpr_mcrstp);
void Stepper_SetStepFreq(stpr_set_t* stpr_set, uint32_t stpr_stpfrq);
void Stepper_GetFaultFlag(stpr_flag_t* stpr_flag);
void Stepper_GetHomeFlag(stpr_flag_t* stpr_flag);
void Stepper_Start(stpr_set_t* stpr_set);

#endif
