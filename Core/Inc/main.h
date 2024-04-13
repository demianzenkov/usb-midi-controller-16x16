/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define ENC34_B_Pin GPIO_PIN_0
#define ENC34_B_GPIO_Port GPIOA
#define ENC34_A_Pin GPIO_PIN_1
#define ENC34_A_GPIO_Port GPIOA
#define ENC34_A_EXTI_IRQn EXTI1_IRQn
#define ADC_BT1_Pin GPIO_PIN_2
#define ADC_BT1_GPIO_Port GPIOA
#define ADC_BT2_Pin GPIO_PIN_3
#define ADC_BT2_GPIO_Port GPIOA
#define ADC_BT3_Pin GPIO_PIN_4
#define ADC_BT3_GPIO_Port GPIOA
#define ADC_BT4_Pin GPIO_PIN_5
#define ADC_BT4_GPIO_Port GPIOA
#define ENC44_A_Pin GPIO_PIN_6
#define ENC44_A_GPIO_Port GPIOA
#define ENC44_B_Pin GPIO_PIN_7
#define ENC44_B_GPIO_Port GPIOA
#define ENC44_B_EXTI_IRQn EXTI9_5_IRQn
#define ENC43_A_Pin GPIO_PIN_9
#define ENC43_A_GPIO_Port GPIOE
#define ENC43_B_Pin GPIO_PIN_11
#define ENC43_B_GPIO_Port GPIOE
#define ENC43_B_EXTI_IRQn EXTI15_10_IRQn
#define ENC33_B_Pin GPIO_PIN_12
#define ENC33_B_GPIO_Port GPIOE
#define ENC33_A_Pin GPIO_PIN_13
#define ENC33_A_GPIO_Port GPIOE
#define ENC33_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC42_A_Pin GPIO_PIN_14
#define ENC42_A_GPIO_Port GPIOE
#define ENC42_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC42_B_Pin GPIO_PIN_15
#define ENC42_B_GPIO_Port GPIOE
#define ENC41_A_Pin GPIO_PIN_12
#define ENC41_A_GPIO_Port GPIOB
#define ENC41_B_Pin GPIO_PIN_13
#define ENC41_B_GPIO_Port GPIOB
#define ENC32_A_Pin GPIO_PIN_10
#define ENC32_A_GPIO_Port GPIOD
#define ENC32_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC32_B_Pin GPIO_PIN_11
#define ENC32_B_GPIO_Port GPIOD
#define ENC31_A_Pin GPIO_PIN_12
#define ENC31_A_GPIO_Port GPIOD
#define ENC31_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC31_B_Pin GPIO_PIN_13
#define ENC31_B_GPIO_Port GPIOD
#define ENC24_B_Pin GPIO_PIN_14
#define ENC24_B_GPIO_Port GPIOD
#define ENC24_A_Pin GPIO_PIN_15
#define ENC24_A_GPIO_Port GPIOD
#define ENC22_A_Pin GPIO_PIN_6
#define ENC22_A_GPIO_Port GPIOC
#define ENC22_A_EXTI_IRQn EXTI9_5_IRQn
#define ENC22_B_Pin GPIO_PIN_7
#define ENC22_B_GPIO_Port GPIOC
#define ENC23_A_Pin GPIO_PIN_8
#define ENC23_A_GPIO_Port GPIOC
#define ENC23_A_EXTI_IRQn EXTI9_5_IRQn
#define ENC23_B_Pin GPIO_PIN_9
#define ENC23_B_GPIO_Port GPIOC
#define ENC21_B_Pin GPIO_PIN_8
#define ENC21_B_GPIO_Port GPIOA
#define ENC21_A_Pin GPIO_PIN_9
#define ENC21_A_GPIO_Port GPIOA
#define ENC21_A_EXTI_IRQn EXTI9_5_IRQn
#define ENC12_A_Pin GPIO_PIN_15
#define ENC12_A_GPIO_Port GPIOA
#define ENC12_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC11_A_Pin GPIO_PIN_0
#define ENC11_A_GPIO_Port GPIOD
#define ENC11_A_EXTI_IRQn EXTI0_IRQn
#define ENC11_B_Pin GPIO_PIN_1
#define ENC11_B_GPIO_Port GPIOD
#define ENC13_A_Pin GPIO_PIN_2
#define ENC13_A_GPIO_Port GPIOD
#define ENC13_A_EXTI_IRQn EXTI2_IRQn
#define ENC13_B_Pin GPIO_PIN_3
#define ENC13_B_GPIO_Port GPIOD
#define ENC14_A_Pin GPIO_PIN_4
#define ENC14_A_GPIO_Port GPIOD
#define ENC14_A_EXTI_IRQn EXTI4_IRQn
#define ENC14_B_Pin GPIO_PIN_5
#define ENC14_B_GPIO_Port GPIOD
#define ENC12_B_Pin GPIO_PIN_8
#define ENC12_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
