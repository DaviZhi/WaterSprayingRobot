#include "chassis.h"

void Chassis_Start(chassis_set_t* chassis_set)
{
	BLDC_Start(&chassis_set->chassis_bldc_set[LF], LF);
	BLDC_Start(&chassis_set->chassis_bldc_set[RF], RF);
	BLDC_Start(&chassis_set->chassis_bldc_set[LB], LB);
	BLDC_Start(&chassis_set->chassis_bldc_set[RB], RB);
}

void Chassis_SpeedTransform(chassis_set_t* chassis_set)	//X-shape
{
	chassis_set->chassis_bldc_set[LB].speed_set = chassis_set->chassis_vx_set + chassis_set->chassis_vy_set - 
												  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	chassis_set->chassis_bldc_set[LF].speed_set = chassis_set->chassis_vx_set - chassis_set->chassis_vy_set - 
												  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	chassis_set->chassis_bldc_set[RF].speed_set = chassis_set->chassis_vx_set + chassis_set->chassis_vy_set + 
												  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
	
	chassis_set->chassis_bldc_set[RB].speed_set = chassis_set->chassis_vx_set - chassis_set->chassis_vy_set + 
												  chassis_set->chassis_vz_set * CHASSIS_FACTOR;
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
