#ifndef ANALOG_OUTPUT_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define ANALOG_OUTPUT_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint32_t).
#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

constexpr std::uint32_t ANALOG_OUTPUT_MAX_VALUE = 4095u;  // Define o valor máximo para a saída analógica do DAC.

class AnalogOutput 
// Declaração da classe AnalogOutput.
{
public:
    AnalogOutput(DAC_HandleTypeDef *hdac, std::uint32_t channel);  // Declaração do construtor.
    void Set(std::uint32_t value);  // Declaração da função membro que define o valor de saída do DAC.
    std::uint32_t Get();  // Declaração da função membro que retorna o valor atual de saída do DAC.
    ~AnalogOutput();  // Declaração do destrutor.

private:
    DAC_HandleTypeDef *hdac;  // Ponteiro para a estrutura de controle do DAC.
    std::uint32_t channel;  // Canal do DAC a ser usado.
    std::uint32_t value;  // Armazena o valor atual de saída do DAC.
};

#endif // !ANALOG_OUTPUT_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
