#include "pump_driver.h"
#include "pump_xdefine.h"

/**
 * @brief Initialize pump to proper work mode.
 * @param pump_set structure ptr
 */
void Pump_Init(pump_set_t* pump_set)
{
	pump_set->flowrate_set = PUMP_FLOWRATE_MAX;
	pump_set->pump_in1_set = PUMP_IN1_RESET;
	
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
	HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
}

/**
 * @brief Set flowrate of pump.
 * @param pump_set structure ptr
 * @param flowrate value, limited up to @refer PUMP_FLOWRATE_MAX
 */
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

/**
 * @brief Set mode of pump.
 * @param pump_set structure ptr
 * @param pump mode
 *		@arg PUMP_SLEEP
 *		@arg PUMP_BRAKE
 *		@arg PUMP_ACTIVE
 */
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

/**
 * @brief Start pump.
 */
void Pump_Start(void)
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
}

/**	
 * @brief Emergency off pump when encounter man-made error or other errors.
 * @param pump_set structure ptr
 * @note This function should not be used in other files.
 */
static void Pump_EMO(pump_set_t* pump_set)
{
	pump_set->flowrate_set = PUMP_FLOWRATE_MIN;
	pump_set->pump_in1_set = PUMP_IN1_SET;
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pump_set->flowrate_set);
	HAL_GPIO_WritePin(PUMP_IN1_GPIO_Port, PUMP_IN1_Pin, pump_set->pump_in1_set);
}
