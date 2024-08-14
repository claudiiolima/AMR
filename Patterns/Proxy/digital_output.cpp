#include "digital_output.hpp"

DigitalOutput::DigitalOutput(const Proxies::DigitalOutputConfig &config, Proxies::DigitalState initial_value) : port(*config.port), pin(config.pin)
{
  // Escreve o estado inicial do pino digital.
  this->Write(initial_value);
}

/**
 * @brief Escreve o estado do pino digital.
 * 
 * @param[in] state 
 */
void DigitalOutput::Write(Proxies::DigitalState state) 
{   
  // Verifica o estado desejado.
  if (state == Proxies::DigitalState::High) 
  {
    // Define o pino como SET.
    HAL_GPIO_WritePin(&this->port, this->pin, GPIO_PIN_SET);
  }
  else 
  {
    // Define o pino como RESET.
    HAL_GPIO_WritePin(&this->port, this->pin, GPIO_PIN_RESET);
  }
}

/**
 * @brief Le o estado atual do pino digital.
 * 
 * @return Proxies::DigitalState 
 */
Proxies::DigitalState DigitalOutput::Read() 
{
  // Lê o estado do pino GPIO especificado.
  GPIO_PinState const pin_state = HAL_GPIO_ReadPin(&this->port, this->pin);
  // Inicializa a variável de estado digital como Low.
  Proxies::DigitalState digital_output_state = Proxies::DigitalState::Low;

  // Verifica se o estado do pino é SET.
  if (pin_state == GPIO_PIN_SET) 
  {
    // Define o estado digital para High.
    digital_output_state = Proxies::DigitalState::High;
  }

  // Retorna o estado digital.
  return digital_output_state;
}

/**
 * @brief Alterna o estado atual do pino digital.
 * 
 */
void DigitalOutput::Toggle() 
{
  // Verifica o estado atual.
  if (this->Read() == Proxies::DigitalState::High) 
  {
    // Se estiver High, muda para Low.
    this->Write(Proxies::DigitalState::Low);
  }
  else
  {
    // Se estiver Low, muda para High.
    this->Write(Proxies::DigitalState::High);
  }
}

DigitalOutput::~DigitalOutput() {}
