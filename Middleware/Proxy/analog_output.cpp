#include "analog_output.hpp"

#include <algorithm>

AnalogOutput::AnalogOutput(Proxies::AnalogOutputObj& hdac, Proxies::AnalogChannel channel)
  : hdac(hdac), channel(channel) {}

/**
 * @brief Metodo que define o valor de saída do DAC.
 * 
 * @param[in] value Valor da saida analogica. [0, ANALOG_OUTPUT_MAX_VALUE]
 */
void AnalogOutput::Set(Proxies::DACValue value) 
{
  // Garante que o valor não exceda o máximo permitido.
  this->value = std::min(ANALOG_OUTPUT_MAX_VALUE, value);

  // Define o valor do DAC no canal especificado.
  HAL_DAC_SetValue(&this->hdac, this->channel, DAC_ALIGN_12B_R, this->value);
}

/**
 * @brief Metodo que retorna o valor atual de saída do DAC.
 * 
 * @return Valor atual de saída do DAC.
 */
Proxies::DACValue AnalogOutput::Get() 
{
  // Retorna o valor armazenado.
  return this->value;
}

AnalogOutput::~AnalogOutput() 
{
}
