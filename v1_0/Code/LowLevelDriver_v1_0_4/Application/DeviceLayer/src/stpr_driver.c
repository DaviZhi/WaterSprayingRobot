#include "stpr_driver.h"

void Stepper_DirectSet(stpr_set_t* stpr_set, GPIO_PinState dir_set)
{
	stpr_set->direct_set = dir_set;
	HAL_GPIO_WritePin(STEPPER_DIR_GPIO_Port, STEPPER_DIR_Pin, stpr_set->direct_set);
}

void Stepper_SleepSet(stpr_set_t* stpr_set, GPIO_PinState slp_set)
{
	stpr_set->stpr_status.sleep_status = slp_set;
	HAL_GPIO_WritePin(STEPPER_nSLP_GPIO_Port, STEPPER_nSLP_Pin, stpr_set->stpr_status.sleep_status);
}

void Stepper_EnableSet(stpr_set_t* stpr_set, GPIO_PinState ebl_set)
{
	stpr_set->stpr_status.enable_status = ebl_set;
	HAL_GPIO_WritePin(STEPPER_nENBL_GPIO_Port, STEPPER_nENBL_Pin, stpr_set->stpr_status.enable_status);
}

void Stepper_ResetSet(stpr_set_t* stpr_set, GPIO_PinState rst_set)
{
	stpr_set->stpr_status.reset_status = rst_set;
	HAL_GPIO_WritePin(STEPPER_nRST_GPIO_Port, STEPPER_nRST_Pin, stpr_set->stpr_status.reset_status);
}

void Stepper_DecaySet(stpr_set_t* stpr_set, GPIO_PinState dcy_set)
{
	stpr_set->decay_set = dcy_set;
	HAL_GPIO_WritePin(STEPPER_DECAY_GPIO_Port, STEPPER_DECAY_Pin, stpr_set->decay_set);
}

void Stepper_MicrostepSet(stpr_set_t* stpr_set, stpr_microstep_e stpr_mcrstp)
{
	uint8_t mode[3] = {0};
	
	stpr_set->microstep_set = stpr_mcrstp;
	mode[0] = ((stpr_set->microstep_set >> 0) & 0x01);
	mode[1] = ((stpr_set->microstep_set >> 1) & 0x01);
	mode[2] = ((stpr_set->microstep_set >> 2) & 0x01);
	
	HAL_GPIO_WritePin(STEPPER_MODE0_GPIO_Port, STEPPER_MODE0_Pin, (GPIO_PinState)mode[0]);
	HAL_GPIO_WritePin(STEPPER_MODE1_GPIO_Port, STEPPER_MODE1_Pin, (GPIO_PinState)mode[1]);
	HAL_GPIO_WritePin(STEPPER_MODE2_GPIO_Port, STEPPER_MODE2_Pin, (GPIO_PinState)mode[2]);
}

void Stepper_StepFreqSet(stpr_set_t* stpr_set, uint16_t stpr_stpfrq)
{
	stpr_set->stepfreq_set = stpr_stpfrq;
	__HAL_TIM_SET_AUTORELOAD(&htim12, (84000000 / (htim12.Init.Prescaler * stpr_set->stepfreq_set)) - 1);
	__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (84000000 / (htim12.Init.Prescaler * stpr_set->stepfreq_set)) / 2);
}

void Stepper_FaultFlagGet(stpr_flag_t* stpr_flag)
{
	stpr_flag->fault_flag = HAL_GPIO_ReadPin(STEPPER_nFLT_GPIO_Port, STEPPER_nFLT_Pin);
}

void Stepper_HomeFlagGet(stpr_flag_t* stpr_flag)
{
	stpr_flag->home_flag = HAL_GPIO_ReadPin(STEPPER_nHOME_GPIO_Port, STEPPER_nHOME_Pin);
}
