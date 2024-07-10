#include "digital_output.hpp"

#include "core.h"

DigitalOutput::DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin) : port(port), pin(pin)
{
    this->Write(DOState::Unsetted);
}

DigitalOutput::DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin, DOState::Value initial_value) : port(port), pin(pin)
{
	this->Write(initial_value);
}

void DigitalOutput::Write(DOState::Value state)
{   
    if (state == DOState::Setted)
    {
    	HAL_GPIO_WritePin(this->port, this->pin, GPIO_PIN_SET);
    }
    else
    {
    	HAL_GPIO_WritePin(this->port, this->pin, GPIO_PIN_RESET);
    }
}

DOState::Value DigitalOutput::Read()
{
    GPIO_PinState const pin_state = HAL_GPIO_ReadPin(this->port, this->pin);
    DOState::Value digital_output_state = DOState::Unsetted;

    if (pin_state == GPIO_PIN_SET)
    {
        digital_output_state = DOState::Setted;
    }

    return digital_output_state;
}

void DigitalOutput::Toggle()
{
    if (this->Read() == DOState::Setted)
    {
        this->Write(DOState::Unsetted);
    }
    else
    {
        this->Write(DOState::Setted);
    }
}

DigitalOutput::~DigitalOutput()
{
}
