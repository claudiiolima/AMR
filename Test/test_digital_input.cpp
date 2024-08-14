#include <limits.h>
#include "gtest/gtest.h"
#include "digital_input.hpp"

namespace
{
TEST(DigitalInput, Negative)
{
    Proxies::DigitalInputConfig config = {.port = (Proxies::DigitalInputObj*)0, .pin = 0};

    DigitalInput di(config);
}

}