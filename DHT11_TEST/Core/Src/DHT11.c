#include "dht11.h"
#include <stdio.h>

// 微秒级延时函数
static void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0); // 定时器计数器清零
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

// 等待引脚变为期望电平，带超时（微秒），返回1表示成功，0表示超时
static uint8_t wait_for_level(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState level, uint32_t timeout_us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while ((__HAL_TIM_GET_COUNTER(&htim2) < timeout_us) && (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != level))
    {
        // 空循环等待
    }
    return (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == level) ? 1 : 0;
}

// 设置引脚为输出模式
static void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// 设置引脚为输入模式
static void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉输入
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// 发送起始信号并检查 DHT11 的响应
static uint8_t DHT11_Start(void)
{
    uint8_t response = 0;
    Set_Pin_Output(DHT11_PORT, DHT11_PIN); // 设置为输出

    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET); // 拉低
    HAL_Delay(20);                                            // 延时 > 18ms

    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET); // 拉高
    delay_us(30);                                           // 延时 30us

    Set_Pin_Input(DHT11_PORT, DHT11_PIN); // 设置为输入

    // 等待 DHT11 的响应
    // DHT11 会先拉低约80us，然后拉高约80us
    // 等待总线上变为低电平（响应开始），超时返回
    if (!wait_for_level(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET, 100))
        return 0;

    // 等待 DHT11 拉低结束（等待变高），超时返回
    if (!wait_for_level(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET, 150))
        return 0;

    // 响应正确
    response = 1;
    return response;
}

// 从 DHT11 读取一个字节
static uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, result = 0;
    for (i = 0; i < 8; i++)
    {
        // 等待数据位的起始低电平（约50us），超时保护
        if (!wait_for_level(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET, 80))
            return 0; // 超时

        // 等待高电平开始（位的高电平），超时保护
        if (!wait_for_level(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET, 80))
            return 0; // 超时

        // 高电平开始后延时大约40us再采样，高电平长代表1，短代表0
        delay_us(40);
        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET)
        {
            result |= (1 << (7 - i));
            // 等待高电平结束再进入下一位
            if (!wait_for_level(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET, 100))
                return 0;
        }
        else
        {
            result &= ~(1 << (7 - i));
        }
    }
    return result;
}

// 公开的读取函数
uint8_t DHT11_ReadData(DHT11_Data *data)
{
    uint8_t rawData[5] = {0};

    if (DHT11_Start())
    {
        for (int i = 0; i < 5; i++)
        {
            rawData[i] = DHT11_Read_Byte();
        }

        // 校验和检查
        uint8_t checksum = rawData[0] + rawData[1] + rawData[2] + rawData[3];
        if (checksum == rawData[4])
        {
            data->humidity = (float)rawData[0] + ((float)rawData[1] / 10.0f);
            data->temperature = (float)rawData[2] + ((float)rawData[3] / 10.0f);
            return 1; // 成功
        }
    }
    return 0; // 失败
}
