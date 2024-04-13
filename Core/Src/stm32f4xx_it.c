/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern ADC_HandleTypeDef hadc1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC11_A_Pin);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
  if(HAL_GPIO_ReadPin(ENC11_A_GPIO_Port, ENC11_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC11_B_GPIO_Port, ENC11_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC34_A_Pin);
  /* USER CODE BEGIN EXTI1_IRQn 1 */
  if(HAL_GPIO_ReadPin(ENC34_A_GPIO_Port, ENC34_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC34_B_GPIO_Port, ENC34_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }
  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */

  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC13_A_Pin);
  /* USER CODE BEGIN EXTI2_IRQn 1 */
  if(HAL_GPIO_ReadPin(ENC13_A_GPIO_Port, ENC13_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC11_B_GPIO_Port, ENC11_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }

  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC14_A_Pin);
  /* USER CODE BEGIN EXTI4_IRQn 1 */
  if(HAL_GPIO_ReadPin(ENC14_A_GPIO_Port, ENC14_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC14_B_GPIO_Port, ENC14_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles ADC1, ADC2 and ADC3 interrupts.
  */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

  /* USER CODE END ADC_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC22_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC44_B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC23_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC21_A_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  if(HAL_GPIO_ReadPin(ENC22_A_GPIO_Port, ENC22_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC22_B_GPIO_Port, ENC22_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }
    if(HAL_GPIO_ReadPin(ENC44_B_GPIO_Port, ENC44_B_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC44_A_GPIO_Port, ENC44_A_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
    if(HAL_GPIO_ReadPin(ENC23_A_GPIO_Port, ENC23_A_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC23_B_GPIO_Port, ENC23_B_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
    if(HAL_GPIO_ReadPin(ENC43_A_GPIO_Port, ENC43_A_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC43_B_GPIO_Port, ENC43_B_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(ENC32_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC43_B_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC31_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC33_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC42_A_Pin);
  HAL_GPIO_EXTI_IRQHandler(ENC12_A_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
  if(HAL_GPIO_ReadPin(ENC32_A_GPIO_Port, ENC32_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC32_B_GPIO_Port, ENC32_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }
    if(HAL_GPIO_ReadPin(ENC43_B_GPIO_Port, ENC43_B_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC43_A_GPIO_Port, ENC43_A_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
  if(HAL_GPIO_ReadPin(ENC31_A_GPIO_Port, ENC31_A_Pin) == GPIO_PIN_SET){
    // Encoder 1
    if(HAL_GPIO_ReadPin(ENC31_B_GPIO_Port, ENC31_B_Pin) == GPIO_PIN_SET){
      // Clockwise
    }else{
      // Counter Clockwise
    }
  }
    if(HAL_GPIO_ReadPin(ENC33_A_GPIO_Port, ENC33_A_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC33_B_GPIO_Port, ENC33_B_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
    if(HAL_GPIO_ReadPin(ENC42_A_GPIO_Port, ENC42_A_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC42_B_GPIO_Port, ENC42_B_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
    if(HAL_GPIO_ReadPin(ENC12_A_GPIO_Port, ENC12_A_Pin) == GPIO_PIN_SET){
        // Encoder 1
        if(HAL_GPIO_ReadPin(ENC12_B_GPIO_Port, ENC12_B_Pin) == GPIO_PIN_SET){
        // Clockwise
        }else{
        // Counter Clockwise
        }
    }
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
