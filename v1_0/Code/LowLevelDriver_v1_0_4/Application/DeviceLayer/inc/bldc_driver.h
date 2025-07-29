#ifndef BLDC_DRIVER_H
#define BLDC_DRIVER_H

#include "tim.h"
#include "adc.h"

typedef enum
{
	LF = 2,
	RF = 0,
	LB = 1,
	RB = 3,
}bldc_num_e;

typedef struct
{
	GPIO_PinState brake_set;
	GPIO_PinState revo_set;
	uint16_t speed_set;
	uint16_t speed_get;
	
}bldc_set_t;

//typedef struct
//{
//	bldc_set_t bldc_set;
//	bldc_num_e bldc_num;
//	
//}bldc_t;

void BLDC_EMO(bldc_set_t* bldc_set);
void BLDC_Init(bldc_set_t* bldc_set);
void BLDC_BrakeSet(bldc_set_t* bldc_set, bldc_num_e bldc_num, GPIO_PinState bra_set);
void BLDC_RevoSet(bldc_set_t* bldc_set, bldc_num_e bldc_num, GPIO_PinState rev_set);
void BLDC_SpeedSet(bldc_set_t* bldc_set, bldc_num_e bldc_num, uint16_t spd_set);

void BLDC_xQueueCreate(void);
void BLDC_SpeedSend(void);
void BLDC_SpeedReceive(bldc_set_t* bldc_set);

void BLDC_Start(bldc_num_e bldc_num);
void BLDC_Stop(bldc_num_e bldc_num);

#endif
