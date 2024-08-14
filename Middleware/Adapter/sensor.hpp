#ifndef SENSOR_HPP__
#define SENSOR_HPP__

#include <cstdint>

#include "adapters.hpp"
#include "analog_input.hpp"

class Sensor
{
public:
  virtual void Sample() = 0;                // Declaração da função virtual pura para amostrar o sensor.
  virtual Adapters::SensorRaw GetRaw() = 0; // Declaração da função virtual pura para obter o valor bruto do sensor.
  virtual ~Sensor() = default;              // Declaração do destrutor virtual.
};

class SensorAdapter : public Sensor 
{
public:
  SensorAdapter(Proxies::AnalogInputObj &adc, Proxies::Timeout timeout);
  ~SensorAdapter();

  /**
   * @brief Amostra o sensor.
   * 
   */
  void Sample() override
  {
    this->adaptee_->Sample();  // Chama a função Sample do objeto AnalogInput.
    this->raw = this->adaptee_->Get();  // Obtém o valor do objeto AnalogInput e armazena na variável raw.
  }

  /**
   * @brief Retorna o valor bruto do sensor.
   * 
   */
  Adapters::SensorRaw GetRaw() override
  {
    // Retorna o valor armazenado na variável raw.
    return this->raw;
  }

private:
    AnalogInput *adaptee_; // Ponteiro para o objeto AnalogInput.
    Adapters::SensorRaw raw;     // Variável para armazenar o valor bruto do sensor.
};

#endif // SENSOR_HPP__
