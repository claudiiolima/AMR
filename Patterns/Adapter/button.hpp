#ifndef BUTTON_HPP__
#define BUTTON_HPP__

#include <cstdint>
#include "digital_input.hpp"

#include "core.h"

const std::uint32_t BUTTON_DEBOUNCE_TICKS = 40u;

namespace ButtonState
{
    enum Value
    {
        Unsetted = 0,
        Setted = 1,
    };
}

namespace ButtonType
{
    enum Value
    {
        BUTTON_BLUE,
    };
}

class Button
{
public:
	virtual void Sample() = 0;
	virtual bool GetState() = 0;
	virtual ~Button() = default;
};

class ButtonAdapter : public Button
{
public:
	ButtonAdapter(ButtonType::Value button);
	~ButtonAdapter();

	void Sample() override
	{
		this->aux_sample     = this->current_sample;
		this->current_sample = (this->adaptee_->Read() == DIState::Setted) ? true : false;

		if (this->current_sample == this->old_sample)
		{
			if (this->tick >= BUTTON_DEBOUNCE_TICKS)
			{
				this->state = this->current_sample;
			}
			else
			{
				this->tick++;
			}
		}
		else
		{
			if (this->tick > 0u)
			{
				this->tick--;
			}
		}
		this->old_sample = this->aux_sample;
	};

	bool GetState() override
	{
		return this->state;
	};

private:
	DigitalInput *adaptee_;
	std::uint32_t tick;
	bool aux_sample;
	bool current_sample;
	bool old_sample;
	bool state;
};

#endif // !BUTTON_HPP__
