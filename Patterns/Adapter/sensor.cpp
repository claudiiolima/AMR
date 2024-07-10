#include "sensor.hpp"
#include "analog_input.hpp"

#include "core.h"

SensorAdapter::SensorAdapter(SensorAdapterMap *adc, std::uint32_t timeout)
{
	this->adaptee_ = new AnalogInput(adc, timeout);
};

SensorAdapter::~SensorAdapter()
{
	delete this->adaptee_;
};
