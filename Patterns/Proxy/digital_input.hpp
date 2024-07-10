#ifndef DIGITAL_INPUT_HPP__
#define DIGITAL_INPUT_HPP__

#include <cstdint>
#include "core.h"

namespace DIState
{
    enum Value
    {
        Unsetted = 0,
        Setted = 1,
    };
}

class DigitalInput
{
public:
    DigitalInput(GPIO_TypeDef *port, std::uint16_t pin);
    DIState::Value Read();
    ~DigitalInput();

private:
    GPIO_TypeDef *port;
    std::uint16_t pin;
};

#endif // !DIGITAL_INPUT_HPP__
