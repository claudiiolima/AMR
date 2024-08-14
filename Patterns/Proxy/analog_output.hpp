#ifndef ANALOG_OUTPUT_HPP__
#define ANALOG_OUTPUT_HPP__

#include <cstdint>

#include "proxies.hpp"

// Define o valor máximo para a saída analógica do DAC.
constexpr Proxies::DACValue ANALOG_OUTPUT_MAX_VALUE = 4095u;

class AnalogOutput 
{
public:
  AnalogOutput(Proxies::AnalogOutput& hdac, Proxies::AnalogChannel channel);
  void Set(Proxies::DACValue value);
  Proxies::DACValue Get();
  ~AnalogOutput();

private:
  Proxies::AnalogOutput& hdac;    // Ponteiro para a estrutura de controle do DAC.
  Proxies::AnalogChannel channel; // Canal do DAC a ser usado.
  Proxies::DACValue value;        // Armazena o valor atual de saída do DAC.
};

#endif // ANALOG_OUTPUT_HPP__
