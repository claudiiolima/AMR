#ifndef LAMP_HPP__
#define LAMP_HPP__

#include <cstdint>

#include "adapters.hpp"
#include "analog_output.hpp"

class Lamp 
{
public:
    virtual void Set(float value) = 0; // Declaração da função virtual pura para definir o valor da lâmpada.
    virtual ~Lamp() = default;         // Declaração do destrutor virtual.
};

class LampAdapter : public Lamp 
{
public:
    LampAdapter(Proxies::AnalogOutput &dac, Proxies::AnalogChannel channel, Adapters::LampPercentage initial_value = 0.0f);
    ~LampAdapter();

    /**
     * @brief Define o valor da lâmpada.
     * 
     * @param[in] value Valor da lâmpada. [0.0, 100.0]
     */
    void Set(float value) override 
    {
        // Converte o valor de porcentagem para o valor correspondente no range do DAC e define o valor no objeto AnalogOutput.
        this->adaptee_->Set((uint32_t)(value * (float)ANALOG_OUTPUT_MAX_VALUE / 100.0f));
    };

private:
    AnalogOutput *adaptee_; // Ponteiro para o objeto AnalogOutput.
};

#endif // LAMP_HPP__
