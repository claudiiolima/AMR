#ifndef ANALOG_INPUT_HPP__
#define ANALOG_INPUT_HPP__

#include <cstdint>
#include "core.h"

class AnalogInput
{
public:
    AnalogInput(ADC_HandleTypeDef *hadc, std::uint32_t timeout);
    void Sample();
    std::uint32_t Get();
    ~AnalogInput();

private:
    ADC_HandleTypeDef *hadc;
    std::uint32_t timeout;
    std::uint32_t value;
};

#endif // !ANALOG_INPUT_HPP__
