#include "bldc_driver.h"
#include "bldc_xdefine.h"
#include "FreeRTOS.h"
#include "queue.h"

/**
 * @brief Initialize all BLDC to proper work mode.
 * @param bldc_set structure ptr
 */
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

/**	
 * @brief Set whether brake or loose for appointed BLDC.
 * @param bldc_set structure ptr
 * @param bldc number
 *		@arg LF
 *		@arg RF
 *		@arg LB
 *		@arg RB
 * @param bldc brake or loose
 * 		@arg BLDC_BRAKE
 * 		@arg BLDC_LOOSE
 */
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

/**	
 * @brief Set revolution(rotation) direction for appointed BLDC.
 * @param bldc_set structure ptr
 * @param bldc number
 *		@arg LF
 *		@arg RF
 *		@arg LB
 *		@arg RB
 * @param bldc revolution(rotation) direction
 * 		@arg BLDC_CW
 * 		@arg BLDC_CCW
 */
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

/**	
 * @brief Set speed for appointed BLDC.
 * @param bldc_set structure ptr
 * @param bldc number
 *		@arg LF
 *		@arg RF
 *		@arg LB
 *		@arg RB
 * @param bldc speed value, limited up to @refer BLDC_SPDMAX
 */
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

xQueueHandle xQueueConvData;

void BLDC_xQueueCreate(void)
{
	xQueueConvData = xQueueCreate(4, sizeof(uint16_t));
}

//uint16_t ConvRcv1,ConvRcv2,ConvRcv3,ConvRcv4;

void BLDC_SpeedSend(void)
{
	static uint16_t conv_data_send[4];
	
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)conv_data_send, sizeof(conv_data_send));
//	ConvRcv1 = conv_data_send[0];
//	ConvRcv2 = conv_data_send[1];
//	ConvRcv3 = conv_data_send[2];
//	ConvRcv4 = conv_data_send[3];
	
	xQueueSendToBack(xQueueConvData, conv_data_send, portMAX_DELAY);
}

void BLDC_SpeedReceive(bldc_set_t* bldc_set)
{
	static uint16_t conv_data_rcv[4];
	
	if(xQueueReceive(xQueueConvData, conv_data_rcv, portMAX_DELAY) == pdPASS)
	{
		bldc_set[LF].speed_get = conv_data_rcv[0];
		bldc_set[RF].speed_get = conv_data_rcv[1];
		bldc_set[RB].speed_get = conv_data_rcv[2];
		bldc_set[LB].speed_get = conv_data_rcv[3];
	}
}

/**	
 * @brief Start appointed BLDC.
 * @param bldc number
 *		@arg LF
 *		@arg RF
 *		@arg LB
 *		@arg RB
 */
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

/**	
 * @brief Stop appointed BLDC.
 * @param bldc number
 *		@arg LF
 *		@arg RF
 *		@arg LB
 *		@arg RB
 */
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

/**	
 * @brief Emergency off all BLDCs when encounter man-made error or other errors.
 * @param bldc_set structure ptr
 * @note This function should not be used in other files.
 */
static void BLDC_EMO(bldc_set_t* bldc_set)
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
