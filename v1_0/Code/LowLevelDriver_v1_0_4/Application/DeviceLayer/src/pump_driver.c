#include "pump_driver.h"
#include "pump_xdefine.h"

void Pump_Init(pump_set_t* pump_set)
{
	/*Allocate memory*/
	
	/*End of allocation*/
	
	pump_set->flowrate_set = PUMP_FLOWRATE_MAX;
	pump_set->pump_in1_set = PUMP_IN1_RESET;
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
	HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
}

void Pump_EMO(pump_set_t* pump_set)
{
	pump_set->flowrate_set = PUMP_FLOWRATE_MIN;
	pump_set->pump_in1_set = PUMP_IN1_SET;
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
	HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
}

void Pump_FlowRateSet(pump_set_t* pump_set, uint16_t flwrt_set)
{
	if(flwrt_set <= PUMP_FLOWRATE_MAX)
	{
		pump_set->flowrate_set = flwrt_set;
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
	}
	else
	{
		Pump_EMO(pump_set);
	}
}

void Pump_ModeSet(pump_set_t* pump_set, pump_modeset_e pump_mdset)
{
	switch(pump_mdset)
	{
		case PUMP_SLEEP:
		{
			pump_set->flowrate_set = PUMP_FLOWRATE_MAX;
			pump_set->pump_in1_set = PUMP_IN1_RESET;
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
			HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
			break;
		}
		case PUMP_BRAKE:
		{
			pump_set->flowrate_set = PUMP_FLOWRATE_MIN;
			pump_set->pump_in1_set = PUMP_IN1_SET;
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
			HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
			break;
		}
		case PUMP_ACTIVE:
		{
			pump_set->pump_in1_set = PUMP_IN1_SET;
			HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
			break;
		}
		default:
		{
			Pump_EMO(pump_set);
			break;
		}
	}
}
