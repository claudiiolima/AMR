#include "analog_output.hpp"  // Inclui o cabeçalho para a classe AnalogOutput, que contém a definição da classe e suas declarações de função.

#include <algorithm>  // Inclui a biblioteca de algoritmos padrão do C++, usada aqui para a função std::min.
#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

AnalogOutput::AnalogOutput(DAC_HandleTypeDef *hdac, std::uint32_t channel) : hdac(hdac), channel(channel)
// Construtor da classe AnalogOutput que inicializa os membros da classe `hdac` e `channel` com os valores passados como parâmetros.
{
}

void AnalogOutput::Set(std::uint32_t value) 
// Função membro que define o valor de saída do DAC.
{   
    this->value = std::min(ANALOG_OUTPUT_MAX_VALUE, value);  // Garante que o valor não exceda o máximo permitido.
    HAL_DAC_SetValue(this->hdac, this->channel, DAC_ALIGN_12B_R, this->value);  // Define o valor do DAC no canal especificado.
}

std::uint32_t AnalogOutput::Get() 
// Função membro que retorna o valor atual de saída do DAC.
{
    return this->value;  // Retorna o valor armazenado.
}

AnalogOutput::~AnalogOutput() 
// Destrutor da classe AnalogOutput. Atualmente, não realiza nenhuma ação específica.
{
}
