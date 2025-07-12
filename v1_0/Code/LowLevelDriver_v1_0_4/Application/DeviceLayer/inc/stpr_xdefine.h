#ifndef STPR_XDEFINE_H
#define STPR_XDEFINE_H

//microstepping indexer
//#define		STEP_FULL		0x0
//#define		STEP_HALF		0x1
//#define		STEP_QUARTER	0x2
//#define		STEP_8MICRO		0x3
//#define		STEP_16MICRO	0x4
//#define		STEP_32MICRO	0x5

//enable status
#define		STEPPER_ENABLE		GPIO_PIN_RESET
#define		STEPPER_DISABLE		GPIO_PIN_SET

//reset status
#define		STEPPER_RESET		GPIO_PIN_RESET
#define		STEPPER_SET			GPIO_PIN_SET

//sleep status
#define		STEPPER_SLEEP		GPIO_PIN_RESET
#define		STEPPER_ACTIVE		GPIO_PIN_SET

//decay set
#define		STEPPER_SLOWDECAY	GPIO_PIN_RESET
#define		STEPPER_FASTDECAY	GPIO_PIN_SET

#endif
