#ifndef LED_HPP__
#define LED_HPP__

#include <cstdint>

#include "adapters.hpp"
#include "digital_output.hpp"

class Led 
{
public:
    virtual void Set() = 0;                    // Declaração da função virtual pura para acender o LED.
    virtual void Reset() = 0;                  // Declaração da função virtual pura para apagar o LED.
    virtual Adapters::LedState GetState() = 0; // Declaração da função virtual pura para obter o estado do LED.
    virtual void Toggle() = 0;                 // Declaração da função virtual pura para alternar o estado do LED.
    virtual ~Led() = default;                  // Declaração do destrutor virtual.
};

class LedAdapter : public Led 
// Declaração da classe LedAdapter que herda da classe Led.
{
public:
  LedAdapter(Adapters::LedType led, Adapters::LedState initial_value = Adapters::LedState::On);
  ~LedAdapter();

  /**
   * @brief Acende o LED
   * 
   */
  void Set() override 
  {
    // Escreve o estado "aceso" no objeto DigitalOutput.
    this->adaptee_->Write(Proxies::DigitalState::High);
  }

  /**
   * @brief Apaga o LED
   * 
   */
  void Reset() override 
  {
    // Escreve o estado "apagado" no objeto DigitalOutput.
    this->adaptee_->Write(Proxies::DigitalState::Low);
  }

  /**
   * @brief Retorna o estado do LED, implementada da classe base Led.
   * 
   * @return Adapters::LedState 
   */
  Adapters::LedState GetState() override 
  {
    // Lê o estado atual do objeto DigitalOutput.
    Proxies::DigitalState const do_state = this->adaptee_->Read();
    // Inicializa o estado do LED como "apagado".
    Adapters::LedState led_state = Adapters::LedState::Off;

    // Se o estado do DigitalOutput for "aceso", atualiza o estado do LED para "aceso".
    if (do_state == Proxies::DigitalState::High)
    {
        // Atualiza o estado do LED para "aceso".
        led_state = Adapters::LedState::On;
    }

    // Retorna o estado do LED.
    return led_state;
  }

  /**
   * @brief Alterna o estado do LED, implementada da classe base Led.
   * 
   */
  void Toggle() override 
  {
    // Se o estado atual do LED for "aceso", apaga o LED.
    if (this->GetState() == Adapters::LedState::On) 
    {
      // Apaga o LED.
      this->Reset();
    }
    else 
    // Se o estado atual do LED for "apagado", acende o LED.
    {
      // Acende o LED.
      this->Set();
    }
  }

private:
  DigitalOutput *adaptee_;  // Ponteiro para o objeto DigitalOutput.
};

#endif // LED_HPP__
