#include "sensor.hpp"  // Inclui o cabeçalho para a classe Sensor e SensorAdapter, que contém a definição da classe e suas declarações de função.
#include "analog_input.hpp"  // Inclui o cabeçalho para a classe AnalogInput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

SensorAdapter::SensorAdapter(SensorAdapterMap *adc, std::uint32_t timeout) 
// Construtor da classe SensorAdapter que inicializa um objeto AnalogInput.
{
    this->adaptee_ = new AnalogInput(adc, timeout);  // Cria um novo objeto AnalogInput.
};

SensorAdapter::~SensorAdapter() 
// Destrutor da classe SensorAdapter que deleta o objeto AnalogInput.
{
    delete this->adaptee_;  // Deleta o objeto AnalogInput alocado dinamicamente.
};
