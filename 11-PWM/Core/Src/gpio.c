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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = KEY_OK_Pin|KEY_UP_Pin|KEY_DOWN_Pin|KEY_RIGHT_Pin
                          |KEY_LEFT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_ESC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_ESC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
// void led(void)
// {
//   HAL_GPIO_WritePin(GPIOB,LED1_Pin,GPIO_PIN_RESET);
// }

/**
 * @brief  控制LED1和LED2亮灭的
 *@note    详细细节描述，ON控制LED亮,OFF控制LED灭
 *@param   device:可以是两个LED,两个宏，在gpio.h中定义
 *         cmd:用来控制LED亮灭的指令
 *             ON:LED亮
 *           OFF：LED灭
 * @retval None
 */

void LED_control(uint8_t device, uint8_t cmd)
{
  if (device == LED1)
  {
    if (cmd == ON)
    {
      // HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
    }
    else if (cmd == OFF)
    {
      // HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET);
    }
  }
  else if (device == LED2)
  {
    if (cmd == ON)
    {
      // HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET);
    }
    else if (cmd == OFF)
    {
      // HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET);
    }
  }
}

void LED_Test(void)
{
  LED_control(LED1, ON);
  LED_control(LED2, OFF);
  HAL_Delay(500);
  LED_control(LED1, OFF);
  LED_control(LED2, ON);
  HAL_Delay(500);
}

/**
 * @brief  控制蜂鸣器的
 *@note    详细细节描述，ON蜂鸣器工作,OFF控制蜂鸣器不工作
 *         cmd:用来控制BEEP指令
 *             ON:BEEP工作
 *           OFF：BEEP不工作
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

/**
 * @brief  获取按键的值
 *@note    详细细节描述，根据按下的按键，返回对应的键值
 * @retval None
 */
uint8_t KEY_Scan(void)
{
  uint8_t keyval = 0;
  if (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_RESET)
  {
    keyval = KEY_UP;
  }
  else if (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) == GPIO_PIN_RESET)
  {
    keyval = KEY_DOWN;
  }
  else if (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) == GPIO_PIN_RESET)
  {
    keyval = KEY_LEFT;
  }
  else if (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin) == GPIO_PIN_RESET)
  {
    keyval = KEY_RIGHT;
  }
  else if (HAL_GPIO_ReadPin(KEY_OK_GPIO_Port, KEY_OK_Pin) == GPIO_PIN_RESET)
  {
    keyval = KEY_OK;
  }
  else if (HAL_GPIO_ReadPin(KEY_ESC_GPIO_Port, KEY_ESC_Pin) == GPIO_PIN_RESET)
  {
    keyval = KEY_ESC;
  }
  return keyval;
}

void KEY_Test(void)
{
  uint8_t keyval = KEY_Scan();
  if (keyval > 0)
  {
    if (keyval == KEY_UP)
    {
      LED_control(LED1, ON);
    }
    else if (keyval == KEY_DOWN)
    {
      LED_control(LED1, OFF);
    }
    else if (keyval == KEY_LEFT)
    {
      LED_control(LED2, ON);
    }
    else if (keyval == KEY_RIGHT)
    {
      LED_control(LED2, OFF);
    }
    else if (keyval == KEY_OK)
    {
      BEEP_control(ON);
    }
    else if (keyval == KEY_ESC)
    {
      BEEP_control(OFF);
    }
  }
}
/* USER CODE END 2 */
