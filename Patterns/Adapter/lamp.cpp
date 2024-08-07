#include "lamp.hpp"  // Inclui o cabeçalho para a classe Lamp e LampAdapter, que contém a definição da classe e suas declarações de função.
#include "analog_output.hpp"  // Inclui o cabeçalho para a classe AnalogOutput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

LampAdapter::LampAdapter(LampAdapterMap *dac, std::uint32_t channel) 
// Construtor da classe LampAdapter que inicializa um objeto AnalogOutput com o valor inicial zero.
{
    this->adaptee_ = new AnalogOutput(dac, channel);  // Cria um novo objeto AnalogOutput.
    this->adaptee_->Set(0u);  // Define o valor do objeto AnalogOutput para zero.
};

LampAdapter::LampAdapter(LampAdapterMap *dac, std::uint32_t channel, std::uint32_t initial_value) 
// Sobrecarga do construtor que permite inicializar um objeto AnalogOutput com um valor inicial especificado.
{
    this->adaptee_ = new AnalogOutput(dac, channel);  // Cria um novo objeto AnalogOutput.
    this->adaptee_->Set(initial_value);  // Define o valor do objeto AnalogOutput para o valor inicial especificado.
};

LampAdapter::~LampAdapter() 
// Destrutor da classe LampAdapter que deleta o objeto AnalogOutput.
{
    delete this->adaptee_;  // Deleta o objeto AnalogOutput alocado dinamicamente.
};
