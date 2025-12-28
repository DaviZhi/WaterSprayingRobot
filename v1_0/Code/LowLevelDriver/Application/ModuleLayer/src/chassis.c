#include "chassis.h"

void Chassis_Init(chassis_set_t* chassis_set)
{
	BLDC_Init(&chassis_set->chassis_bldc_set[LF], LF);
	BLDC_Init(&chassis_set->chassis_bldc_set[RF], RF);
	BLDC_Init(&chassis_set->chassis_bldc_set[LB], LB);
	BLDC_Init(&chassis_set->chassis_bldc_set[RB], RB);
	
	for(uint8_t i = 0; i < BLDC_NUM; i++)
	{
		chassis_set->chassis_target_set[i] = 0;
	}
	chassis_set->chassis_vx_set = 0;
	chassis_set->chassis_vy_set = 0;
	chassis_set->chassis_vz_set = 0;
	
	/* Initialize remote receive buffer to center values to avoid invalid data at startup */
	for(uint8_t i = 0; i < 3; i++)
	{
		chassis_set->chassis_receive_remote[i] = REMOTE_CH_CENTER;
	}
}

void Chassis_Start(chassis_set_t* chassis_set)
{
	BLDC_Start(&chassis_set->chassis_bldc_set[LF], LF);
	BLDC_Start(&chassis_set->chassis_bldc_set[RF], RF);
	BLDC_Start(&chassis_set->chassis_bldc_set[LB], LB);
	BLDC_Start(&chassis_set->chassis_bldc_set[RB], RB);
}

void Chassis_Stop(chassis_set_t* chassis_set)
{
	BLDC_Stop(&chassis_set->chassis_bldc_set[LF], LF);
	BLDC_Stop(&chassis_set->chassis_bldc_set[RF], RF);
	BLDC_Stop(&chassis_set->chassis_bldc_set[LB], LB);
	BLDC_Stop(&chassis_set->chassis_bldc_set[RB], RB);
}

void Chassis_BrakeSet(chassis_set_t* chassis_set, chassis_brake_set_e chassis_brake_set)
{
	switch(chassis_brake_set)
	{
		case CHASSIS_BRAKE:
		{
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[LF], LF, BLDC_BRAKE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[RF], RF, BLDC_BRAKE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[LB], LB, BLDC_BRAKE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[RB], RB, BLDC_BRAKE);
			break;
		}
		case CHASSIS_LOOSE:
		{
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[LF], LF, BLDC_LOOSE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[RF], RF, BLDC_LOOSE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[LB], LB, BLDC_LOOSE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[RB], RB, BLDC_LOOSE);
			break;
		}
		default:
		{
			break;
		}
	}
	
}

void Chassis_SpeedTransform(chassis_set_t* chassis_set)
{
	/* Reverse vy and vz signs to compensate for RF and RB motor direction reversal */
	/* RF and RB: CW = backward, CCW = forward (opposite to LB and LF) */
	int16_t vy_reversed = -chassis_set->chassis_vy_set;
	int16_t vz_reversed = -chassis_set->chassis_vz_set;
	
#ifdef CHASSIS_SHAPE_X
	/* X-shaped Mecanum wheel installation formula */
	chassis_set->chassis_target_set[LB] = chassis_set->chassis_vx_set + vy_reversed - 
										  vz_reversed * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[LF] = chassis_set->chassis_vx_set - vy_reversed - 
										  vz_reversed * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[RF] = chassis_set->chassis_vx_set + vy_reversed + 
										  vz_reversed * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[RB] = chassis_set->chassis_vx_set - vy_reversed + 
										  vz_reversed * CHASSIS_FACTOR;
#elif defined(CHASSIS_SHAPE_O)
	/* O-shaped (Diamond) Mecanum wheel installation formula */
	chassis_set->chassis_target_set[LF] = chassis_set->chassis_vx_set + vy_reversed + 
										  vz_reversed * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[RF] = chassis_set->chassis_vx_set - vy_reversed + 
										  vz_reversed * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[LB] = chassis_set->chassis_vx_set - vy_reversed - 
										  vz_reversed * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[RB] = chassis_set->chassis_vx_set + vy_reversed - 
										  vz_reversed * CHASSIS_FACTOR;
#else
	#error "Please define either CHASSIS_SHAPE_X or CHASSIS_SHAPE_O in chassis.h"
#endif
}

/**
 * @brief Map remote channel values (200-1800) to chassis speed set values (int16_t)
 * @param chassis_set structure ptr
 * @param remote_ch_x remote channel X value
 * @param remote_ch_y remote channel Y value
 * @param remote_ch_z remote channel Z value
 * @note Remote channel center value (1000) maps to 0 (stop)
 *       Remote channel range 200-1800 maps to -1000 to +1000
 */
void Chassis_RemoteToSpeed(chassis_set_t* chassis_set, uint16_t remote_ch_x, uint16_t remote_ch_y, uint16_t remote_ch_z)
{
	int32_t temp;
	int32_t ch_offset;
	
	/* Check if remote channel values are valid (within valid range) */
	/* If invalid (e.g., 0 or out of range), set to 0 to avoid unexpected movement */
	if(remote_ch_x < REMOTE_CH_MIN || remote_ch_x > REMOTE_CH_MAX)
	{
		chassis_set->chassis_vx_set = 0;
	}
	else
	{
		/* Apply dead zone for channel X */
		ch_offset = (int32_t)remote_ch_x - REMOTE_CH_CENTER;
		if(ch_offset > -REMOTE_CH_DEADZONE && ch_offset < REMOTE_CH_DEADZONE)
		{
			/* In dead zone, set to center value (maps to 0) */
			chassis_set->chassis_vx_set = 0;
		}
		else
		{
			/* Map remote channel X (200-1800, center 1000) to chassis_vx_set (-1000 to +1000) */
			temp = (ch_offset * CHASSIS_SPD_MAX) / REMOTE_CH_RANGE;
			if(temp > CHASSIS_SPD_MAX)
				chassis_set->chassis_vx_set = CHASSIS_SPD_MAX;
			else if(temp < -CHASSIS_SPD_MAX)
				chassis_set->chassis_vx_set = -CHASSIS_SPD_MAX;
			else
				chassis_set->chassis_vx_set = (int16_t)temp;
		}
	}
	
	if(remote_ch_y < REMOTE_CH_MIN || remote_ch_y > REMOTE_CH_MAX)
	{
		chassis_set->chassis_vy_set = 0;
	}
	else
	{
		/* Apply dead zone for channel Y */
		ch_offset = (int32_t)remote_ch_y - REMOTE_CH_CENTER;
		if(ch_offset > -REMOTE_CH_DEADZONE && ch_offset < REMOTE_CH_DEADZONE)
		{
			/* In dead zone, set to center value (maps to 0) */
			chassis_set->chassis_vy_set = 0;
		}
		else
		{
			/* Map remote channel Y (200-1800, center 1000) to chassis_vy_set (-1000 to +1000) */
			temp = (ch_offset * CHASSIS_SPD_MAX) / REMOTE_CH_RANGE;
			if(temp > CHASSIS_SPD_MAX)
				chassis_set->chassis_vy_set = CHASSIS_SPD_MAX;
			else if(temp < -CHASSIS_SPD_MAX)
				chassis_set->chassis_vy_set = -CHASSIS_SPD_MAX;
			else
				chassis_set->chassis_vy_set = (int16_t)temp;
		}
	}
	
	if(remote_ch_z < REMOTE_CH_MIN || remote_ch_z > REMOTE_CH_MAX)
	{
		chassis_set->chassis_vz_set = 0;
	}
	else
	{
		/* Apply dead zone for channel Z */
		ch_offset = (int32_t)remote_ch_z - REMOTE_CH_CENTER;
		if(ch_offset > -REMOTE_CH_DEADZONE && ch_offset < REMOTE_CH_DEADZONE)
		{
			/* In dead zone, set to center value (maps to 0) */
			chassis_set->chassis_vz_set = 0;
		}
		else
		{
			/* Map remote channel Z (200-1800, center 1000) to chassis_vz_set (-1000 to +1000) */
			temp = (ch_offset * CHASSIS_SPD_MAX) / REMOTE_CH_RANGE;
			if(temp > CHASSIS_SPD_MAX)
				chassis_set->chassis_vz_set = CHASSIS_SPD_MAX;
			else if(temp < -CHASSIS_SPD_MAX)
				chassis_set->chassis_vz_set = -CHASSIS_SPD_MAX;
			else
				chassis_set->chassis_vz_set = (int16_t)temp;
		}
	}
}

/**
 * @brief Map chassis_target_set values (int16_t, can be negative) to PWM duty cycle (0-1000) and set motor direction
 * @param chassis_set structure ptr
 * @note Motor direction mapping:
 *       LB, LF: Positive -> CW (forward), Negative -> CCW (backward)
 *       RF, RB: Positive -> CCW (forward), Negative -> CW (backward)
 *       PWM value = absolute value of target_set (limited to 1000)
 */
void Chassis_TargetToPWM(chassis_set_t* chassis_set)
{
	int16_t target_temp;
	uint16_t pwm_value;
	GPIO_PinState direction;
	bldc_num_e bldc_num_array[BLDC_NUM] = {LF, RF, LB, RB};
	bldc_num_e bldc_num;
	
	for(uint8_t i = 0; i < BLDC_NUM; i++)
	{
		bldc_num = bldc_num_array[i];
		target_temp = chassis_set->chassis_target_set[bldc_num];
		
		/* Get absolute value and limit PWM to maximum (1000) */
		if(target_temp > CHASSIS_SPD_MAX)
			pwm_value = CHASSIS_SPD_MAX;
		else if(target_temp < -CHASSIS_SPD_MAX)
			pwm_value = CHASSIS_SPD_MAX;
		else
			pwm_value = (uint16_t)(target_temp >= 0 ? target_temp : -target_temp);
		
		/* Determine direction based on motor position and target sign */
		/* LB and LF: CW = forward (positive), CCW = backward (negative) */
		/* RF and RB: CCW = forward (positive), CW = backward (negative) */
		if(bldc_num == LB || bldc_num == LF)
		{
			/* Left side motors: positive -> CW, negative -> CCW */
			direction = (target_temp >= 0) ? BLDC_CW : BLDC_CCW;
		}
		else
		{
			/* Right side motors (RF, RB): positive -> CCW, negative -> CW (reversed) */
			direction = (target_temp >= 0) ? BLDC_CCW : BLDC_CW;
		}
		
		/* Set motor direction */
		/* Pass entire array pointer, not single element address */
		BLDC_RevoSet(chassis_set->chassis_bldc_set, bldc_num, direction);
		
		/* Set motor speed (PWM duty cycle) */
		BLDC_SpeedSet(chassis_set->chassis_bldc_set, bldc_num, pwm_value);
	}
}

#if 0
void Chassis_SpeedSet(chassis_set_t* chassis_set, uint16_t spd_set)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		chassis_set->chassis_bldc_set[i].speed_set = spd_set;
	}
	
	BLDC_SpeedSet(&chassis_set->chassis_bldc_set[LF], LF, chassis_set->chassis_bldc_set[LF].speed_set);
	BLDC_SpeedSet(&chassis_set->chassis_bldc_set[RF], RF, chassis_set->chassis_bldc_set[RF].speed_set);
	BLDC_SpeedSet(&chassis_set->chassis_bldc_set[LB], LB, chassis_set->chassis_bldc_set[LB].speed_set);
	BLDC_SpeedSet(&chassis_set->chassis_bldc_set[RB], RB, chassis_set->chassis_bldc_set[RB].speed_set);
}

void Chassis_RevoSet(chassis_set_t* chassis_set, chassis_revo_set_e revo_set)
{
	switch(revo_set)
	{
		case CHASSIS_REVO_CCW:
		{
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[LF], LF, BLDC_CCW);
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[RF], RF, BLDC_CCW);
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[LB], LB, BLDC_CCW);
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[RB], RB, BLDC_CCW);
			break;
		}
		case CHASSIS_REVO_CW:
		{
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[LF], LF, BLDC_CW);
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[RF], RF, BLDC_CW);
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[LB], LB, BLDC_CW);
			BLDC_RevoSet(&chassis_set->chassis_bldc_set[RB], RB, BLDC_CW);
			break;
		}
		default:
		{
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[LF], LF, BLDC_BRAKE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[RF], RF, BLDC_BRAKE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[LB], LB, BLDC_BRAKE);
			BLDC_BrakeSet(&chassis_set->chassis_bldc_set[RB], RB, BLDC_BRAKE);
			break;
		}
	}
}

#endif
