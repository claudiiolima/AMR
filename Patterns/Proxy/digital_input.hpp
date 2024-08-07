#ifndef DIGITAL_INPUT_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define DIGITAL_INPUT_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint16_t).
#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

namespace DIState 
// Namespace para definir os estados do pino digital.
{
    enum Value 
    // Enumeração para representar os estados possíveis do pino digital.
    {
        Unsetted = 0,  // Estado "não configurado" (pino está LOW).
        Setted = 1,  // Estado "configurado" (pino está HIGH).
    };
}

class DigitalInput 
// Declaração da classe DigitalInput.
{
public:
    DigitalInput(const DigitalInputConfig &config);     // Declaração do construtor.
    DIState::Value Read();                              // Declaração da função membro que lê o estado do pino digital.
     ~DigitalInput();                                   // Declaração do destrutor.

private:
    GPIO_TypeDef *port;  // Ponteiro para a estrutura do porto GPIO.
    std::uint16_t pin;  // Número do pino do porto GPIO.
};

#endif // !DIGITAL_INPUT_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
