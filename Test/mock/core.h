#ifndef CORE_H__
#define CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t ADC_HandleTypeDef;
typedef uint32_t DAC_HandleTypeDef;
typedef uint32_t GPIO_TypeDef;
typedef uint32_t GPIO_PinState;

#define GPIOA_BASE 0
#define GPIOD_BASE 3

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET   1

#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif