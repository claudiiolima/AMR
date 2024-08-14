#ifndef BUTTON_HPP__
#define BUTTON_HPP__

#include <cstdint>

#include "adapters.hpp"
#include "digital_input.hpp"

// Define o número de ticks para debounce do botão.
const Adapters::Ticks BUTTON_DEBOUNCE_TICKS = 40u;

class Button 
{
public:
  virtual void Sample() = 0;   // Declaração da função virtual pura para amostrar o estado do botão.
  virtual bool GetState() = 0; // Declaração da função virtual pura para obter o estado do botão.
  virtual ~Button() = default; // Declaração do destrutor virtual.
};

class ButtonAdapter : public Button 
// Declaração da classe ButtonAdapter que herda da classe Button.
{
public:
  ButtonAdapter(Adapters::ButtonType button);
  ~ButtonAdapter();

  /**
   * @brief Amostra o estado do botão.
   * 
   */
  void Sample() override
  {
    // Armazena a amostra atual em aux_sample.
    this->aux_sample     = this->current_sample;
    // Lê o estado atual do botão e atualiza current_sample.
    this->current_sample = (this->adaptee_->Read() == Proxies::DigitalState::High) ? true : false;  

    // Verifica a amostra atual com a antiga.
    if (this->current_sample == this->old_sample) 
    {
      // Verifica se o contador de debounce atingir o limite.
      if (this->tick >= BUTTON_DEBOUNCE_TICKS) 
      {
        // Atualiza o estado do botão.
        this->state = this->current_sample;
      }
      else 
      {
        // Incrementa o contador de debounce.
        this->tick++;
      }
    }
    else 
    {
      if (this->tick > 0u) 
      {
        // Decrementa o contador de debounce.
        this->tick--;
      }
    }
    // Atualiza a amostra antiga com aux_sample.
    this->old_sample = this->aux_sample;
  }

  /**
   * @brief Retorna o estado do botão.
   * 
   * @return Estado do botão
   * @retval true Pressed.
   * @retval false Unpressed.
   */
  bool GetState() override 
  {
    return this->state;
  }

private:
  DigitalInput *adaptee_;  // Ponteiro para o objeto DigitalInput.
  Adapters::Ticks tick;  // Contador de debounce.
  bool aux_sample;  // Armazena a amostra auxiliar.
  bool current_sample;  // Armazena a amostra atual.
  bool old_sample;  // Armazena a amostra antiga.
  bool state;  // Armazena o estado atual do botão.
};

#endif // BUTTON_HPP__
