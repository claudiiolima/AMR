#include "digital_input.hpp"

#include "core.h"

DigitalInput::DigitalInput(GPIO_TypeDef *port, std::uint16_t pin) : port(port), pin(pin) {}

DIState::Value DigitalInput::Read()
{
    GPIO_PinState const pin_state = HAL_GPIO_ReadPin(this->port, this->pin);
    DIState::Value digital_input_state = DIState::Unsetted;

    if (pin_state == GPIO_PIN_SET)
    {
        digital_input_state = DIState::Setted;
    }

    return digital_input_state;
}

DigitalInput::~DigitalInput()
{
}
