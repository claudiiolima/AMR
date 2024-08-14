#include "button.hpp"

Proxies::DigitalInputConfig const button_map[] =
{
  // Mapeia o botão azul para a porta GPIOA e o pino 0.
  [Adapters::ButtonType::BUTTON_BLUE] = {Proxies::MappedDigitalInputs[Proxies::DI_A_0]},
};

ButtonAdapter::ButtonAdapter(Adapters::ButtonType button) 
{
  this->adaptee_   = new DigitalInput(button_map[button]);
  this->debouncer_ = new Debouncer(BUTTON_DEBOUNCE_TICKS);
};

ButtonAdapter::~ButtonAdapter()
{
  // Deleta o objeto DigitalInput alocado dinamicamente.
  delete this->adaptee_;
};
