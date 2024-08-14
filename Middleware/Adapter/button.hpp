#ifndef BUTTON_HPP__
#define BUTTON_HPP__

#include <cstdint>

#include "adapters.hpp"
#include "debouncer.hpp"
#include "digital_input.hpp"

// Define o número de ticks para debounce do botão.
const Debouncers::Ticks BUTTON_DEBOUNCE_TICKS = 40u;

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
    // Lê o estado atual do botão e atualiza current_sample.
    this->current_sample = (this->adaptee_->Read() == Proxies::DigitalState::High) ? true : false;

    this->debouncer_->Sample(this->current_sample);
    this->state = this->debouncer_->Get();
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
  Debouncer *debouncer_;  // Ponteiro para o objeto Debouncer.
  DigitalInput *adaptee_; // Ponteiro para o objeto DigitalInput.
  bool current_sample;    // Armazena o estado atual do botão.
  bool state;             // Armazena o estado atual do botão.
};

#endif // BUTTON_HPP__
