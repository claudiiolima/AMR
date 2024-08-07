#include "analog_input.hpp"  // Inclui o cabeçalho para a classe AnalogInput, que contém a definição da classe e suas declarações de função.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

AnalogInput::AnalogInput(ADC_HandleTypeDef *hadc, std::uint32_t timeout) : hadc(hadc), timeout(timeout) 
// Construtor da classe AnalogInput que inicializa os membros da classe `hadc` e `timeout` com os valores passados como parâmetros.
{
}

void AnalogInput::Sample() 
// Função membro que inicia a amostragem do ADC e aguarda até que a conversão seja concluída.
{
    HAL_ADC_Start(this->hadc);  // Inicia o ADC.
    HAL_ADC_PollForConversion(this->hadc, this->timeout);  // Aguarda até que a conversão do ADC seja concluída ou até que o tempo limite expire.
}

std::uint32_t AnalogInput::Get() 
// Função membro que retorna o valor convertido do ADC.
{
    return HAL_ADC_GetValue(this->hadc);  // Obtém o valor convertido do ADC e o retorna.
}

AnalogInput::~AnalogInput() 
// Destrutor da classe AnalogInput. Atualmente, não realiza nenhuma ação específica.
{
}
