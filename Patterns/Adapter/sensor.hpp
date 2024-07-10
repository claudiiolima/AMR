#ifndef SENSOR_HPP__
#define SENSOR_HPP__

#include <cstdint>
#include "analog_input.hpp"

#include "core.h"

typedef ADC_HandleTypeDef SensorAdapterMap;

class Sensor
{
public:
	virtual void Sample() = 0;
	virtual std::uint32_t GetRaw() = 0;
	virtual ~Sensor() = default;
};

class SensorAdapter : public Sensor
{
public:
	SensorAdapter(SensorAdapterMap *adc, std::uint32_t timeout);
	~SensorAdapter();

	void Sample() override
	{
		this->adaptee_->Sample();
		this->raw = this->adaptee_->Get();
	};

	std::uint32_t GetRaw() override
	{
		return this->raw;
	};

private:
	AnalogInput *adaptee_;
	std::uint32_t raw;
};

#endif // !SENSOR_HPP__
