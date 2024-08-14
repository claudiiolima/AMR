#ifndef DIGITAL_OUTPUT_HPP__
#define DIGITAL_OUTPUT_HPP__

#include <cstdint>

#include "proxies.hpp"

class DigitalOutput 
{
public:
    DigitalOutput(const Proxies::DigitalOutputConfig &config, Proxies::DigitalState initial_value = Proxies::DigitalState::Low);
    void Write(Proxies::DigitalState state);
    Proxies::DigitalState Read();
    void Toggle();
    ~DigitalOutput();

private:
    Proxies::DigitalOutputObj &port; // Endereço da porta GPIO.
    Proxies::DigitalPin pin;      // Pino da porta GPIO.
};

#endif // DIGITAL_OUTPUT_HPP__
