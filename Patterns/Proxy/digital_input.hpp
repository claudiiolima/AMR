#ifndef DIGITAL_INPUT_HPP__
#define DIGITAL_INPUT_HPP__

#include <cstdint>

#include "proxies.hpp"

class DigitalInput 
{
public:
  DigitalInput(const Proxies::DigitalInputConfig &config);
  Proxies::DigitalState Read();
  ~DigitalInput();

private:
  Proxies::DigitalInput &port; // Endereço da porta GPIO.
  Proxies::DigitalPin pin;     // Pino da porta GPIO.
};

#endif // DIGITAL_INPUT_HPP__
