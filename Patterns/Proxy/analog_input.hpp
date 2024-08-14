
#ifndef ANALOG_INPUT_HPP__
#define ANALOG_INPUT_HPP__

#include <cstdint>

#include "proxies.hpp"

class AnalogInput {
public:
  AnalogInput(Proxies::AnalogInput &hadc, Proxies::Timeout timeout_ms);
  void Sample();
  Proxies::ADCValue Get();
  ~AnalogInput();

private:
  Proxies::AnalogInput &hadc; // Ponteiro para a estrutura de controle do ADC.
  Proxies::Timeout timeout_ms; // Tempo limite para a operação de conversão do ADC.
  Proxies::ADCValue value;    // Armazena o valor convertido do ADC.
};

#endif // ANALOG_INPUT_HPP__
