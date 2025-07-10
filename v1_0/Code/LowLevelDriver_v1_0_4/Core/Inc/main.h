/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLDC3_BRA_Pin GPIO_PIN_5
#define BLDC3_BRA_GPIO_Port GPIOE
#define BLDC3_SPD_Pin GPIO_PIN_6
#define BLDC3_SPD_GPIO_Port GPIOE
#define BLDC3_REV_Pin GPIO_PIN_13
#define BLDC3_REV_GPIO_Port GPIOC
#define BLDC3_FG_Pin GPIO_PIN_0
#define BLDC3_FG_GPIO_Port GPIOC
#define BLDC2_BRA_Pin GPIO_PIN_1
#define BLDC2_BRA_GPIO_Port GPIOC
#define BLDC2_REV_Pin GPIO_PIN_2
#define BLDC2_REV_GPIO_Port GPIOC
#define BLDC2_FG_Pin GPIO_PIN_3
#define BLDC2_FG_GPIO_Port GPIOC
#define BLDC2_SPD_Pin GPIO_PIN_0
#define BLDC2_SPD_GPIO_Port GPIOA
#define BLDC4_BRA_Pin GPIO_PIN_4
#define BLDC4_BRA_GPIO_Port GPIOA
#define BLDC4_REV_Pin GPIO_PIN_5
#define BLDC4_REV_GPIO_Port GPIOA
#define BLDC4_FG_Pin GPIO_PIN_6
#define BLDC4_FG_GPIO_Port GPIOA
#define BLDC4_SPD_Pin GPIO_PIN_7
#define BLDC4_SPD_GPIO_Port GPIOA
#define BLDC1_BRA_Pin GPIO_PIN_0
#define BLDC1_BRA_GPIO_Port GPIOB
#define BLDC1_FG_Pin GPIO_PIN_1
#define BLDC1_FG_GPIO_Port GPIOB
#define BLDC1_REV_Pin GPIO_PIN_7
#define BLDC1_REV_GPIO_Port GPIOE
#define BLDC1_SPD_Pin GPIO_PIN_9
#define BLDC1_SPD_GPIO_Port GPIOE
#define STEPPER_nHOME_Pin GPIO_PIN_15
#define STEPPER_nHOME_GPIO_Port GPIOE
#define STEPPER_MODE2_Pin GPIO_PIN_12
#define STEPPER_MODE2_GPIO_Port GPIOB
#define STEPPER_MODE1_Pin GPIO_PIN_13
#define STEPPER_MODE1_GPIO_Port GPIOB
#define STEPPER_MODE0_Pin GPIO_PIN_14
#define STEPPER_MODE0_GPIO_Port GPIOB
#define STEPPER_STEP_Pin GPIO_PIN_15
#define STEPPER_STEP_GPIO_Port GPIOB
#define STEPPER_nENBL_Pin GPIO_PIN_8
#define STEPPER_nENBL_GPIO_Port GPIOD
#define STEPPER_DIR_Pin GPIO_PIN_9
#define STEPPER_DIR_GPIO_Port GPIOD
#define STEPPER_DECAY_Pin GPIO_PIN_10
#define STEPPER_DECAY_GPIO_Port GPIOD
#define STEPPER_nFLT_Pin GPIO_PIN_6
#define STEPPER_nFLT_GPIO_Port GPIOC
#define STEPPER_nSLP_Pin GPIO_PIN_7
#define STEPPER_nSLP_GPIO_Port GPIOC
#define STEPPER_nRST_Pin GPIO_PIN_8
#define STEPPER_nRST_GPIO_Port GPIOC
#define PUMP_IN2_Pin GPIO_PIN_8
#define PUMP_IN2_GPIO_Port GPIOB
#define PUMP_IN1_Pin GPIO_PIN_9
#define PUMP_IN1_GPIO_Port GPIOB
#define PUMP_VREF_Pin GPIO_PIN_0
#define PUMP_VREF_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
