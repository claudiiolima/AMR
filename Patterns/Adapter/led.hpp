#ifndef LED_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define LED_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint32_t).
#include "digital_output.hpp"  // Inclui o cabeçalho para a classe DigitalOutput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

namespace LedState 
// Namespace para definir os estados do LED.
{
    enum Value 
    // Enumeração para representar os estados possíveis do LED.
    {
        Unsetted = 0,  // Estado "apagado".
        Setted = 1,  // Estado "aceso".
    };
}

namespace LedType 
// Namespace para definir os tipos de LED.
{
    enum Value 
    // Enumeração para representar os tipos possíveis de LED.
    {
        LD4,  // Tipo de LED LD4.
        LD5,  // Tipo de LED LD5.
        LD6,  // Tipo de LED LD6.
    };
}

class Led 
// Declaração da classe abstrata Led.
{
public:
    virtual void Set() = 0;  // Declaração da função virtual pura para acender o LED.
    virtual void Reset() = 0;  // Declaração da função virtual pura para apagar o LED.
    virtual LedState::Value GetState() = 0;  // Declaração da função virtual pura para obter o estado do LED.
    virtual void Toggle() = 0;  // Declaração da função virtual pura para alternar o estado do LED.
    virtual ~Led() = default;  // Declaração do destrutor virtual.
};

class LedAdapter : public Led 
// Declaração da classe LedAdapter que herda da classe Led.
{
public:
    LedAdapter(LedType::Value led);  // Declaração do construtor.
    LedAdapter(LedType::Value led, LedState::Value initial_value);  // Declaração da sobrecarga do construtor.
    ~LedAdapter();  // Declaração do destrutor.

    void Set() override 
    // Função membro que acende o LED, implementada da classe base Led.
    {
        this->adaptee_->Write(DOState::Setted);  // Escreve o estado "aceso" no objeto DigitalOutput.
    }

    void Reset() override 
    // Função membro que apaga o LED, implementada da classe base Led.
    {
        this->adaptee_->Write(DOState::Unsetted);  // Escreve o estado "apagado" no objeto DigitalOutput.
    }

    LedState::Value GetState() override 
    // Função membro que retorna o estado do LED, implementada da classe base Led.
    {
        DOState::Value const do_state = this->adaptee_->Read();  // Lê o estado atual do objeto DigitalOutput.
        LedState::Value led_state = LedState::Unsetted;  // Inicializa o estado do LED como "apagado".

        if (do_state == DOState::Setted) 
        // Se o estado do DigitalOutput for "aceso", atualiza o estado do LED para "aceso".
        {
            led_state = LedState::Setted;  // Atualiza o estado do LED para "aceso".
        }

        return led_state;  // Retorna o estado do LED.
    }

    void Toggle() override 
    // Função membro que alterna o estado do LED, implementada da classe base Led.
    {
        if (this->GetState() == LedState::Setted) 
        // Se o estado atual do LED for "aceso", apaga o LED.
        {
            this->Reset();  // Apaga o LED.
        }
        else 
        // Se o estado atual do LED for "apagado", acende o LED.
        {
            this->Set();  // Acende o LED.
        }
    }

private:
    DigitalOutput *adaptee_;  // Ponteiro para o objeto DigitalOutput.
};

#endif // !LED_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
