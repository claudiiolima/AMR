#ifndef DIGITAL_OUTPUT_HPP__
#define DIGITAL_OUTPUT_HPP__

#include <cstdint>
#include "core.h"

namespace DOState
{
    enum Value
    {
        Unsetted = 0,
        Setted = 1,
    };
}

class DigitalOutput
{
public:
    DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin);
    DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin, DOState::Value initial_value);
    void Write(DOState::Value state);
    DOState::Value Read();
    void Toggle();
    ~DigitalOutput();

private:
    GPIO_TypeDef *port;
    std::uint16_t pin;
};

#endif // !DIGITAL_OUTPUT_HPP__
