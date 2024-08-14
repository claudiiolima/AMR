#include "lamp.hpp"

LampAdapter::LampAdapter(Proxies::AnalogOutputObj &dac, Proxies::AnalogChannel channel, Adapters::LampPercentage initial_value)
{
  // Cria um novo objeto AnalogOutput.
  this->adaptee_ = new AnalogOutput(dac, channel);
  // Define o valor do objeto AnalogOutput para o valor inicial especificado.
  this->adaptee_->Set(initial_value);
};

LampAdapter::~LampAdapter() 
{
  // Deleta o objeto AnalogOutput alocado dinamicamente.
  delete this->adaptee_;
};
