/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usart.h"
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
/* USER CODE BEGIN Variables */
uint8_t TransmitBuffer[10] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 34};
uint8_t ReceiveBuffer[10] = {};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Blink */
osThreadId_t BlinkHandle;
const osThreadAttr_t Blink_attributes = {
  .name = "Blink",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Logger */
osThreadId_t LoggerHandle;
const osThreadAttr_t Logger_attributes = {
  .name = "Logger",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void BlinkLed(void *argument);
void UartLog(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

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

  /* creation of Blink */
  BlinkHandle = osThreadNew(BlinkLed, NULL, &Blink_attributes);

  /* creation of Logger */
  LoggerHandle = osThreadNew(UartLog, NULL, &Logger_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_BlinkLed */
/**
* @brief Function implementing the Blink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BlinkLed */
void BlinkLed(void *argument)
{
  /* USER CODE BEGIN BlinkLed */
  /* Infinite loop */
  for(;;)
  {
	 HAL_GPIO_TogglePin(BUILD_IN_LED_GPIO_Port, BUILD_IN_LED_Pin);
	 osDelay(1000);
  }
  /* USER CODE END BlinkLed */
}

/* USER CODE BEGIN Header_UartLog */
/**
* @brief Function implementing the Logger thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UartLog */
void UartLog(void *argument)
{
  /* USER CODE BEGIN UartLog */
  /* Infinite loop */
	HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 10);
	for(;;)
	{
		HAL_UART_Transmit_DMA(&huart1, TransmitBuffer, 10);
		osDelay(1000);
	}
  /* USER CODE END UartLog */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	for(uint8_t i = 0; i < 10; ++i){
		TransmitBuffer[i]++;
	};
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 10);
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
