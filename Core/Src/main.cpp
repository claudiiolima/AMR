/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <led.hpp>
#include <button.hpp>
#include <sensor.hpp>
#include <lamp.hpp>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;  // Manipulador do periférico ADC1.
DAC_HandleTypeDef hdac;  // Manipulador do periférico DAC.
TIM_HandleTypeDef htim2;  // Manipulador do periférico TIM2.

/* USER CODE BEGIN PV */
static ButtonAdapter blue_button = ButtonAdapter(Adapters::ButtonType::BUTTON_BLUE); // Criação de um objeto ButtonAdapter para o botão azul.
static LedAdapter led_4          = LedAdapter(Adapters::LedType::LD4);               // Criação de um objeto LedAdapter para o LED LD4.
static LedAdapter led_5          = LedAdapter(Adapters::LedType::LD5);               // Criação de um objeto LedAdapter para o LED LD5.
static SensorAdapter some_sensor = SensorAdapter(hadc1, 1u);                         // Criação de um objeto SensorAdapter para o sensor, usando ADC1 e um tempo limite de 1ms.
static LampAdapter some_lamp     = LampAdapter(hdac, DAC_CHANNEL_1);                 // Criação de um objeto LampAdapter para o DAC, usando o canal 1.
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);  // Protótipo da função para configurar o clock do sistema.
static void MX_GPIO_Init(void);  // Protótipo da função para inicializar os pinos GPIO.
static void MX_ADC1_Init(void);  // Protótipo da função para inicializar o ADC1.
static void MX_DAC_Init(void);  // Protótipo da função para inicializar o DAC.
static void MX_TIM2_Init(void);  // Protótipo da função para inicializar o TIM2.
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) 
// Callback chamado quando o temporizador TIM2 atinge o final do período.
{
	if (htim->Instance == TIM2)  // Verifica se o temporizador é o TIM2.
	{
		if (blue_button.GetState() == true)  // Verifica o estado do botão azul.
		{
			led_5.Set();  // Se o botão estiver pressionado, acende o LED LD5.
		}
		else
		{
			led_5.Reset();  // Se o botão não estiver pressionado, apaga o LED LD5.
		}
		led_4.Toggle();  // Alterna o estado do LED LD4.

    some_sensor.Sample();  // Amostra o sensor.
    some_lamp.Set(some_sensor.GetRaw());  // Define o valor do lamp para o valor bruto do sensor.
    //
		// HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (AD_RES << 4));  // Código comentado para definir o valor do DAC.
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();  // Inicializa a biblioteca HAL (Hardware Abstraction Layer).

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();  // Configura o clock do sistema.

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();  // Inicializa todos os pinos GPIO.
  MX_ADC1_Init();  // Inicializa o ADC1.
  MX_DAC_Init();  // Inicializa o DAC.
  MX_TIM2_Init();  // Inicializa o TIM2.
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);  // Inicia o TIM2 em modo de interrupção.
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  blue_button.Sample();  // Amostra o estado do botão azul.
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};  // Estrutura para configuração do oscilador do RCC.
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};  // Estrutura para configuração dos clocks do RCC.

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();  // Habilita o clock para o controlador de potência.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  // Configura a escala de tensão do regulador interno.

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  // Configura o tipo de oscilador para HSE (High-Speed External).
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;  // Habilita o oscilador HSE.
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;  // Habilita o PLL (Phase-Locked Loop).
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;  // Configura a fonte do PLL como HSE.
  RCC_OscInitStruct.PLL.PLLM = 8;  // Configura o divisor de entrada do PLL.
  RCC_OscInitStruct.PLL.PLLN = 336;  // Configura o multiplicador do PLL.
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;  // Configura o divisor de saída do PLL.
  RCC_OscInitStruct.PLL.PLLQ = 7;  // Configura o divisor Q do PLL.
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a configuração falhar.
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;  // Configura os tipos de clocks a serem inicializados.
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // Configura a fonte do clock do sistema como PLL.
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // Configura o divisor do clock AHB.
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  // Configura o divisor do clock APB1.
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  // Configura o divisor do clock APB2.

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a configuração falhar.
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};  // Estrutura para configuração dos canais do ADC.

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;  // Define o ADC1 como o periférico ADC.
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;  // Configura o prescaler do clock do ADC.
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;  // Configura a resolução do ADC para 12 bits.
  hadc1.Init.ScanConvMode = DISABLE;  // Desativa o modo de conversão de varredura.
  hadc1.Init.ContinuousConvMode = DISABLE;  // Desativa o modo de conversão contínua.
  hadc1.Init.DiscontinuousConvMode = DISABLE;  // Desativa o modo de conversão descontínua.
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;  // Desativa o disparo externo.
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;  // Configura o início da conversão para software.
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;  // Alinha os dados do ADC à direita.
  hadc1.Init.NbrOfConversion = 1;  // Configura o número de conversões para 1.
  hadc1.Init.DMAContinuousRequests = DISABLE;  // Desativa as solicitações contínuas de DMA.
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;  // Configura a seleção de fim de conversão para uma única conversão.
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a inicialização falhar.
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;  // Configura o canal ADC1.
  sConfig.Rank = 1;  // Configura o ranking do canal na sequência.
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;  // Configura o tempo de amostragem para 3 ciclos.
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a configuração do canal falhar.
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};  // Estrutura para configuração dos canais do DAC.

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;  // Define o DAC como o periférico DAC.
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a inicialização falhar.
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;  // Desativa o disparo do DAC.
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;  // Habilita o buffer de saída do DAC.
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a configuração do canal falhar.
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};  // Estrutura para configuração da fonte de clock do TIM2.
  TIM_MasterConfigTypeDef sMasterConfig = {0};  // Estrutura para configuração mestre do TIM2.

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;  // Define o TIM2 como o periférico TIM.
  htim2.Init.Prescaler = 999;  // Configura o prescaler do TIM2.
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;  // Configura o modo do contador para contar para cima.
  htim2.Init.Period = 16799;  // Define o período do TIM2.
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // Configura a divisão de clock do TIM2.
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // Desativa o pré-carregamento do auto-recarregamento.
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a inicialização falhar.
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;  // Configura a fonte de clock como interna.
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a configuração da fonte de clock falhar.
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;  // Configura o gatilho de saída mestre para reset.
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;  // Desativa o modo mestre-escravo.
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();  // Chama o manipulador de erro se a configuração de sincronização mestre falhar.
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};  // Estrutura para configuração dos pinos GPIO.
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();  // Habilita o clock para o GPIOC.
  __HAL_RCC_GPIOH_CLK_ENABLE();  // Habilita o clock para o GPIOH.
  __HAL_RCC_GPIOA_CLK_ENABLE();  // Habilita o clock para o GPIOA.
  __HAL_RCC_GPIOB_CLK_ENABLE();  // Habilita o clock para o GPIOB.
  __HAL_RCC_GPIOD_CLK_ENABLE();  // Habilita o clock para o GPIOD.
  __HAL_RCC_GPIOE_CLK_ENABLE();  // Habilita o clock para o GPIOE.

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);  // Configura o nível do pino OTG_FS_PowerSwitchOn como alto.

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);  // Configura o nível dos pinos LD4, LD3, LD5, LD6 e Audio_RST como baixo.

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;  // Configura o pino OTG_FS_PowerSwitchOn.
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Configura o modo como saída push-pull.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Configura a velocidade do pino como baixa.
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino OTG_FS_PowerSwitchOn.

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;  // Configura o pino PDM_OUT.
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Configura o modo como função alternativa push-pull.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Configura a velocidade do pino como baixa.
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;  // Configura a função alternativa como SPI2.
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino PDM_OUT.

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;  // Configura o pino B1.
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;  // Configura o modo como evento de borda crescente.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino B1.

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;  // Configura o pino BOOT1.
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Configura o modo como entrada.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino BOOT1.

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;  // Configura o pino CLK_IN.
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Configura o modo como função alternativa push-pull.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Configura a velocidade do pino como baixa.
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;  // Configura a função alternativa como SPI2.
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino CLK_IN.

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;  // Configura os pinos LD4, LD3, LD5, LD6 e Audio_RST.
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Configura o modo como saída push-pull.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Configura a velocidade dos pinos como baixa.
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);  // Inicializa os pinos LD4, LD3, LD5, LD6 e Audio_RST.

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;  // Configura o pino VBUS_FS.
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Configura o modo como entrada.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino VBUS_FS.

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;  // Configura os pinos OTG_FS_ID, OTG_FS_DM e OTG_FS_DP.
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Configura o modo como função alternativa push-pull.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Configura a velocidade dos pinos como baixa.
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;  // Configura a função alternativa como OTG_FS.
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // Inicializa os pinos OTG_FS_ID, OTG_FS_DM e OTG_FS_DP.

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;  // Configura o pino OTG_FS_OverCurrent.
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Configura o modo como entrada.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino OTG_FS_OverCurrent.

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;  // Configura os pinos Audio_SCL e Audio_SDA.
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;  // Configura o modo como função alternativa open-drain.
  GPIO_InitStruct.Pull = GPIO_PULLUP;  // Ativa o pull-up.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Configura a velocidade dos pinos como baixa.
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;  // Configura a função alternativa como I2C1.
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  // Inicializa os pinos Audio_SCL e Audio_SDA.

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;  // Configura o pino MEMS_INT2.
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;  // Configura o modo como evento de borda crescente.
  GPIO_InitStruct.Pull = GPIO_NOPULL;  // Desativa o pull-up/pull-down.
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);  // Inicializa o pino MEMS_INT2.

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();  // Desativa as interrupções.
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
