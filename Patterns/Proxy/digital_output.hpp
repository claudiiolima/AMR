#ifndef DIGITAL_OUTPUT_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define DIGITAL_OUTPUT_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint16_t).
#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

namespace DOState 
// Namespace para definir os estados do pino digital.
{
    enum Value 
    // Enumeração para representar os estados possíveis do pino digital.
    {
        Unsetted = 0,  // Estado "não configurado" (pino está LOW).
        Setted = 1,  // Estado "configurado" (pino está HIGH).
    };
}

class DigitalOutput 
// Declaração da classe DigitalOutput.
{
public:
    DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin);  // Declaração do construtor.
    DigitalOutput(GPIO_TypeDef *port, std::uint16_t pin, DOState::Value initial_value);  // Declaração da sobrecarga do construtor.
    void Write(DOState::Value state);  // Declaração da função membro que define o estado do pino digital.
    DOState::Value Read();  // Declaração da função membro que lê o estado atual do pino digital.
    void Toggle();  // Declaração da função membro que alterna o estado do pino digital.
    ~DigitalOutput();  // Declaração do destrutor.

private:
    GPIO_TypeDef *port;  // Ponteiro para a estrutura do porto GPIO.
    std::uint16_t pin;  // Número do pino do porto GPIO.
};

#endif // !DIGITAL_OUTPUT_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
