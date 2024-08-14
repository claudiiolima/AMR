#include "debouncer.hpp"

Debouncer::Debouncer(Debouncers::Ticks limit_ticks)
  : limit_ticks(limit_ticks), tick(0), aux_sample(false), current_sample(false), old_sample(false), state(false) {}

void Debouncer::Sample(bool value)
{
  // Armazena a amostra atual em aux_sample.
    this->aux_sample     = this->current_sample;
    // Lê o estado atual do botão e atualiza current_sample.
    this->current_sample = value;

    // Verifica a amostra atual com a antiga.
    if (this->current_sample == this->old_sample) 
    {
      // Verifica se o contador de debounce atingir o limite.
      if (this->tick >= this->limit_ticks) 
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

bool Debouncer::Get()
{
  return this->state;
}

Debouncer::~Debouncer() {}
