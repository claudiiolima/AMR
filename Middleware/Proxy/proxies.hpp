#ifndef PROXIES_HPP__
#define PROXIES_HPP__

#include <cstdint>

#include "core.h"

namespace Proxies
{

typedef ADC_HandleTypeDef AnalogInputObj;
typedef DAC_HandleTypeDef AnalogOutputObj;
typedef GPIO_TypeDef DigitalInputObj;
typedef GPIO_TypeDef DigitalOutputObj;

typedef std::uint32_t Timeout;
typedef std::uint16_t DigitalPin;
typedef std::uint16_t AnalogChannel;
typedef std::uint32_t ADCValue;
typedef std::uint32_t DACValue;
enum DigitalState
{
  Low  = 0,
  High = 1,
};

struct DigitalInputConfig
{
  DigitalInputObj* port; // Objeto GPIO.
  DigitalPin pin;     // Pino da porta GPIO.
};

struct DigitalOutputConfig
{
  DigitalOutputObj* port; // Objeto GPIO.
  DigitalPin pin;      // Pino da porta GPIO.
};

enum DIMap
{
  DI_A_0,
  DI_NUMBER_OF_MAPS,
};

enum DOMap
{
  DO_D_12,
  DO_D_14,
  DO_D_15,
  DO_NUMBER_OF_MAPS,
};

const DigitalInputConfig MappedDigitalInputs[DI_NUMBER_OF_MAPS] =
{
  [DI_A_0] = {.port = (DigitalInputObj*)GPIOA_BASE, .pin = GPIO_PIN_0},
};

const DigitalOutputConfig MappedDigitalOutputs[DO_NUMBER_OF_MAPS] =
{
  [DO_D_12] = {.port = (DigitalOutputObj*)GPIOD_BASE, .pin = GPIO_PIN_12},
  [DO_D_14] = {.port = (DigitalOutputObj*)GPIOD_BASE, .pin = GPIO_PIN_14},
  [DO_D_15] = {.port = (DigitalOutputObj*)GPIOD_BASE, .pin = GPIO_PIN_15},
};

}

#endif // PROXIES_HPP__
