#include "stpr_driver.h"
#include "stpr_xdefine.h"

/**	
 * @brief Set rotation direction of stepper.
 * @param stpr_set structure ptr
 * @param stepper rotation direction set
 * 		@arg STEPPER_CCW
 * 		@arg STEPPER_CW
 */
void Stepper_DirectSet(stpr_set_t* stpr_set, GPIO_PinState dir_set)
{
	stpr_set->direct_set = dir_set;
	HAL_GPIO_WritePin(STEPPER_DIR_GPIO_Port, STEPPER_DIR_Pin, stpr_set->direct_set);
}

/**	
 * @brief Set work mode of stepper.
 * @param stpr_set structure ptr
 * @param stepper work mode set
 * 		@arg STEPPER_SLEEP
 * 		@arg STEPPER_ACTIVE
 */
void Stepper_SleepSet(stpr_set_t* stpr_set, GPIO_PinState slp_set)
{
	stpr_set->stpr_status.sleep_status = slp_set;
	HAL_GPIO_WritePin(STEPPER_nSLP_GPIO_Port, STEPPER_nSLP_Pin, stpr_set->stpr_status.sleep_status);
}

/**	
 * @brief Set enable or disable of stepper.
 * @param stpr_set structure ptr
 * @param stepper enable or disable status set
 * 		@arg STEPPER_ENABLE
 * 		@arg STEPPER_DISABLE
 */
void Stepper_EnableSet(stpr_set_t* stpr_set, GPIO_PinState ebl_set)
{
	stpr_set->stpr_status.enable_status = ebl_set;
	HAL_GPIO_WritePin(STEPPER_nENBL_GPIO_Port, STEPPER_nENBL_Pin, stpr_set->stpr_status.enable_status);
}

/**	
 * @brief Set reset or set of stepper.
 * @param stpr_set structure ptr
 * @param stepper set or reset status set
 * 		@arg STEPPER_SET
 * 		@arg STEPPER_RESET
 */
void Stepper_ResetSet(stpr_set_t* stpr_set, GPIO_PinState rst_set)
{
	stpr_set->stpr_status.reset_status = rst_set;
	HAL_GPIO_WritePin(STEPPER_nRST_GPIO_Port, STEPPER_nRST_Pin, stpr_set->stpr_status.reset_status);
}

/**	
 * @brief Set decay mode of stepper.
 * @param stpr_set structure ptr
 * @param stepper decay mode set
 * 		@arg STEPPER_SLOWDECAY
 * 		@arg STEPPER_FASTDECAY
 */
void Stepper_DecaySet(stpr_set_t* stpr_set, GPIO_PinState dcy_set)
{
	stpr_set->decay_set = dcy_set;
	HAL_GPIO_WritePin(STEPPER_DECAY_GPIO_Port, STEPPER_DECAY_Pin, stpr_set->decay_set);
}

/**	
 * @brief Set microstep of stepper.
 * @param stpr_set structure ptr
 * @param stepper microstep set
 * 		@arg STEP_FULL
 * 		@arg STEP_HALF
 * 		@arg STEP_QUARTER
 * 		@arg STEP_8MICRO
 * 		@arg STEP_16MICRO
 * 		@arg STEP_32MICRO
 */
void Stepper_MicrostepSet(stpr_set_t* stpr_set, stpr_microstep_e stpr_mcrstp)
{
	static uint8_t mode[3] = {0};
	
	stpr_set->microstep_set = stpr_mcrstp;
	mode[0] = ((stpr_set->microstep_set >> 0) & 0x01);
	mode[1] = ((stpr_set->microstep_set >> 1) & 0x01);
	mode[2] = ((stpr_set->microstep_set >> 2) & 0x01);
	
	HAL_GPIO_WritePin(STEPPER_MODE0_GPIO_Port, STEPPER_MODE0_Pin, (GPIO_PinState)mode[0]);
	HAL_GPIO_WritePin(STEPPER_MODE1_GPIO_Port, STEPPER_MODE1_Pin, (GPIO_PinState)mode[1]);
	HAL_GPIO_WritePin(STEPPER_MODE2_GPIO_Port, STEPPER_MODE2_Pin, (GPIO_PinState)mode[2]);
}

/**	
 * @brief Set step frequency of stepper.
 * @param stpr_set structure ptr
 * @param stepper step frequency set, limited up to 250kHz according to max value of DRV8825
 */
void Stepper_StepFreqSet(stpr_set_t* stpr_set, uint32_t stpr_stpfrq)
{
	static uint32_t tim12_clock;
	
	stpr_set->stepfreq_set = stpr_stpfrq;
	tim12_clock = HAL_RCC_GetPCLK1Freq() * 2;
	
	__HAL_TIM_SET_AUTORELOAD(&htim12, (tim12_clock / (htim12.Init.Prescaler * stpr_set->stepfreq_set)) - 1);
	__HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, (tim12_clock / (htim12.Init.Prescaler * stpr_set->stepfreq_set)) / 2);
}

/**	
 * @brief Get fault flag of stepper.
 * @param stpr_flag structure ptr
 * @return fault flag
 */
uint8_t Stepper_FaultFlagGet(stpr_flag_t* stpr_flag)
{
	stpr_flag->fault_flag = HAL_GPIO_ReadPin(STEPPER_nFLT_GPIO_Port, STEPPER_nFLT_Pin);
	return stpr_flag->fault_flag;
}

/**	
 * @brief Set decay mode of stepper.
 * @param stpr_set structure ptr
 * @return home flag
 */
uint8_t Stepper_HomeFlagGet(stpr_flag_t* stpr_flag)
{
	stpr_flag->home_flag = HAL_GPIO_ReadPin(STEPPER_nHOME_GPIO_Port, STEPPER_nHOME_Pin);
	return stpr_flag->home_flag;
}

/**	
 * @brief Start stepper.
 */
void Stepper_Start(void)
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
}
