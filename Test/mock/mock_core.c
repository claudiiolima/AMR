#ifdef __cplusplus
extern "C" {
#endif

#include "mock_core.h"
#include "core.h"

static GPIO_PinState retval;
static GPIO_TypeDef* GPIOx_expected;
static uint16_t GPIO_Pin_expected;

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return retval;
}

void HAL_GPIO_ReadPin_Return(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState state)
{
    GPIOx_expected = GPIOx;
    GPIO_Pin_expected = GPIO_Pin;
    retval = state;
}

#ifdef __cplusplus
}
#endif