#include "button.hpp"
#include "digital_output.hpp"

#include "core.h"

struct ButtonAdapterMap
{
	GPIO_TypeDef *port;
	uint16_t pin;
};

ButtonAdapterMap const button_map[] =
{
	[ButtonType::BUTTON_BLUE] = {.port = GPIOA, .pin = GPIO_PIN_0}, /* LA 0 */
};

ButtonAdapter::ButtonAdapter(ButtonType::Value button)
{
	this->state          = false;
	this->current_sample = false;
	this->old_sample     = false;

	this->adaptee_ = new DigitalInput(button_map[button].port, button_map[button].pin);
};

ButtonAdapter::~ButtonAdapter()
{
	delete this->adaptee_;
};
