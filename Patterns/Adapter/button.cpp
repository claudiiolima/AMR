#include "button.hpp"  // Inclui o cabeçalho para a classe Button e ButtonAdapter, que contém a definição da classe e suas declarações de função.
#include "digital_output.hpp"  // Inclui o cabeçalho para a classe DigitalOutput.
#include "default_objects.hpp"  // Inclui o novo cabeçalho que define a struct DigitalInputConfig.

#include "core.h"  // Inclui um cabeçalho adicional que contém definições e declarações usadas neste arquivo.

struct ButtonAdapterMap 
// Estrutura que mapeia um tipo de botão para a porta GPIO e o pino correspondente.
{
    GPIO_TypeDef *port;  // Ponteiro para a estrutura do porto GPIO.
    uint16_t pin;  // Número do pino do porto GPIO.
};

ButtonAdapterMap const button_map[] = 
// Mapeamento constante de tipos de botão para suas respectivas portas e pinos GPIO.
{
    [ButtonType::BUTTON_BLUE] = {GPIOA, GPIO_PIN_0}, // Mapeia o botão azul para a porta GPIOA e o pino 0.
};

ButtonAdapter::ButtonAdapter(ButtonType::Value button) 
// Construtor da classe ButtonAdapter que inicializa os membros da classe e cria um novo objeto DigitalInput.
{
    this->state          = false;  // Inicializa o estado do botão como false.
    this->current_sample = false;  // Inicializa a amostra atual como false.
    this->old_sample     = false;  // Inicializa a amostra antiga como false.

    // Cria um novo objeto DigitalInput usando a porta e o pino mapeados para o botão especificado.
    DigitalInputConfig config(button_map[button].port, button_map[button].pin);
    this->adaptee_ = new DigitalInput(config);  
};

ButtonAdapter::~ButtonAdapter() 
// Destrutor da classe ButtonAdapter que deleta o objeto DigitalInput.
{
    delete this->adaptee_;  // Deleta o objeto DigitalInput alocado dinamicamente.
};
