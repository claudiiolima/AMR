
#include "core.h"

struct AnalogInputConfig {

    ADC_HandleTypeDef *hadc;
    std::uint32_t timeout;

    // Construtor para inicializar a struct
    AnalogInputConfig(ADC_HandleTypeDef *hadc, std::uint32_t timeout)
        : hadc(hadc), timeout(timeout) {}
};


struct DigitalInputConfig
{
    GPIO_TypeDef *port;  // Ponteiro para a estrutura do porto GPIO.
    std::uint16_t pin;    // Número do pino do porto GPIO.

    // Construtor para inicializar a struct
    DigitalInputConfig(GPIO_TypeDef *port, std::uint16_t pin)
        : port(port), pin(pin) {}
};