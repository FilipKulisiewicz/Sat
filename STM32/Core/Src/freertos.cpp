/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <cstdio>

#include <logger.hh>
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
uint8_t TransmitBuffer[50] = {}; //virtualMaster

uint8_t ReceiveBuffer[50] = {};
Logger Log(&huart1);


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
/* Definitions for virtualMaster */
osThreadId_t virtualMasterHandle;
const osThreadAttr_t virtualMaster_attributes = {
  .name = "virtualMaster",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void BlinkLed(void *argument);
void UartLog(void *argument);
void MasterCom(void *argument);

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
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Blink */
  BlinkHandle = osThreadNew(BlinkLed, NULL, &Blink_attributes);

  /* creation of Logger */
  LoggerHandle = osThreadNew(UartLog, NULL, &Logger_attributes);

  /* creation of virtualMaster */
  virtualMasterHandle = osThreadNew(MasterCom, NULL, &virtualMaster_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_BlinkLed */
/* USER CODE END Header_BlinkLed */
void BlinkLed(void *argument)
{
	/* USER CODE BEGIN BlinkLed */
	 HAL_GPIO_TogglePin(BUILD_IN_LED_GPIO_Port, BUILD_IN_LED_Pin);
	 osDelay(1000);

	/* USER CODE END BlinkLed */
}

/* USER CODE BEGIN Header_UartLog */
/* USER CODE END Header_UartLog */
void UartLog(void *argument)
{
	/* USER CODE BEGIN UartLog */

	HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 50);


	/* USER CODE END UartLog */
}

/* USER CODE BEGIN Header_MasterCom */
/* USER CODE END Header_MasterCom */
void MasterCom(void *argument)
{
  /* USER CODE BEGIN MasterCom */
	HAL_ADC_Start(&hadc1);
	for(;;){
		if((HAL_ADC_GetValue(&hadc1) % 90) == 0)
			while((HAL_ADC_GetValue(&hadc1) % 3) != 0){
				HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"LGDT", 50);
				osDelay(100);
			}
		else{
			std::sprintf((char*)TransmitBuffer, "LL:%lu", (HAL_ADC_GetValue(&hadc1) % 1000));
			HAL_UART_Transmit_DMA(&huart1, TransmitBuffer, 50);
		}
		osDelay(1000);
	}


  /* USER CODE END MasterCom */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(Log.TakeCommand(ReceiveBuffer) == "0")
		HAL_UART_Transmit_DMA(&huart1, ReceiveBuffer, 50);
	HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 50);
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
