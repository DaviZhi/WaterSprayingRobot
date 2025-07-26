#include "bldc_driver.h"
#include "bldc_xdefine.h"

void BLDC_Init(bldc_set_t* bldc_set)
{
	bldc_set[LF].brake_set = BLDC_LOOSE;
	bldc_set[RF].brake_set = BLDC_LOOSE;
	bldc_set[LB].brake_set = BLDC_LOOSE;
	bldc_set[RB].brake_set = BLDC_LOOSE;
	
	HAL_GPIO_WritePin(BLDC3_BRA_GPIO_Port, BLDC3_BRA_Pin, bldc_set[LF].brake_set);
	HAL_GPIO_WritePin(BLDC1_BRA_GPIO_Port, BLDC1_BRA_Pin, bldc_set[RF].brake_set);
	HAL_GPIO_WritePin(BLDC2_BRA_GPIO_Port, BLDC2_BRA_Pin, bldc_set[LB].brake_set);
	HAL_GPIO_WritePin(BLDC4_BRA_GPIO_Port, BLDC4_BRA_Pin, bldc_set[RB].brake_set);
	
	bldc_set[LF].speed_set = BLDC_SPDMIN;
	bldc_set[RF].speed_set = BLDC_SPDMIN;
	bldc_set[LB].speed_set = BLDC_SPDMIN;
	bldc_set[RB].speed_set = BLDC_SPDMIN;
	
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, bldc_set[LF].speed_set);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, bldc_set[RF].speed_set);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, bldc_set[LB].speed_set);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, bldc_set[RB].speed_set);
}

void BLDC_BrakeSet(bldc_set_t* bldc_set, bldc_num_e bldc_num, GPIO_PinState bra_set)
{
	switch(bldc_num)
	{
		case LF:
		{
			bldc_set[LF].brake_set = bra_set;
			HAL_GPIO_WritePin(BLDC3_BRA_GPIO_Port, BLDC3_BRA_Pin, bldc_set[LF].brake_set);
			break;
		}
		case RF:
		{
			bldc_set[RF].brake_set = bra_set;
			HAL_GPIO_WritePin(BLDC1_BRA_GPIO_Port, BLDC1_BRA_Pin, bldc_set[RF].brake_set);
			break;
		}
		case LB:
		{
			bldc_set[LB].brake_set = bra_set;
			HAL_GPIO_WritePin(BLDC2_BRA_GPIO_Port, BLDC2_BRA_Pin, bldc_set[LB].brake_set);
			break;
		}
		case RB:
		{
			bldc_set[RB].brake_set = bra_set;
			HAL_GPIO_WritePin(BLDC4_BRA_GPIO_Port, BLDC4_BRA_Pin, bldc_set[RB].brake_set);
			break;
		}
		default:
		{
			BLDC_EMO(bldc_set);
			break;
		}
	}
}

void BLDC_RevoSet(bldc_set_t* bldc_set, bldc_num_e bldc_num, GPIO_PinState rev_set)
{
	switch(bldc_num)
	{
		case LF:
		{
			bldc_set[LF].revo_set = rev_set;
			HAL_GPIO_WritePin(BLDC3_BRA_GPIO_Port, BLDC3_BRA_Pin, bldc_set[LF].revo_set);
			break;
		}
		case RF:
		{
			bldc_set[RF].revo_set = rev_set;
			HAL_GPIO_WritePin(BLDC1_BRA_GPIO_Port, BLDC1_BRA_Pin, bldc_set[RF].revo_set);
			break;
		}
		case LB:
		{
			bldc_set[LB].revo_set = rev_set;
			HAL_GPIO_WritePin(BLDC2_BRA_GPIO_Port, BLDC2_BRA_Pin, bldc_set[LB].revo_set);
			break;
		}
		case RB:
		{
			bldc_set[RB].revo_set = rev_set;
			HAL_GPIO_WritePin(BLDC4_BRA_GPIO_Port, BLDC4_BRA_Pin, bldc_set[RB].revo_set);
			break;
		}
		default:
		{
			BLDC_EMO(bldc_set);
			break;
		}
	}
}

uint32_t Val = 0;

void BLDC_SpeedGet(void)
{
	
}

void BLDC_SpeedSet(bldc_set_t* bldc_set, bldc_num_e bldc_num, uint16_t spd_set)
{
	if(spd_set <= BLDC_SPDMAX)
	{
		switch(bldc_num)
		{
			case LF:
			{
				bldc_set[LF].speed_set = spd_set;
				__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, bldc_set[LF].speed_set);
				break;
			}
			case RF:
			{
				bldc_set[RF].speed_set = spd_set;
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, bldc_set[RF].speed_set);
				break;
			}
			case LB:
			{
				bldc_set[LB].speed_set = spd_set;
				__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, bldc_set[LB].speed_set);
				break;
			}
			case RB:
			{
				bldc_set[RB].speed_set = spd_set;
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, bldc_set[RB].speed_set);
				break;
			}
			default:
			{
				BLDC_EMO(bldc_set);
				break;
			}
		}
	}
	else
	{
		BLDC_EMO(bldc_set);
	}
}

void BLDC_Start(bldc_num_e bldc_num)
{
	switch(bldc_num)
	{
		case LF:
		{
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
			break;
		}
		case RF:
		{
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			break;
		}
		case LB:
		{
			HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
			break;
		}
		case RB:
		{
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
			break;
		}
		default:
		{
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
			break;
		} 
	}
}

void BLDC_Stop(bldc_num_e bldc_num)
{
	switch(bldc_num)
	{
		case LF:
		{
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
			break;
		}
		case RF:
		{
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			break;
		}
		case LB:
		{
			HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
			break;
		}
		case RB:
		{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
			break;
		}
		default:
		{
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
			break;
		} 
	}
}

void BLDC_EMO(bldc_set_t* bldc_set)
{
	bldc_set[LF].brake_set = GPIO_PIN_RESET;
	bldc_set[RF].brake_set = GPIO_PIN_RESET;
	bldc_set[LB].brake_set = GPIO_PIN_RESET;
	bldc_set[RB].brake_set = GPIO_PIN_RESET;
	
	HAL_GPIO_WritePin(BLDC1_BRA_GPIO_Port, BLDC1_BRA_Pin, bldc_set[LF].brake_set);
	HAL_GPIO_WritePin(BLDC2_BRA_GPIO_Port, BLDC2_BRA_Pin, bldc_set[RF].brake_set);
	HAL_GPIO_WritePin(BLDC3_BRA_GPIO_Port, BLDC3_BRA_Pin, bldc_set[LB].brake_set);
	HAL_GPIO_WritePin(BLDC4_BRA_GPIO_Port, BLDC4_BRA_Pin, bldc_set[RB].brake_set);
}
