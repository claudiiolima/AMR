#include "lamp.hpp"
#include "analog_output.hpp"

#include "core.h"

LampAdapter::LampAdapter(LampAdapterMap *dac, std::uint32_t channel)
{
	this->adaptee_ = new AnalogOutput(dac, channel);
	this->adaptee_->Set(0u);
};

LampAdapter::LampAdapter(LampAdapterMap *dac, std::uint32_t channel, std::uint32_t initial_value)
{
	this->adaptee_ = new AnalogOutput(dac, channel);
	this->adaptee_->Set(initial_value);
};

LampAdapter::~LampAdapter()
{
	delete this->adaptee_;
};
