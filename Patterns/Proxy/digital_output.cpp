#include "digital_output.hpp"  // Inclui o cabeçalho para a classe DigitalOutput, que contém a definição da classe e suas declarações de função.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

DigitalOutput::DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin) : port(port), pin(pin) 
// Construtor da classe DigitalOutput que inicializa os membros da classe `port` e `pin` com os valores passados como parâmetros.
{
    this->Write(DOState::Unsetted);  // Define o estado inicial do pino digital como Unsetted (pino está LOW).
}

DigitalOutput::DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin, DOState::Value initial_value) : port(port), pin(pin) 
// Sobrecarga do construtor que permite definir um valor inicial específico para o pino digital.
{
    this->Write(initial_value);  // Define o estado inicial do pino digital conforme especificado pelo usuário.
}

void DigitalOutput::Write(DOState::Value state) 
// Função membro que define o estado do pino digital.
{   
    if (state == DOState::Setted) 
    // Verifica se o estado desejado é Setted.
    {
        HAL_GPIO_WritePin(this->port, this->pin, GPIO_PIN_SET);  // Define o pino como HIGH.
    }
    else 
    // Caso contrário, define o estado como Unsetted.
    {
        HAL_GPIO_WritePin(this->port, this->pin, GPIO_PIN_RESET);  // Define o pino como LOW.
    }
}

DOState::Value DigitalOutput::Read() 
// Função membro que lê o estado atual do pino digital.
{
    GPIO_PinState const pin_state = HAL_GPIO_ReadPin(this->port, this->pin);  // Lê o estado do pino GPIO especificado.
    DOState::Value digital_output_state = DOState::Unsetted;  // Inicializa a variável de estado digital como Unsetted.

    if (pin_state == GPIO_PIN_SET) 
    // Verifica se o estado do pino é SET.
    {
        digital_output_state = DOState::Setted;  // Se o pino está SET, atualiza o estado digital para Setted.
    }

    return digital_output_state;  // Retorna o estado digital.
}

void DigitalOutput::Toggle() 
// Função membro que alterna o estado atual do pino digital.
{
    if (this->Read() == DOState::Setted) 
    // Verifica se o estado atual é Setted.
    {
        this->Write(DOState::Unsetted);  // Se estiver Setted, muda para Unsetted.
    }
    else 
    // Caso contrário, muda para Setted.
    {
        this->Write(DOState::Setted);  // Se estiver Unsetted, muda para Setted.
    }
}

DigitalOutput::~DigitalOutput() 
// Destrutor da classe DigitalOutput. Atualmente, não realiza nenhuma ação específica.
{
}
