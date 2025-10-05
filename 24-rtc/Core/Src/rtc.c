/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    rtc.c
 * @brief   This file provides code for the configuration
 *          of the RTC instances.
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
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include <time.h>
#include "OLED.h"

static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef *hrtc);
static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef *hrtc);
static HAL_StatusTypeDef RTC_WriteTimeCounter(RTC_HandleTypeDef *hrtc, uint32_t TimeCounter);
static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef *hrtc);
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

    /* USER CODE BEGIN RTC_Init 0 */

    /* USER CODE END RTC_Init 0 */

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef DateToUpdate = {0};

    /* USER CODE BEGIN RTC_Init 1 */

    /* USER CODE END RTC_Init 1 */

    /** Initialize RTC Only
     */
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN Check_RTC_BKUP */
    if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x5051)
    {
        /* USER CODE END Check_RTC_BKUP */

        /** Initialize RTC and set the Time and Date
         */
        sTime.Hours = 0x19;
        sTime.Minutes = 0x3;
        sTime.Seconds = 0x0;

        if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
        {
            Error_Handler();
        }
        DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
        DateToUpdate.Month = RTC_MONTH_JANUARY;
        DateToUpdate.Date = 0x2;
        DateToUpdate.Year = 0x24;

        if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
        {
            Error_Handler();
        }

        /* USER CODE BEGIN RTC_Init 2 */
        struct tm rtc_tm;
        rtc_tm.tm_year = 2025 - 1900;
        rtc_tm.tm_mon = 8 - 1;
        rtc_tm.tm_mday = 8;
        rtc_tm.tm_hour = 20;
        rtc_tm.tm_min = 16;
        rtc_tm.tm_sec = 20;
        RTC_WriteTimeCounter(&hrtc, mktime(&rtc_tm));
        /* USER CODE BEGIN RTC_Init 2 */
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5051); // 设置标志位, 表示时间已经被设置
    }
    /* USER CODE END RTC_Init 2 */
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *rtcHandle)
{

    if (rtcHandle->Instance == RTC)
    {
        /* USER CODE BEGIN RTC_MspInit 0 */

        /* USER CODE END RTC_MspInit 0 */
        HAL_PWR_EnableBkUpAccess();
        /* Enable BKP CLK enable for backup registers */
        __HAL_RCC_BKP_CLK_ENABLE();
        /* RTC clock enable */
        __HAL_RCC_RTC_ENABLE();
        /* USER CODE BEGIN RTC_MspInit 1 */

        /* USER CODE END RTC_MspInit 1 */
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle)
{

    if (rtcHandle->Instance == RTC)
    {
        /* USER CODE BEGIN RTC_MspDeInit 0 */

        /* USER CODE END RTC_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_RTC_DISABLE();
        /* USER CODE BEGIN RTC_MspDeInit 1 */

        /* USER CODE END RTC_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
void RTC_Test(void)
{
    struct tm *tp;
    time_t t = RTC_ReadTimeCounter(&hrtc);
    tp = localtime(&t);
    printf("%u:%d-%d-%d %d:%d:%d\n", t, tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
           tp->tm_hour, tp->tm_min, tp->tm_sec);
    HAL_Delay(1000);
}

static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef *hrtc)
{
    uint32_t tickstart = 0U;

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    tickstart = HAL_GetTick();
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef *hrtc)
{
    uint32_t tickstart = 0U;

    tickstart = HAL_GetTick();
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if ((HAL_GetTick() - tickstart) > RTC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

    return HAL_OK;
}

/**
 * @brief  Write the time counter in RTC_CNT registers.
 * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
 *                the configuration information for RTC.
 * @param  TimeCounter: Counter to write in RTC_CNT registers
 * @retval HAL status
 */
static HAL_StatusTypeDef RTC_WriteTimeCounter(RTC_HandleTypeDef *hrtc, uint32_t TimeCounter)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Set Initialization mode */
    if (RTC_EnterInitMode(hrtc) != HAL_OK)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set RTC COUNTER MSB word */
        WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16U));
        /* Set RTC COUNTER LSB word */
        WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));

        /* Wait for synchro */
        if (RTC_ExitInitMode(hrtc) != HAL_OK)
        {
            status = HAL_ERROR;
        }
    }

    return status;
}

/**
 * @brief  Read the time counter available in RTC_CNT registers.
 * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
 *                the configuration information for RTC.
 * @retval Time counter
 */
static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef *hrtc)
{
    uint16_t high1 = 0U, high2 = 0U, low = 0U;
    uint32_t timecounter = 0U;

    high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
    low = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
    high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);

    if (high1 != high2)
    {
        /* In this case the counter roll over during reading of CNTL and CNTH registers,
           read again CNTL register then return the counter value */
        timecounter = (((uint32_t)high2 << 16U) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
    }
    else
    {
        /* No counter roll over during reading of CNTL and CNTH registers, counter
           value is equal to first value of CNTL and CNTH */
        timecounter = (((uint32_t)high1 << 16U) | low);
    }

    return timecounter;
}

/* USER CODE END 1 */
