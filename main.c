/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "cmsis_os.h"

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

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
volatile uint8_t  indice_pantalla= 0;
//volatile uint8_t contador_10ms = 0;
//volatile uint8_t flag_10ms = 0;
//volatile uint8_t flag_2ms = 0;
volatile uint8_t digitos_a_mostrar[4] = {0, 0, 0, 0};
//volatile uint16_ tiempo_restante = 120;
char rx_buffer[10]={0,0,0,0,0,0,0,0,0,0};
uint8_t rx_byte = 0;
uint8_t rx_index=0;
volatile uint8_t flag_message=0;
//uint16_t centesimas = 0;
//uint8_t segundos = 0;
//uint8_t minutos = 0;
uint16_t tiempo_restante = 0;
const uint16_t TIEMPO_INICIAL = 120;
volatile bool cronometro_corriendo = false;
const osThreadAttr_t crono_attr = {
  .name = "TareaCronometro",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t botones_attr = {
  .name = "TareaBotones",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
const osThreadAttr_t uart_attr = {
	.name="TareaUART",
	.stack_size= 256*4,
	.priority = (osPriority_t) osPriorityNormal
};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_UART4_Init(void);
static void MX_TIM2_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */
void ActualizarDigitos(void);
void TareaCronometro(void* argumento);
void TareaUART(void* argumento);
void TareaBotones(void* argumento);
bool HayNuevaPulsacion(GPIO_TypeDef* PULSADOR,uint16_t PIN, GPIO_PinState* estado_valido);
void Display_EscribirPatron(uint8_t patron, uint8_t indice_pantalla);
void seleccionar(uint8_t indicepantalla);
/*bool evento_pausa(bool* ptr_cronometro_corriendo);
bool evento_start(bool* ptr_cronometro_corriendo);
void evento_reset();
void evento_status(bool cronometro_corriendo, uint16_t tiempo_actual);
void evento_set();*/


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	GPIO_PinState estado_valido1 = GPIO_PIN_SET;
	GPIO_PinState estado_valido2 = GPIO_PIN_SET;
	bool cronometro_corriendo = false;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_UART4_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);
	//HAL_UART_Transmit(&huart4, mensaje_prueba, strlen(mensaje_prueba), 100);
	HAL_UART_Receive_IT(&huart4, &rx_byte, 1);
	HAL_UART_Transmit_IT(&huart4,(uint8_t*) rx_buffer, rx_index);
	 osThreadId_t tareaCronometro =  osThreadNew(TareaCronometro, NULL, &crono_attr);
	  osThreadId_t Botones = osThreadNew(TareaBotones, NULL, &botones_attr);
	  osThreadId_t UART= osThreadNew(TareaUART, NULL, &uart_attr);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	  while (1)
	  {



	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
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

  /** Initializes the CPU, AHB and APB buses clocks
  */
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
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
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
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
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
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
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
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BIT_1_Pin|BIT_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, SEGMENTO_B_Pin|SEGMENTO_D_Pin|SEGMENTO_P_Pin|SEGMENTO_C_Pin
                          |SEGMENTO_G_Pin|SEGMENTO_E_Pin|SEGMENTO_A_Pin|SEGMENTO_F_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BIT_1_Pin BIT_0_Pin */
  GPIO_InitStruct.Pin = BIT_1_Pin|BIT_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : START_Pin PULSADOR_Pin */
  GPIO_InitStruct.Pin = START_Pin|PULSADOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEGMENTO_B_Pin SEGMENTO_D_Pin SEGMENTO_P_Pin SEGMENTO_C_Pin
                           SEGMENTO_G_Pin SEGMENTO_E_Pin SEGMENTO_A_Pin SEGMENTO_F_Pin */
  GPIO_InitStruct.Pin = SEGMENTO_B_Pin|SEGMENTO_D_Pin|SEGMENTO_P_Pin|SEGMENTO_C_Pin
                          |SEGMENTO_G_Pin|SEGMENTO_E_Pin|SEGMENTO_A_Pin|SEGMENTO_F_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void TareaUART(void *argumento)
{
	char mensaje_estado[30];
	for(;;)
	{
		if(flag_message == 1)
		{
			if(strcmp((char*)rx_buffer, "start") == 0)
			{
				// Lógica de evento_start integrada
				cronometro_corriendo = true;
				HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
			}
			else if(strcmp((char*)rx_buffer, "pause") == 0)
			{
				// Lógica de evento_pausa integrada
				cronometro_corriendo = false;
				HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
			}
			else if(strcmp((char*)rx_buffer, "status") == 0)
			{
				// Lógica de evento_status integrada
				uint8_t min = tiempo_restante / 60;
				uint8_t seg = tiempo_restante % 60;

				if (cronometro_corriendo)
				{
					sprintf(mensaje_estado, "RUNNING %02d.%02d\r\n", min, seg);
				}
				else if (tiempo_restante == 0)
				{
					sprintf(mensaje_estado, "ALARM %02d.%02d\r\n", min, seg);
				}
				else
				{
					sprintf(mensaje_estado, "PAUSED %02d.%02d\r\n", min, seg);
				}

				HAL_UART_Transmit(&huart4, (uint8_t*)mensaje_estado, strlen(mensaje_estado), 100);
			}
			else if((strncmp((char*)rx_buffer,"set ",4))==0)
			{
				int valor_recibido = atoi((char*)&rx_buffer[4]);

				// El laboratorio pide que el rango sea de 0 a 5999 segundos[cite: 5, 6]
				if (valor_recibido >= 0 && valor_recibido <= 5999)
				{
					cronometro_corriendo = false;
					tiempo_restante = (uint16_t)valor_recibido;

					// Actualizamos los dígitos inmediatamente con el nuevo valor
					ActualizarDigitos();

					HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
				}
				else
				{
					HAL_UART_Transmit(&huart4, (uint8_t*)"ERROR RANGO\r\n", 13, 100);
				}
			}
			else if(strcmp((char*)rx_buffer, "reset") == 0)
			{
			    // Si se recibe un reset por UART (opcional, pero útil)
			    cronometro_corriendo = false;
			    tiempo_restante = TIEMPO_INICIAL;
			    ActualizarDigitos();
			    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
			    HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
			}
			else
			{
				// Robustez: Tratamiento de comandos desconocidos
				HAL_UART_Transmit(&huart4, (uint8_t*)"ERROR\r\n", 7, 100);
			}

			// Limpiar variables para el próximo mensaje
			memset((char*)rx_buffer, 0, sizeof(rx_buffer));
			rx_index = 0;
			flag_message = 0;
		}

		// Bloqueo para ceder el procesador
		osDelay(pdMS_TO_TICKS(50));
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
	if(indice_pantalla==2)

	{
		HAL_GPIO_WritePin(SEGMENTO_P_GPIO_Port,SEGMENTO_P_Pin, GPIO_PIN_SET);
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
		HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
		break;
	case 6:
		HAL_GPIO_WritePin(SEGMENTO_A_GPIO_Port, SEGMENTO_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_G_GPIO_Port, SEGMENTO_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_C_GPIO_Port, SEGMENTO_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_D_GPIO_Port, SEGMENTO_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_E_GPIO_Port, SEGMENTO_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SEGMENTO_F_GPIO_Port, SEGMENTO_F_Pin, GPIO_PIN_SET);
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == htim1.Instance)
	{
		// Avisamos al main que pasaron 2 ms para que cambie la pantalla


		// Escribimos el patrón y seleccionamos el display
		Display_EscribirPatron(digitos_a_mostrar[indice_pantalla], indice_pantalla);
		seleccionar(indice_pantalla);
		indice_pantalla++;


		if (indice_pantalla >= 4)
		{
			indice_pantalla = 0;
		}

	}
}
void seleccionar(uint8_t indicepantalla)
{
	if(indicepantalla == 0)
	{
		HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_RESET);
	}else if(indicepantalla == 1)
	{
		HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_SET);
	}else if(indicepantalla == 2)
	{
		HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_RESET);
	}else if(indicepantalla == 3)
	{
		HAL_GPIO_WritePin(BIT_0_GPIO_Port, BIT_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIT_1_GPIO_Port, BIT_1_Pin, GPIO_PIN_SET);
	}
}

void TareaCronometro(void *argumento)
{
	ActualizarDigitos();
	uint32_t tick_actual = osKernelGetTickCount();
	for(;;)
	{
		if(cronometro_corriendo)
		{
			if(tiempo_restante > 0)
			{
				tiempo_restante--;
				ActualizarDigitos();
			}
			else
			{
				cronometro_corriendo = false;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); // Start para encender la alarma
			}
		}

		tick_actual += pdMS_TO_TICKS(1000);
		osDelayUntil(tick_actual);
	}
}
void TareaBotones(void *argumento)
{
	GPIO_PinState estado_start = GPIO_PIN_SET;
	GPIO_PinState estado_reset = GPIO_PIN_SET;
	for(;;)
	{
		// Corregido: Leer el puerto y pin correctos para START
		if(HayNuevaPulsacion(START_GPIO_Port, START_Pin, &estado_start))
		{
			cronometro_corriendo = !cronometro_corriendo;
		}

		// Leer el puerto y pin para RESET
		if(HayNuevaPulsacion(PULSADOR_GPIO_Port, PULSADOR_Pin, &estado_reset))
		{
			if(!cronometro_corriendo)
			{
				tiempo_restante = TIEMPO_INICIAL; // Corregido: punto y coma, no dos puntos
				ActualizarDigitos(); // Corregido: Nombre exacto de la función
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
			}
		}

		osDelay(pdMS_TO_TICKS(10)); // Corregido: typos os_Delay y TOCKS
	}
}
bool HayNuevaPulsacion(GPIO_TypeDef *puerto, uint16_t pin, GPIO_PinState *estado_valido)
{
	GPIO_PinState lectura1;
	GPIO_PinState lectura2;
	bool nueva_pulsacion = false;

	lectura1 = HAL_GPIO_ReadPin(puerto, pin);

	if(lectura1 != (*estado_valido))
	{
		osDelay(pdMS_TO_TICKS(T_REBOTE_MS)); //
		lectura2 = HAL_GPIO_ReadPin(puerto, pin);

		if(lectura2 == lectura1)
		{
			GPIO_PinState estado_anterior = *estado_valido;
			*estado_valido = lectura2;
			if((estado_anterior == GPIO_PIN_SET) && (*estado_valido == GPIO_PIN_RESET))
			{
				nueva_pulsacion = true;
			}
		}
	}
	return nueva_pulsacion;
}
void ActualizarDigitos(void) {
    uint8_t min = tiempo_restante / 60;
    uint8_t seg = tiempo_restante % 60;
    digitos_a_mostrar[3] = min / 10;
    digitos_a_mostrar[2] = min % 10;
    digitos_a_mostrar[1] = seg / 10;
    digitos_a_mostrar[0] = seg % 10;
}
/*bool evento_pausa(bool* ptr_cronometro_corriendo)
{
    *ptr_cronometro_corriendo = false; // Modificamos la variable original
    HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
    return *ptr_cronometro_corriendo;
}

bool evento_start(bool* ptr_cronometro_corriendo)
{
    *ptr_cronometro_corriendo = true; // Modificamos la variable original
    HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
    return *ptr_cronometro_corriendo;
}

void evento_reset(bool* ptr_cronometro_corriendo)
{
    *ptr_cronometro_corriendo = false;
    tiempo_restante = 0;
    centesimas = 0;

    // Limpiamos los displays
    for(uint8_t i = 0; i < 4; i++)
    {
        digitos_a_mostrar[i] = 0;
    }

    // Apagamos el PWM del buzzer (reconocimiento de alarma)[cite: 1]
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);

    HAL_UART_Transmit(&huart4, (uint8_t*)"OK\r\n", 4, 100);
}
void evento_status(bool cronometro_corriendo, uint16_t tiempo_actual)

{
    char mensaje_estado[30];
    uint8_t min = tiempo_actual / 60;
    uint8_t seg = tiempo_actual % 60;

    // El documento pide responder con el estado y el tiempo en formato MM.SS[cite: 1]
    if (cronometro_corriendo)
    {
        sprintf(mensaje_estado, "RUNNING %02d.%02d\r\n", min, seg);
    }
    else if (tiempo_actual == 0)
    {
        // Si no corre y el tiempo es 0, puede estar en alarma o reposo
        sprintf(mensaje_estado, "ALARM %02d.%02d\r\n", min, seg);
    }
    else
    {
        sprintf(mensaje_estado, "PAUSED %02d.%02d\r\n", min, seg);
    }

    HAL_UART_Transmit(&huart4, (uint8_t*)mensaje_estado, strlen(mensaje_estado), 100);
}*/


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	if(huart->Instance == UART4)
	{
		if(rx_byte!='\n'&& rx_byte!='\r')
		{
			rx_buffer[rx_index]= rx_byte;
			rx_index++;
			if(rx_index == 9)
			{
				rx_index=0;
			}
		}else if(rx_index>0)
		{
			rx_buffer[rx_index] = '\0'; // Cerramos la cadena de texto como un string de C
			flag_message = 1;
		}
		HAL_UART_Receive_IT(&huart4, &rx_byte, 1);

	}
}


/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
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
