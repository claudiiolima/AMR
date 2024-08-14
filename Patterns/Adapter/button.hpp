#ifndef BUTTON_HPP__  // Prevenção contra inclusão múltipla do arquivo de cabeçalho.
#define BUTTON_HPP__

#include <cstdint>  // Inclui a biblioteca padrão de tipos inteiros de largura fixa (como uint32_t).
#include "digital_input.hpp"  // Inclui o cabeçalho para a classe DigitalInput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

const std::uint32_t BUTTON_DEBOUNCE_TICKS = 40u;  
// Define o número de ticks para debounce do botão.

namespace ButtonState 
// Namespace para definir os estados do botão.
{
    enum Value 
    // Enumeração para representar os estados possíveis do botão.
    {
        Unsetted = 0,  // Estado "não pressionado".
        Setted = 1,  // Estado "pressionado".
    };
}

namespace ButtonType 
// Namespace para definir os tipos de botão.
{
    enum Value 
    // Enumeração para representar os tipos possíveis de botão.
    {
        BUTTON_BLUE,  // Tipo de botão azul.
    };
}

class Button 
// Declaração da classe abstrata Button.
{
public:
    virtual void Sample() = 0;  // Declaração da função virtual pura para amostrar o estado do botão.
    virtual bool GetState() = 0;  // Declaração da função virtual pura para obter o estado do botão.
    virtual ~Button() = default;  // Declaração do destrutor virtual.
};

class ButtonAdapter : public Button 
// Declaração da classe ButtonAdapter que herda da classe Button.
{
public:
    ButtonAdapter(ButtonType::Value button);  // Declaração do construtor.
    ~ButtonAdapter();  // Declaração do destrutor.

    void Sample() override 
    // Função membro que amostra o estado do botão, implementada da classe base Button.
    {
        this->aux_sample     = this->current_sample;  // Armazena a amostra atual em aux_sample.
        this->current_sample = (this->adaptee_->Read() == DIState::Setted) ? true : false;  
        // Lê o estado atual do botão e atualiza current_sample.

        if (this->current_sample == this->old_sample) 
        // Verifica se a amostra atual é igual à amostra antiga.
        {
            if (this->tick >= BUTTON_DEBOUNCE_TICKS) 
            // Se o contador de debounce atingir o limite, atualiza o estado do botão.
            {
                this->state = this->current_sample;  // Atualiza o estado do botão.
            }
            else 
            // Incrementa o contador de debounce.
            {
                this->tick++;  // Incrementa o contador de debounce.
            }
        }
        else 
        // Se a amostra atual for diferente da amostra antiga, decrementa o contador de debounce.
        {
            if (this->tick > 0u) 
            {
                this->tick--;  // Decrementa o contador de debounce.
            }
        }
        this->old_sample = this->aux_sample;  // Atualiza a amostra antiga com aux_sample.
    }

    bool GetState() override 
    // Função membro que retorna o estado do botão, implementada da classe base Button.
    {
        return this->state;  // Retorna o estado do botão.
    }

private:
    DigitalInput *adaptee_;  // Ponteiro para o objeto DigitalInput.
    std::uint32_t tick;  // Contador de debounce.
    bool aux_sample;  // Armazena a amostra auxiliar.
    bool current_sample;  // Armazena a amostra atual.
    bool old_sample;  // Armazena a amostra antiga.
    bool state;  // Armazena o estado atual do botão.
};

#endif // !BUTTON_HPP__  // Fim da prevenção contra inclusão múltipla do arquivo de cabeçalho.
