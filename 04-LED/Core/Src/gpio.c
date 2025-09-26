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
#include "main.h"

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
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin;
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
  * @brief  控制LED1和LED2亮灭的
  *@note    详细细节描述，ON控制LED亮,OFF控制LED灭
  *@param   device:可以是两个LED,两个宏，在gpio.h中定义
  *         cmd:用来控制LED亮灭的指令
  *             ON:LED亮
  *           OFF：LED灭
  * @retval None
  */

  void led(void)
  {
    HAL_GPIO_WritePin(GPIOB,LED1_Pin,GPIO_PIN_RESET);
  }

void LED_control(uint8_t device,uint8_t cmd)
{
  if(device == LED1)
  {
    if(cmd == ON)
    {
      HAL_GPIO_WritePin(GPIOB,LED1_Pin,GPIO_PIN_RESET);
    }
    else if(cmd == OFF)
    {
      HAL_GPIO_WritePin(GPIOB,LED1_Pin,GPIO_PIN_SET);
    }
  }
  else if(device == LED2)
  {
    if(cmd == ON)
    {
      HAL_GPIO_WritePin(GPIOB,LED2_Pin,GPIO_PIN_RESET);
    }
    else if(cmd == OFF)
    {
      HAL_GPIO_WritePin(GPIOB,LED2_Pin,GPIO_PIN_SET);
    }
  }
}

void LED_Test(void)
{
  LED_control(LED1,ON);
  LED_control(LED2,OFF);
  HAL_Delay(500);
  LED_control(LED1,OFF);
  LED_control(LED2,ON);
  HAL_Delay(500);
}
/* USER CODE END 2 */
