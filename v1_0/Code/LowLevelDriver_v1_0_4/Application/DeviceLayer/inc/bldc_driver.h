#ifndef BLDC_DRIVER_H
#define BLDC_DRIVER_H

#include "tim.h"
#include "adc.h"

#include "dev.h"

/* Private enum---------*/
typedef enum
{
	LF = 2,		//left front bldc
	RF = 0,		//right front bldc
	LB = 1,     //left behind bldc
	RB = 3,     //right behind bldc
}bldc_num_e;

/* Private struct----------*/
typedef struct
{
	GPIO_PinState brake_set;
	GPIO_PinState revo_set;
	uint16_t speed_set;
	uint16_t speed_get;
	dev_status_e bldc_status;
	
}bldc_set_t;

/* BLDC_Imported function------------------------------------------------------*/
static void BLDC_EMO(bldc_set_t* bldc_set);

/* BLDC_Exported function------------------------------------------------------*/
void BLDC_Init(bldc_set_t* bldc_set, bldc_num_e bldc_num);
void BLDC_SetBrake(bldc_set_t* bldc_set, bldc_num_e bldc_num, GPIO_PinState bra_set);
void BLDC_SetRevo(bldc_set_t* bldc_set, bldc_num_e bldc_num, GPIO_PinState rev_set);
void BLDC_SetSpeed(bldc_set_t* bldc_set, bldc_num_e bldc_num, uint16_t spd_set);
void BLDC_xQueueCreate(void);
void BLDC_SpeedSend(void);
void BLDC_SpeedReceive(bldc_set_t* bldc_set);
void BLDC_Start(bldc_set_t* bldc_set, bldc_num_e bldc_num);
void BLDC_Stop(bldc_set_t* bldc_set, bldc_num_e bldc_num);

#endif
