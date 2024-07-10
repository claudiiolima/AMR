#ifndef ANALOG_OUTPUT_HPP__
#define ANALOG_OUTPUT_HPP__

#include <cstdint>
#include "core.h"

constexpr std::uint32_t ANALOG_OUTPUT_MAX_VALUE = 4095u;

class AnalogOutput
{
public:
    AnalogOutput(DAC_HandleTypeDef *hdac, std::uint32_t channel);
    void Set(std::uint32_t value);
    std::uint32_t Get();
    ~AnalogOutput();

private:
    DAC_HandleTypeDef *hdac;
    std::uint32_t channel;
    std::uint32_t value;
};

#endif // !ANALOG_OUTPUT_HPP__
