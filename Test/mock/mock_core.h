#ifndef MOCK_CORE_H__
#define MOCK_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"

void HAL_GPIO_ReadPin_Return(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState state);

#ifdef __cplusplus
}
#endif

#endif