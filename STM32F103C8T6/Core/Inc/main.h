/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f1xx_hal.h"

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
#define IMON_1_Pin GPIO_PIN_2
#define IMON_1_GPIO_Port GPIOA
#define IMON_2_Pin GPIO_PIN_3
#define IMON_2_GPIO_Port GPIOA
#define IMON_3_Pin GPIO_PIN_4
#define IMON_3_GPIO_Port GPIOA
#define IMON_4_Pin GPIO_PIN_5
#define IMON_4_GPIO_Port GPIOA
#define IMON_5_Pin GPIO_PIN_6
#define IMON_5_GPIO_Port GPIOA
#define INP_1_Pin GPIO_PIN_7
#define INP_1_GPIO_Port GPIOA
#define INP_2_Pin GPIO_PIN_0
#define INP_2_GPIO_Port GPIOB
#define INP_3_Pin GPIO_PIN_1
#define INP_3_GPIO_Port GPIOB
#define INP_4_Pin GPIO_PIN_2
#define INP_4_GPIO_Port GPIOB
#define INP_5_Pin GPIO_PIN_10
#define INP_5_GPIO_Port GPIOB
#define RUN_LED_Pin GPIO_PIN_8
#define RUN_LED_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_11
#define SW1_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_12
#define SW2_GPIO_Port GPIOA
#define PWEN_1_Pin GPIO_PIN_5
#define PWEN_1_GPIO_Port GPIOB
#define PWEN_2_Pin GPIO_PIN_6
#define PWEN_2_GPIO_Port GPIOB
#define PWEN_3_Pin GPIO_PIN_7
#define PWEN_3_GPIO_Port GPIOB
#define PWEN_4_Pin GPIO_PIN_8
#define PWEN_4_GPIO_Port GPIOB
#define PWEN_5_Pin GPIO_PIN_9
#define PWEN_5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
