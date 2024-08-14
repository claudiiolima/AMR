#ifndef ADAPTERS_HPP__
#define ADAPTERS_HPP__

#include <cstdint>

namespace Adapters
{

typedef float LampPercentage;
typedef std::uint32_t SensorRaw;

// Enumeração para representar os tipos possíveis de botão.
enum ButtonType 
{
  BUTTON_BLUE, // Tipo de botão azul.
};
// Enumeração para representar os tipos possíveis de LED.
enum LedType
{
  LD4, // Tipo de LED LD4.
  LD5, // Tipo de LED LD5.
  LD6, // Tipo de LED LD6.
};
// Enumeração para representar os estados possíveis do LED.
enum LedState
{
  Off = 0, // Estado "apagado".
  On  = 1, // Estado "aceso".
};

}

#endif // ADAPTERS_HPP__
