#include "analog_input.hpp"

AnalogInput::AnalogInput(Proxies::AnalogInput &hadc, Proxies::Timeout timeout_ms = 1000)
  : hadc(hadc), timeout_ms(timeout_ms) {}

/**
 * @brief Metodo que inicia a amostragem do ADC e aguarda até que a conversão
 * seja concluída.
 *
 */
void AnalogInput::Sample()
{
  // Inicia o ADC.
  HAL_ADC_Start(&this->hadc);

  // Aguarda até que a conversão do ADC seja concluída ou até que o tempo
  // limite (timeout_ms) expire.
  HAL_ADC_PollForConversion(&this->hadc, this->timeout_ms);
}

/**
 * @brief Metodo que retorna o valor convertido do ADC.
 *
 */
Proxies::ADCValue AnalogInput::Get()
{
  // Obtém o valor convertido do ADC e o retorna.
  return HAL_ADC_GetValue(&this->hadc);
}

AnalogInput::~AnalogInput() {}
