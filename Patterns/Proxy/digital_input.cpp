#include "digital_input.hpp"  // Inclui o cabeçalho para a classe DigitalInput, que contém a definição da classe e suas declarações de função.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

DigitalInput::DigitalInput(const DigitalInputConfig &config)
    : port(config.port), pin(config.pin)
// Construtor da classe DigitalInput que inicializa os membros da classe `port` e `pin` com os valores passados como parâmetros.
{
}

DIState::Value DigitalInput::Read() 
// Função membro que lê o estado do pino digital.
{
    GPIO_PinState const pin_state = HAL_GPIO_ReadPin(this->port, this->pin);  // Lê o estado do pino GPIO especificado.
    DIState::Value digital_input_state = DIState::Unsetted;  // Inicializa a variável de estado digital como Unsetted.

    if (pin_state == GPIO_PIN_SET) 
    // Verifica se o estado do pino é SET.
    {
        digital_input_state = DIState::Setted;  // Se o pino está SET, atualiza o estado digital para Setted.
    }

    return digital_input_state;  // Retorna o estado digital.
}

DigitalInput::~DigitalInput() 
// Destrutor da classe DigitalInput. Atualmente, não realiza nenhuma ação específica.
{
}
