#include "led.hpp"

Proxies::DigitalOutputConfig const led_map[] =
{
  // Mapeia o LED LD4 para a porta GPIOD e o pino 12.
  [Adapters::LedType::LD4] = {Proxies::MappedDigitalOutputs[Proxies::DO_D_12]},
  // Mapeia o LED LD5 para a porta GPIOD e o pino 14.
  [Adapters::LedType::LD5] = {Proxies::MappedDigitalOutputs[Proxies::DO_D_14]},
  // Mapeia o LED LD6 para a porta GPIOD e o pino 15.
  [Adapters::LedType::LD6] = {Proxies::MappedDigitalOutputs[Proxies::DO_D_15]},
};

LedAdapter::LedAdapter(Adapters::LedType led, Adapters::LedState initial_value)
{
  this->adaptee_ = new DigitalOutput(led_map[led]);  // Cria um novo objeto DigitalOutput.

  // Verifica se o valor inicial do LED.
  if (initial_value == Adapters::LedState::On) 
  {
    // Define o estado do LED como "aceso".
    this->Set();
  }
  else 
  {
    // Define o estado do LED como "apagado".
    this->Reset();
  }
};

LedAdapter::~LedAdapter() 
{
  delete this->adaptee_;  // Deleta o objeto DigitalOutput alocado dinamicamente.
};
