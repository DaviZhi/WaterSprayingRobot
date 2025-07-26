#ifndef STPR_DRIVER_H
#define STPR_DRIVER_H

#include "gpio.h"
#include "tim.h"
#include "stpr_xdefine.h"

typedef enum
{
	STEP_FULL = 0x0,
	STEP_HALF = 0x1,
	STEP_QUARTER = 0x2,
	STEP_8MICRO = 0x3,
	STEP_16MICRO = 0x4,
	STEP_32MICRO = 0x5,
	
}stpr_microstep_e;

typedef struct
{
	uint8_t fault_flag;
	uint8_t home_flag;
	
}stpr_flag_t;

typedef struct
{
	GPIO_PinState enable_status;
	GPIO_PinState sleep_status;
	GPIO_PinState reset_status;
	
}stpr_status_t;

typedef struct
{
	GPIO_PinState direct_set;
	GPIO_PinState decay_set;
	uint8_t microstep_set;
	uint16_t stepfreq_set;
	stpr_status_t stpr_status;
	
}stpr_set_t;


void Stepper_DirectSet(stpr_set_t* stpr_set, GPIO_PinState dir_set);
void Stepper_SleepSet(stpr_set_t* stpr_set, GPIO_PinState slp_set);
void Stepper_EnableSet(stpr_set_t* stpr_set, GPIO_PinState ebl_set);
void Stepper_ResetSet(stpr_set_t* stpr_set, GPIO_PinState rst_set);
void Stepper_DecaySet(stpr_set_t* stpr_set, GPIO_PinState dcy_set);
void Stepper_MicrostepSet(stpr_set_t* stpr_set, stpr_microstep_e stpr_mcrstp);
void Stepper_StepFreqSet(stpr_set_t* stpr_set, uint16_t stpr_stpfrq);
void Stepper_FaultFlagGet(stpr_flag_t* stpr_flag);
void Stepper_HomeFlagGet(stpr_flag_t* stpr_flag);
void Stepper_Start(void);

#endif
