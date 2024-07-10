#ifndef LED_HPP__
#define LED_HPP__

#include <cstdint>
#include "digital_output.hpp"

#include "core.h"

namespace LedState
{
    enum Value
    {
        Unsetted = 0,
        Setted = 1,
    };
}

namespace LedType
{
    enum Value
    {
        LD4,
        LD5,
        LD6,
    };
}

class Led
{
public:
	virtual void Set() = 0;
	virtual void Reset() = 0;
	virtual LedState::Value GetState() = 0;
	virtual void Toggle() = 0;
	virtual ~Led() = default;
};

class LedAdapter : public Led
{
public:
	LedAdapter(LedType::Value led);
	LedAdapter(LedType::Value led, LedState::Value initial_value);
	~LedAdapter();

	void Set() override
	{
		this->adaptee_->Write(DOState::Setted);
	};

	void Reset() override
	{
		this->adaptee_->Write(DOState::Unsetted);
	};

	LedState::Value GetState() override
	{
		DOState::Value const do_state = this->adaptee_->Read();
		LedState::Value led_state = LedState::Unsetted;

		if (do_state == DOState::Setted)
		{
			led_state = LedState::Setted;
		}

		return led_state;
	};

	void Toggle() override
	{
		if (this->GetState() == LedState::Setted)
		{
			this->Reset();
		}
		else
		{
			this->Set();
		}
	};

private:
	DigitalOutput *adaptee_;
};

#endif // !LED_HPP__
