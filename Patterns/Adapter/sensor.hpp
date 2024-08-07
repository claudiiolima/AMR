#ifndef SENSOR_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define SENSOR_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint32_t).
#include "analog_input.hpp"  // Inclui o cabeçalho para a classe AnalogInput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

typedef ADC_HandleTypeDef SensorAdapterMap;  
// Define um alias para ADC_HandleTypeDef como SensorAdapterMap.

class Sensor 
// Declaração da classe abstrata Sensor.
{
public:
    virtual void Sample() = 0;  // Declaração da função virtual pura para amostrar o sensor.
    virtual std::uint32_t GetRaw() = 0;  // Declaração da função virtual pura para obter o valor bruto do sensor.
    virtual ~Sensor() = default;  // Declaração do destrutor virtual.
};

class SensorAdapter : public Sensor 
// Declaração da classe SensorAdapter que herda da classe Sensor.
{
public:
    SensorAdapter(SensorAdapterMap *adc, std::uint32_t timeout);  // Declaração do construtor.
    ~SensorAdapter();  // Declaração do destrutor.

    void Sample() override 
    // Função membro que amostra o sensor, implementada da classe base Sensor.
    {
        this->adaptee_->Sample();  // Chama a função Sample do objeto AnalogInput.
        this->raw = this->adaptee_->Get();  // Obtém o valor do objeto AnalogInput e armazena na variável raw.
    }

    std::uint32_t GetRaw() override 
    // Função membro que retorna o valor bruto do sensor, implementada da classe base Sensor.
    {
        return this->raw;  // Retorna o valor armazenado na variável raw.
    }

private:
    AnalogInput *adaptee_;  // Ponteiro para o objeto AnalogInput.
    std::uint32_t raw;  // Variável para armazenar o valor bruto do sensor.
};

#endif // !SENSOR_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
