#ifndef STPR_XDEFINE_H
#define STPR_XDEFINE_H

#define		STEPPER_STEP_ANGLE	1.8f

/* stepper rotation direction set */
#define		STEPPER_CCW			GPIO_PIN_RESET
#define		STEPPER_CW			GPIO_PIN_SET

/* stepper enable set */
#define		STEPPER_ENABLE		GPIO_PIN_RESET
#define		STEPPER_DISABLE		GPIO_PIN_SET

/* stepper reset or set status set */
#define		STEPPER_RESET		GPIO_PIN_RESET
#define		STEPPER_SET			GPIO_PIN_SET

/* stepper work mode set */
#define		STEPPER_SLEEP		GPIO_PIN_RESET
#define		STEPPER_ACTIVE		GPIO_PIN_SET

/* stepper decay mode set */
#define		STEPPER_SLOWDECAY	GPIO_PIN_RESET
#define		STEPPER_FASTDECAY	GPIO_PIN_SET

#endif
