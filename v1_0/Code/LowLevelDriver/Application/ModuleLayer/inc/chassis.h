#ifndef BIGZ_CHASSIS_H
#define BIGZ_CHASSIS_H

#include "rmt_driver.h"
#include "bldc_driver.h"
#include "bldc_xdefine.h"

#define CHASSIS_FACTOR	1

/* Chassis shape configuration */
/* Define one of the following macros to select chassis installation type */
/* Option 1: X-shaped Mecanum wheel installation */
/* #define CHASSIS_SHAPE_X */
/* Option 2: O-shaped (Diamond) Mecanum wheel installation */
/* #define CHASSIS_SHAPE_O */

/* Default to X-shaped if neither is defined */
#if !defined(CHASSIS_SHAPE_X) && !defined(CHASSIS_SHAPE_O)
	#define CHASSIS_SHAPE_X
#endif

/* Remote channel mapping parameters */
#define REMOTE_CH_MIN		200			/* Remote channel minimum value */
#define REMOTE_CH_MAX		1800		/* Remote channel maximum value */
#define REMOTE_CH_CENTER	1000		/* Remote channel center value */
#define REMOTE_CH_RANGE		800			/* Half range: (MAX - MIN) / 2 */
#define REMOTE_CH_DEADZONE	30			/* Dead zone range around center value (1000 ± DEADZONE) */
#define CHASSIS_SPD_MAX		1000		/* Maximum chassis speed (corresponds to BLDC_SPDMAX) */

typedef enum
{
	CHASSIS_REVO_CCW,
	CHASSIS_REVO_CW,
	
}chassis_revo_set_e;

typedef enum
{
	CHASSIS_BRAKE,
	CHASSIS_LOOSE,
}chassis_brake_set_e;

typedef struct
{
	bldc_set_t chassis_bldc_set[BLDC_NUM];
	int16_t chassis_target_set[BLDC_NUM];
	int16_t chassis_vx_set;
	int16_t chassis_vy_set;
	int16_t chassis_vz_set;
	
	uint16_t chassis_receive_remote[3];

}chassis_set_t;

void Chassis_Init(chassis_set_t* chassis_set);
void Chassis_Start(chassis_set_t* chassis_set);
void Chassis_Stop(chassis_set_t* chassis_set);
void Chassis_BrakeSet(chassis_set_t* chassis_set, chassis_brake_set_e chassis_brake_set);
void Chassis_SpeedTransform(chassis_set_t* chassis_set);
void Chassis_RemoteToSpeed(chassis_set_t* chassis_set, uint16_t remote_ch_x, uint16_t remote_ch_y, uint16_t remote_ch_z);
void Chassis_TargetToPWM(chassis_set_t* chassis_set);

#endif
