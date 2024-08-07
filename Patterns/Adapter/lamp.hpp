#ifndef LAMP_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define LAMP_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint32_t).
#include "analog_output.hpp"  // Inclui o cabeçalho para a classe AnalogOutput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

typedef DAC_HandleTypeDef LampAdapterMap;  
// Define um alias para DAC_HandleTypeDef como LampAdapterMap.

class Lamp 
// Declaração da classe abstrata Lamp.
{
public:
    virtual void Set(float value) = 0;  // Declaração da função virtual pura para definir o valor da lâmpada.
    virtual ~Lamp() = default;  // Declaração do destrutor virtual.
};

class LampAdapter : public Lamp 
// Declaração da classe LampAdapter que herda da classe Lamp.
{
public:
    LampAdapter(LampAdapterMap *dac, std::uint32_t channel);  // Declaração do construtor.
    LampAdapter(LampAdapterMap *dac, std::uint32_t channel, std::uint32_t initial_value);  // Declaração da sobrecarga do construtor.
    ~LampAdapter();  // Declaração do destrutor.

    void Set(float value) override 
    // Função membro que define o valor da lâmpada, implementada da classe base Lamp.
    {
        this->adaptee_->Set((uint32_t)(value * (float)ANALOG_OUTPUT_MAX_VALUE / 100.0f));  
        // Converte o valor de porcentagem para o valor correspondente no range do DAC e define o valor no objeto AnalogOutput.
    };

private:
    AnalogOutput *adaptee_;  // Ponteiro para o objeto AnalogOutput.
};

#endif // !LAMP_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
