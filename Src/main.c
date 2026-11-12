/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Laboratorio 2 - Temporizadores, Interrupciones y Display Multiplexado
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
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

/* USER CODE BEGIN PV */
volatile uint8_t indice_pantalla = 0;
volatile uint8_t digitos_a_mostrar[4] = {0, 0, 0, 0};
volatile bool cronometro_corriendo = false;
volatile uint8_t centesimas = 0;
volatile uint8_t segundos = 0;
volatile uint8_t contador_2ms = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);

/* USER CODE BEGIN PFP */
void ActualizarDigitos(void);
void SeleccionarDigito(uint8_t indice);
void Display_EscribirPatron(uint8_t patron, uint8_t indice_pantalla);
bool HayNuevaPulsacion(GPIO_TypeDef *puerto, uint16_t pin, GPIO_PinState *estado_valido);
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

  /* USER CODE BEGIN 2 */
  ActualizarDigitos();

  HAL_TIM_Base_Start_IT(&htim1);

  GPIO_PinState estado_sw1 = GPIO_PIN_SET;
  GPIO_PinState estado_sw2 = GPIO_PIN_SET;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (HayNuevaPulsacion(START_GPIO_Port, START_Pin, &estado_sw1))
    {
      cronometro_corriendo = !cronometro_corriendo;
    }

    if (HayNuevaPulsacion(RESET_GPIO_Port, RESET_Pin, &estado_sw2))
    {
      if (!cronometro_corriendo)
      {
        segundos = 0;
        centesimas = 0;
        contador_2ms = 0;
        ActualizarDigitos();
      }
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
  * @brief TIM1 Initialization Function
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
  * @brief GPIO Initialization Function
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BIT_1_Pin|BIT_0_Pin, GPIO_PIN_RESET);

  /* Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, SEGMENTO_B_Pin|SEGMENTO_D_Pin|SEGMENTO_P_Pin|SEGMENTO_C_Pin
                          |SEGMENTO_G_Pin|SEGMENTO_E_Pin|SEGMENTO_A_Pin|SEGMENTO_F_Pin, GPIO_PIN_RESET);

  /* Configure GPIO pins : BIT_1_Pin BIT_0_Pin */
  GPIO_InitStruct.Pin = BIT_1_Pin|BIT_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* Configure GPIO pins : START_Pin RESET_Pin */
  GPIO_InitStruct.Pin = START_Pin|RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure GPIO pins : Segmentos A..G y DP */
  GPIO_InitStruct.Pin = SEGMENTO_B_Pin|SEGMENTO_D_Pin|SEGMENTO_P_Pin|SEGMENTO_C_Pin
                          |SEGMENTO_G_Pin|SEGMENTO_E_Pin|SEGMENTO_A_Pin|SEGMENTO_F_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
{
  if(htim->Instance == TIM1)
  {
    Display_EscribirPatron(digitos_a_mostrar[indice_pantalla], indice_pantalla);
    SeleccionarDigito(indice_pantalla);

    indice_pantalla++;
    if (indice_pantalla >= 4)
    {
      indice_pantalla = 0;
    }

    if (cronometro_corriendo)
    {
      contador_2ms++;
      if (contador_2ms >= 5)
      {
        contador_2ms = 0;
        centesimas++;
        if (centesimas >= 100)
        {
          centesimas = 0;
          segundos++;
          if (segundos >= 100)
          {
            segundos = 0;
          }
        }
        ActualizarDigitos();
      }
    }
  }
}

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

void ActualizarDigitos(void) 
{
  digitos_a_mostrar[0] = centesimas % 10;
  digitos_a_mostrar[1] = centesimas / 10;
  digitos_a_mostrar[2] = segundos % 10;
  digitos_a_mostrar[3] = segundos / 10;
}

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