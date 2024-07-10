#ifndef LAMP_HPP__
#define LAMP_HPP__

#include <cstdint>
#include "analog_output.hpp"

#include "core.h"

typedef DAC_HandleTypeDef LampAdapterMap;

class Lamp
{
public:
	virtual void Set(float value) = 0;
	virtual ~Lamp() = default;
};

class LampAdapter : public Lamp
{
public:
	LampAdapter(LampAdapterMap *dac, std::uint32_t channel);
	LampAdapter(LampAdapterMap *dac, std::uint32_t channel, std::uint32_t initial_value);
	~LampAdapter();

	void Set(float value) override
	{
		this->adaptee_->Set((uint32_t)(value * (float)ANALOG_OUTPUT_MAX_VALUE / 100.0f));
	};

private:
	AnalogOutput *adaptee_;
};

#endif // !LAMP_HPP__
