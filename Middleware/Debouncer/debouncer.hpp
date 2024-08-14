
#ifndef DEBOUNCER_HPP__
#define DEBOUNCER_HPP__

#include <cstdint>

namespace Debouncers
{

typedef std::uint32_t Ticks;

}

class Debouncer {
public:
  Debouncer(Debouncers::Ticks limit_ticks = 40);
  void Sample(bool value);
  bool Get();
  ~Debouncer();

private:
  Debouncers::Ticks limit_ticks;  // Contador de debounce.
  Debouncers::Ticks tick;  // Contador de debounce.
  bool aux_sample;  // Armazena a amostra auxiliar.
  bool current_sample;  // Armazena a amostra atual.
  bool old_sample;  // Armazena a amostra antiga.
  bool state;  // Armazena o estado atual do botão.
};

#endif // DEBOUNCER_HPP__
