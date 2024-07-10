#include "led.hpp"
#include "digital_output.hpp"

#include "core.h"

struct LedAdapterMap
{
	GPIO_TypeDef *port;
	uint16_t pin;
};

LedAdapterMap const led_map[] =
{
	[LedType::LD4] = {.port = GPIOD, .pin = GPIO_PIN_12}, /* LD 4 */
	[LedType::LD5] = {.port = GPIOD, .pin = GPIO_PIN_14}, /* LD 5 */
	[LedType::LD6] = {.port = GPIOD, .pin = GPIO_PIN_15}, /* LD 6 */
};

LedAdapter::LedAdapter(LedType::Value led)
{
	this->adaptee_ = new DigitalOutput(led_map[led].port, led_map[led].pin);
	this->Reset();
};

LedAdapter::LedAdapter(LedType::Value led, LedState::Value initial_value)
{
	this->adaptee_ = new DigitalOutput(led_map[led].port, led_map[led].pin);

	if (initial_value == LedState::Setted)
	{
		this->Set();
	}
	else
	{
		this->Reset();
	}
};

LedAdapter::~LedAdapter()
{
	delete this->adaptee_;
};
