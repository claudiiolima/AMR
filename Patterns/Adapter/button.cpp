#include "button.hpp"

Proxies::DigitalInputConfig const button_map[] =
{
  // Mapeia o botão azul para a porta GPIOA e o pino 0.
  [Adapters::ButtonType::BUTTON_BLUE] = {Proxies::MappedDigitalInputs[Proxies::DI_A_0]},
};

ButtonAdapter::ButtonAdapter(Adapters::ButtonType button) 
{
  this->state          = false;  // Inicializa o estado do botão como false.
  this->current_sample = false;  // Inicializa a amostra atual como false.
  this->old_sample     = false;  // Inicializa a amostra antiga como false.

  // Cria um novo objeto DigitalInput usando a porta e o pino mapeados para o botão especificado.
  // Proxies::DigitalInputConfig config(button_map[button].port, button_map[button].pin);
  this->adaptee_ = new DigitalInput(button_map[button]);
};

ButtonAdapter::~ButtonAdapter()
{
  // Deleta o objeto DigitalInput alocado dinamicamente.
  delete this->adaptee_;
};
