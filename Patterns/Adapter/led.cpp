#include "led.hpp"  // Inclui o cabeçalho para a classe Led e LedAdapter, que contém a definição da classe e suas declarações de função.
#include "digital_output.hpp"  // Inclui o cabeçalho para a classe DigitalOutput.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

struct LedAdapterMap 
// Estrutura que mapeia um tipo de LED para a porta GPIO e o pino correspondente.
{
    GPIO_TypeDef *port;  // Ponteiro para a estrutura do porto GPIO.
    uint16_t pin;  // Número do pino do porto GPIO.
};

LedAdapterMap const led_map[] = 
// Mapeamento constante de tipos de LED para suas respectivas portas e pinos GPIO.
{
    [LedType::LD4] = {.port = GPIOD, .pin = GPIO_PIN_12}, /* LD 4 */
    // Mapeia o LED LD4 para a porta GPIOD e o pino 12.
    [LedType::LD5] = {.port = GPIOD, .pin = GPIO_PIN_14}, /* LD 5 */
    // Mapeia o LED LD5 para a porta GPIOD e o pino 14.
    [LedType::LD6] = {.port = GPIOD, .pin = GPIO_PIN_15}, /* LD 6 */
    // Mapeia o LED LD6 para a porta GPIOD e o pino 15.
};

LedAdapter::LedAdapter(LedType::Value led) 
// Construtor da classe LedAdapter que inicializa um objeto DigitalOutput e define o estado inicial do LED como "apagado".
{
    this->adaptee_ = new DigitalOutput(led_map[led].port, led_map[led].pin);  // Cria um novo objeto DigitalOutput.
    this->Reset();  // Define o estado inicial do LED como "apagado".
};

LedAdapter::LedAdapter(LedType::Value led, LedState::Value initial_value) 
// Sobrecarga do construtor que permite inicializar um objeto DigitalOutput com um valor inicial especificado.
{
    this->adaptee_ = new DigitalOutput(led_map[led].port, led_map[led].pin);  // Cria um novo objeto DigitalOutput.

    if (initial_value == LedState::Setted) 
    // Verifica se o valor inicial do LED é "aceso".
    {
        this->Set();  // Define o estado do LED como "aceso".
    }
    else 
    {
        this->Reset();  // Define o estado do LED como "apagado".
    }
};

LedAdapter::~LedAdapter() 
// Destrutor da classe LedAdapter que deleta o objeto DigitalOutput.
{
    delete this->adaptee_;  // Deleta o objeto DigitalOutput alocado dinamicamente.
};
