#include "digital_input.hpp"

DigitalInput::DigitalInput(const Proxies::DigitalInputConfig &config)
  : port(*config.port), pin(config.pin) {}

/**
 * @brief Metodo que lê o estado do pino digital.
 * 
 * @return Proxies::DigitalState 
 */
Proxies::DigitalState DigitalInput::Read()
{
  // Lê o estado do pino GPIO especificado.
  GPIO_PinState const pin_state = HAL_GPIO_ReadPin(static_cast<GPIO_TypeDef*>(&this->port), this->pin);
  // Inicializa a variável de estado digital como Low.
  Proxies::DigitalState digital_input_state = Proxies::DigitalState::Low;

  // Se o pino está SET, atualiza o estado digital para High.
  if (pin_state == GPIO_PIN_SET) 
  {
    digital_input_state = Proxies::DigitalState::High;
  }

  // Retorna o estado digital.
  return digital_input_state;
}

DigitalInput::~DigitalInput() {}
