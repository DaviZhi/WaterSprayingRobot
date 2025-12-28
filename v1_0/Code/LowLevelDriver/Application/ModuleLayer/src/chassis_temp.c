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
#ifdef CHASSIS_SHAPE_O
	/* O-shaped (Diamond) Mecanum wheel installation formula */
	chassis_set->chassis_target_set[LF] = chassis_set->chassis_vx_set + chassis_set->chassis_vy_set + 
										  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[LB] = chassis_set->chassis_vx_set - chassis_set->chassis_vy_set - 
										  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	/* RF and RB motors have reversed direction, so negate their values */
	chassis_set->chassis_target_set[RF] = -(chassis_set->chassis_vx_set - chassis_set->chassis_vy_set + 
											 chassis_set->chassis_vz_set * CHASSIS_FACTOR);

	chassis_set->chassis_target_set[RB] = -(chassis_set->chassis_vx_set + chassis_set->chassis_vy_set - 
											 chassis_set->chassis_vz_set * CHASSIS_FACTOR);
#else
	/* X-shaped Mecanum wheel installation formula (default) */
	chassis_set->chassis_target_set[LB] = chassis_set->chassis_vx_set + chassis_set->chassis_vy_set - 
										  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	chassis_set->chassis_target_set[LF] = chassis_set->chassis_vx_set - chassis_set->chassis_vy_set - 
										  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	/* RF and RB motors have reversed direction, so negate their values */
	chassis_set->chassis_target_set[RF] = -(chassis_set->chassis_vx_set + chassis_set->chassis_vy_set + 
											 chassis_set->chassis_vz_set * CHASSIS_FACTOR);

	chassis_set->chassis_target_set[RB] = -(chassis_set->chassis_vx_set - chassis_set->chassis_vy_set + 
											 chassis_set->chassis_vz_set * CHASSIS_FACTOR);
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

		