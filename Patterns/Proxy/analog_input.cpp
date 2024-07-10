#include "analog_input.hpp"

#include "core.h"

AnalogInput::AnalogInput(ADC_HandleTypeDef *hadc, std::uint32_t timeout) : hadc(hadc), timeout(timeout)
{
}

void AnalogInput::Sample()
{
    HAL_ADC_Start(this->hadc);
    HAL_ADC_PollForConversion(this->hadc, this->timeout);
}

std::uint32_t AnalogInput::Get()
{
    return HAL_ADC_GetValue(this->hadc);
}

AnalogInput::~AnalogInput()
{
}
