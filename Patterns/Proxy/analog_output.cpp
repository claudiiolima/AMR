#include "analog_output.hpp"

#include <algorithm>
#include "core.h"

AnalogOutput::AnalogOutput(DAC_HandleTypeDef *hdac, std::uint32_t channel) : hdac(hdac), channel(channel)
{
}

void AnalogOutput::Set(std::uint32_t value)
{   
    this->value = std::min(ANALOG_OUTPUT_MAX_VALUE, value);;
    HAL_DAC_SetValue(this->hdac, this->channel, DAC_ALIGN_12B_R, this->value);
}

std::uint32_t AnalogOutput::Get()
{
    return this->value;
}

AnalogOutput::~AnalogOutput()
{
}
