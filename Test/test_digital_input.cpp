#include <limits.h>
#include "gtest/gtest.h"
#include "digital_input.hpp"

#include "mock_core.h"

namespace
{

TEST(DigitalInputTest, Read)
{
    Proxies::DigitalInputConfig config = {.port = static_cast<GPIO_TypeDef*>(GPIOA_BASE), .pin = GPIO_PIN_0};

    DigitalInput di(config);

    HAL_GPIO_ReadPin_Return(static_cast<GPIO_TypeDef*>(GPIOA_BASE), GPIO_PIN_0, 0);
    EXPECT_EQ(Proxies::DigitalState::Low, di.Read());

    HAL_GPIO_ReadPin_Return(static_cast<GPIO_TypeDef*>(GPIOA_BASE), GPIO_PIN_0, 1);
    EXPECT_EQ(Proxies::DigitalState::High, di.Read());
}

}