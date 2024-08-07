
#ifndef ANALOG_INPUT_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define ANALOG_INPUT_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint32_t).
#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

class AnalogInput 
// Declaração da classe AnalogInput.
{
public:
    AnalogInput(ADC_HandleTypeDef *hadc, std::uint32_t timeout);  // Declaração do construtor.
    void Sample();  // Declaração da função membro que inicia a amostragem do ADC.
    std::uint32_t Get();  // Declaração da função membro que retorna o valor convertido do ADC.
    ~AnalogInput();  // Declaração do destrutor.

private:
    ADC_HandleTypeDef *hadc;  // Ponteiro para a estrutura de controle do ADC.
    std::uint32_t timeout;  // Tempo limite para a operação de conversão do ADC.
    std::uint32_t value;  // Armazena o valor convertido do ADC.
};

#endif // !ANALOG_INPUT_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
