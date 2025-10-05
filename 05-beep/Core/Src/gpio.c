/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BEEP_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = BEEP_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
// void led(void)
// {
//   HAL_GPIO_WritePin(GPIOB,LED1_Pin,GPIO_PIN_RESET);
// }

/**
 * @brief  控制蜂鸣器的
 *@note    详细细节描述，ON蜂鸣器工作,OFF控制蜂鸣器不工作
 *         cmd:用来控制BEEP指令
 *             ON:BEEP工作
 *           OFF：BEEP不工作
 * @retval None
 */

/**
 * @brief  控制LED1和LED2亮灭的
 *@note    详细细节描述，ON控制LED亮,OFF控制LED灭
 *@param   device:可以是两个LED,两个宏，在gpio.h中定义
 *         cmd:用来控制LED亮灭的指令
 *             ON:LED亮
 *           OFF：LED灭
 * @retval None
 */
void BEEP_control(uint8_t cmd)
{

  if (cmd == ON)
  {
    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
  }
  else if (cmd == OFF)
  {
    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
  }
}

void BEEP_Test(void)
{
  BEEP_control(ON);
  HAL_Delay(200);
  BEEP_control(OFF);
  HAL_Delay(800);
}
/* USER CODE END 2 */
