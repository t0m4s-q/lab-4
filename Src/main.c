/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Laboratorio 3 - UART y Arquitectura Basada en Eventos
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define T_REBOTE_MS 20U
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables --------------------------------------------------------- */
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */
// Control de Display multiplexado
volatile uint8_t indice_pantalla = 0;
volatile uint8_t digitos_a_mostrar[4] = {0, 0, 0, 0};

// Buffer de Recepción UART
char rx_buffer[30] = {0};
uint8_t rx_byte = 0;
uint8_t rx_index = 0;
volatile uint8_t flag_message = 0;

// Variables de estado del Temporizador Programable
volatile uint16_t tiempo_restante = 120; // Tiempo en segundos (formato MM.SS)
const uint16_t TIEMPO_INICIAL_DEFECTO = 120;
volatile bool cronometro_corriendo = false;
volatile bool estado_alarma = false;

// Contador de ticks para la base de tiempo de 1 segundo (500 * 2 ms = 1000 ms)
volatile uint16_t contador_500ticks = 0;
volatile uint8_t flag_alarma_notificada = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_UART4_Init(void);

/* USER CODE BEGIN PFP */
void ActualizarDigitos(void);
void SeleccionarDigito(uint8_t indicepantalla);
void Display_EscribirPatron(uint8_t patron, uint8_t indice_pantalla);
bool HayNuevaPulsacion(GPIO_TypeDef *puerto, uint16_t pin, GPIO_PinState *estado_valido);
void ProcesarComandoUART(void);
/* USER CODE END PFP */

/* Private user code --------------------------------------------------------- */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_UART4_Init();

  /* USER CODE BEGIN 2 */
  ActualizarDigitos();

  // Iniciar Timer 1 para refresco de display y base de tiempo
  HAL_TIM_Base_Start_IT(&htim1);

  // Iniciar recepción UART4 por interrupción (1 byte)
  HAL_UART_Receive_IT(&huart4, &rx_byte, 1);

  // Estados de pulsadores
  GPIO_PinState estado_sw1 = GPIO_PIN_SET; // SW1: START / PAUSE
  GPIO_PinState estado_sw2 = GPIO_PIN_SET; // SW2: RESET
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 1. Procesar Comandos UART recibidos de forma asíncrona
    ProcesarComandoUART();

    // 2. Notificación UART cuando salta la Alarma
    if (flag_alarma_notificada)
    {
      flag_alarma_notificada = 0;
      HAL_UART_Transmit(&huart4, (uint8_t*)"ALARM 00.00\r\n", 13, 100);
    }

    // 3. Polling SW1: START / PAUSE
    if (HayNuevaPulsacion(START_GPIO_Port, START_Pin, &estado_sw1))
    {
      if (!estado_alarma)
      {
        cronometro_corriendo = !cronometro_corriendo;
      }
    }

    // 4. Polling SW2: RESET / Reconocer Alarma
    if (HayNuevaPulsacion(PULSADOR_GPIO_Port, PULSADOR_Pin, &estado_sw2))
    {
      cronometro_corriendo = false;
      estado_alarma = false;
      HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4); // Apagar buzzer
      tiempo_restante = TIEMPO_INICIAL_DEFECTO;
      ActualizarDigitos();
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function (2 ms para refresco)
  */
static void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 83;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function (PWM para Buzzer)
  */
static void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 83;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2273;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1137;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim2);
}

/**
  * @brief UART4 Initialization Function (115200 8N1)
  */
static void MX_UART4_Init(void)
{
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOC, BIT_1_Pin|BIT_0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, SEGMENTO_B_Pin|SEGMENTO_D_Pin|SEGMENTO_P_Pin|SEGMENTO_C_Pin
                          |SEGMENTO_G_Pin|SEGMENTO_E_Pin|SEGMENTO_A_Pin|SEGMENTO_F_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = BIT_1_Pin|BIT_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = START_Pin|PULSADOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SEGMENTO_B_Pin|SEGMENTO_D_Pin|SEGMENTO_P_Pin|SEGMENTO_C_Pin
                          |SEGMENTO_G_Pin|SEGMENTO_E_Pin|SEGMENTO_A_Pin|SEGMENTO_F_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/**
  * @brief Interrupción del Timer 1: Refresco de Display + Tick de 1 segundo
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1)
  {
    // Refresco multiplexado de displays
    Display_EscribirPatron(digitos_a_mostrar[indice_pantalla], indice_pantalla);
    SeleccionarDigito(indice_pantalla);

    indice_pantalla++;
    if (indice_pantalla >= 4)
    {
      indice_pantalla = 0;
    }

    // Cuenta regresiva de 1 segundo (500 * 2 ms = 1000 ms)
    if (cronometro_corriendo)
    {
      contador_500ticks++;
      if (contador_500ticks >= 500)
      {
        contador_500ticks = 0;
        if (tiempo_restante > 0)
        {
          tiempo_restante--;
          ActualizarDigitos();
        }
        
        if (tiempo_restante == 0)
        {
          cronometro_corriendo = false;
          estado_alarma = true;
          HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); // Activar alarma sonora
          flag_alarma_notificada = 1;
        }
      }
    }
  }
}

/**
  * @brief Callback de Recepción UART por Interrupción
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  if(huart->Instance == UART4)
  {
    if(rx_byte != '\n' && rx_byte != '\r')
    {
      rx_buffer[rx_index] = rx_byte;
      rx_index++;
      if(rx_index >= sizeof(rx_buffer) - 1)
      {
        rx_index = 0; // Prevenir desbordamiento de buffer
      }
    }
    else if(rx_index > 0)
    {
      rx_buffer[rx_index] = '\0'; // Finalizar string C
      flag_message = 1;
    }
    // Habilitar siguiente interrupción de recepción
    HAL_UART_Receive_IT(&huart4, &rx_byte, 1);
  }
}

/**
  * @brief Decodificador de Comandos de Texto UART
  */
void ProcesarComandoUART(void)
{
  if (flag_message)
  {
    char mensaje_estado[35];

    if (strcmp(rx_buffer, "start") == 0 || strcmp(rx_buffer, "START") == 0)
    {
      if (!estado_alarma)
      {
        cronometro_corriendo = true;
      }
      HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
    }
    else if (strcmp(rx_buffer, "pause") == 0 || strcmp(rx_buffer, "PAUSE") == 0)
    {
      cronometro_corriendo = false;
      HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
    }
    else if (strcmp(rx_buffer, "status") == 0 || strcmp(rx_buffer, "STATUS") == 0)
    {
      uint8_t min = tiempo_restante / 60;
      uint8_t seg = tiempo_restante % 60;

      if (estado_alarma)
      {
        sprintf(mensaje_estado, "ALARM %02d.%02d\r\n", min, seg);
      }
      else if (cronometro_corriendo)
      {
        sprintf(mensaje_estado, "RUNNING %02d.%02d\r\n", min, seg);
      }
      else
      {
        sprintf(mensaje_estado, "PAUSED %02d.%02d\r\n", min, seg);
      }

      HAL_UART_Transmit(&huart4, (uint8_t*)mensaje_estado, strlen(mensaje_estado), 100);
    }
    else if (strncmp(rx_buffer, "set ", 4) == 0 || strncmp(rx_buffer, "SET ", 4) == 0)
    {
      int valor_recibido = atoi(&rx_buffer[4]);

      // Rango permitido de 0 a 5999 segundos
      if (valor_recibido >= 0 && valor_recibido <= 5999)
      {
        cronometro_corriendo = false;
        estado_alarma = false;
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
        tiempo_restante = (uint16_t)valor_recibido;
        ActualizarDigitos();
        HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
      }
      else
      {
        HAL_UART_Transmit(&huart4, (uint8_t*)"ERROR RANGO\r\n", 13, 100);
      }
    }
    else if (strcmp(rx_buffer, "reset") == 0 || strcmp(rx_buffer, "RESET") == 0)
    {
      cronometro_corriendo = false;
      estado_alarma = false;
      HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
      tiempo_restante = TIEMPO_INICIAL_DEFECTO;
      ActualizarDigitos();
      HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
    }
    else
    {
      HAL_UART_Transmit(&huart4, (uint8_t*)"ERROR\r\n", 7, 100);
    }

    // Limpieza de buffer
    memset((char*)rx_buffer, 0, sizeof(rx_buffer));
    rx_index = 0;
    flag_message = 0;
  }
}

/**
  * @brief Selecciona el dígito multiplexado (PC0, PC2)
  */
void SeleccionarDigito(uint8_t indicepantalla)
{
  if(indicepantalla == 0)
  {
    HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_RESET);
  }
  else if(indicepantalla == 1)
  {
    HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_SET);
  }
  else if(indicepantalla == 2)
  {
    HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_RESET);
  }
  else if(indicepantalla == 3)
  {
    HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_SET);
  }
}

/**
  * @brief Escribe patrón de 7 segmentos y activa el punto decimal en el segundo dígito (MM.SS)
  */
void Display_EscribirPatron(uint8_t patron, uint8_t indice_pantalla)
{
  HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_E_GPIO_Port, SEGMENTO_E_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SEGMENTO_P_GPIO_Port, SEGMENTO_P_Pin, GPIO_PIN_RESET);

  if (indice_pantalla == 2)
  {
    HAL_GPIO_WritePin(SEGMENTO_P_GPIO_Port, SEGMENTO_P_Pin, GPIO_PIN_SET);
  }

  switch(patron)
  {
    case 0:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_E_GPIO_Port, SEGMENTO_E_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
      break;
    case 1:
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      break;
    case 2:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_E_GPIO_Port, SEGMENTO_E_Pin, GPIO_PIN_SET);
      break;
    case 3:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      break;
    case 4:
      HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      break;
    case 5:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      break;
    case 6:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_E_GPIO_Port, SEGMENTO_E_Pin, GPIO_PIN_SET);
      break;
    case 7:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      break;
    case 8:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_E_GPIO_Port, SEGMENTO_E_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      break;
    case 9:
      HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_B_GPIO_Port, SEGMENTO_B_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
      break;
  }
}

/**
  * @brief Convierte segundos a formato MM.SS en 4 dígitos
  */
void ActualizarDigitos(void) 
{
  uint8_t min = tiempo_restante / 60;
  uint8_t seg = tiempo_restante % 60;

  digitos_a_mostrar[3] = min / 10;
  digitos_a_mostrar[2] = min % 10;
  digitos_a_mostrar[1] = seg / 10;
  digitos_a_mostrar[0] = seg % 10;
}

/**
  * @brief Lectura por Polling + Antirrebote de Pulsadores
  */
bool HayNuevaPulsacion(GPIO_TypeDef *puerto, uint16_t pin, GPIO_PinState *estado_valido)
{
  GPIO_PinState lectura1;
  GPIO_PinState lectura2;
  bool nueva_pulsacion = false;

  lectura1 = HAL_GPIO_ReadPin(puerto, pin);

  if (lectura1 != (*estado_valido))
  {
    HAL_Delay(T_REBOTE_MS);
    lectura2 = HAL_GPIO_ReadPin(puerto, pin);

    if (lectura2 == lectura1)
    {
      GPIO_PinState estado_anterior = *estado_valido;
      *estado_valido = lectura2;

      if ((estado_anterior == GPIO_PIN_SET) && (*estado_valido == GPIO_PIN_RESET))
      {
        nueva_pulsacion = true;
      }
    }
  }
  return nueva_pulsacion;
}

/* USER CODE END 4 */

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}