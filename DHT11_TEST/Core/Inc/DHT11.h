  #ifndef INC_DHT11_H_
  #define INC_DHT11_H_

  #include "main.h" // 包含你的主头文件，通常是 main.h

  // 定义 DHT11 连接的 GPIO 端口和引脚
  #define DHT11_PORT GPIOA
  #define DHT11_PIN  GPIO_PIN_1

  // 定义使用的定时器句柄 (请确保在 main.c 中定义了 htim2)
  extern TIM_HandleTypeDef htim2;

  typedef struct {
      float temperature;
      float humidity;
  } DHT11_Data;

  /**
   * @brief 从 DHT11 读取温湿度数据
   * @param data 指向 DHT11_Data 结构体的指针，用于存储读取的数据
   * @return 1 表示成功, 0 表示失败 (校验和错误)
   */
  uint8_t DHT11_ReadData(DHT11_Data *data);

  #endif /* INC_DHT11_H_ */
