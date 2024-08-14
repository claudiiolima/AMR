#ifdef __cplusplus
extern "C" {
#endif

#include "mock.h"
#include "core.h"

static GPIO_PinState retval;

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return retval;
}

void HAL_GPIO_ReadPin_Return(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState state)
{
    retval = state;
}

#ifdef __cplusplus
}
#endif