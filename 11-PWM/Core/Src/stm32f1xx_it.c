/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f1xx_it.c
 * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "tim.h"
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

/* Debounce configuration: 50 ms */
#define KEY_DEBOUNCE_MS 50U

/* store last processed tick for each key pin */
static uint32_t key_last_tick_UP = 0;
static uint32_t key_last_tick_DOWN = 0;
static uint32_t key_last_tick_LEFT = 0;
static uint32_t key_last_tick_RIGHT = 0;
static uint32_t key_last_tick_OK = 0;
static uint32_t key_last_tick_ESC = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
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
 * @brief This function handles Prefetch fault, memory access fault.
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
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
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
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles EXTI line[9:5] interrupts.
 */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_LEFT_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_ESC_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_OK_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_UP_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_DOWN_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_RIGHT_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint32_t now = HAL_GetTick();

  if (GPIO_Pin == KEY_UP_Pin)
  {
    if ((now - key_last_tick_UP) >= KEY_DEBOUNCE_MS)
    {
      key_last_tick_UP = now;
      /* LED_control(LED1, ON); */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); /* 占空比0%，亮度100% */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
    }
  }
  else if (GPIO_Pin == KEY_DOWN_Pin)
  {
    if ((now - key_last_tick_DOWN) >= KEY_DEBOUNCE_MS)
    {
      key_last_tick_DOWN = now;
      /* LED_control(LED1, OFF); */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 20); /* 占空比20%，亮度80% */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 20);
    }
  }
  else if (GPIO_Pin == KEY_LEFT_Pin)
  {
    if ((now - key_last_tick_LEFT) >= KEY_DEBOUNCE_MS)
    {
      key_last_tick_LEFT = now;
      /* LED_control(LED2, ON); */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 40); /* 占空比40%，亮度60% */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 40);
    }
  }
  else if (GPIO_Pin == KEY_RIGHT_Pin)
  {
    if ((now - key_last_tick_RIGHT) >= KEY_DEBOUNCE_MS)
    {
      key_last_tick_RIGHT = now;
      /* LED_control(LED2, OFF); */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 60); /* 占空比60%，亮度40% */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 60);
    }
  }
  else if (GPIO_Pin == KEY_OK_Pin)
  {
    if ((now - key_last_tick_OK) >= KEY_DEBOUNCE_MS)
    {
      key_last_tick_OK = now;
      /* BEEP_control(ON); */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 80); /* 占空比80%，亮度20% */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 80);
    }
  }
  else if (GPIO_Pin == KEY_ESC_Pin)
  {
    if ((now - key_last_tick_ESC) >= KEY_DEBOUNCE_MS)
    {
      key_last_tick_ESC = now;
      /* BEEP_control(OFF); */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 100); /* 占空比100%，亮度0% */
      __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 100);
    }
  }
}

/* USER CODE END 1 */
