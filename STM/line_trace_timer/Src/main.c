/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2018 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

#define START_LASER_MIN 100
#define START_LASER_MAX 200
#define GOAL_LASER_MIN 120
#define GOAL_LASER_MAX 200

#define SET_START_ZONE 		(StartLaserValue > START_LASER_MIN && StartLaserValue < START_LASER_MAX)
#define RESET_START_ZONE	(StartLaserValue > START_LASER_MAX)
#define SET_GOAL_ZONE 		(GoalLaserValue > GOAL_LASER_MIN && GoalLaserValue < GOAL_LASER_MAX)
#define RESET_GOAL_ZONE		(GoalLaserValue > GOAL_LASER_MAX)

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 *
 * @retval None
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

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
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	MX_SPI2_Init();
	MX_CAN_Init();
	MX_USART3_UART_Init();
	MX_ADC1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	uint32_t ts = 0;
	uint32_t sendDataTs = 0;

	uint8_t txData;

	uint8_t waitStartFlag = 0;
	uint32_t startFlag = 0;
	uint32_t goalFlag = 0;

	uint32_t com_ts = 0;

	initCAN();

	uint32_t requestDataStartTs = HAL_GetTick();
	uint32_t requestDataGoalTs = HAL_GetTick() + 10;

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		if (ts < HAL_GetTick()) {
			LED0_TOGGLE;
			if (goalFlag) {
				ts = HAL_GetTick() + 20;
			} else if (startFlag) {
				ts = HAL_GetTick() + 100;
			} else if (waitStartFlag) {
				ts = HAL_GetTick() + 500;
			} else {
				ts = HAL_GetTick() + 1000;
			}

		}

		if (com_ts < HAL_GetTick()) {
			com_ts = HAL_GetTick() + 500;
			txData = 0x01;
			HAL_UART_Transmit(&huart3, &txData, 1, 10);
		}

		if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE)) {
			//Receive Start
			uint8_t rxData;
			HAL_UART_Receive(&huart3, &rxData, 1, 50);
			if (rxData == 0x10) {
				NVIC_SystemReset();
			}

		}

		if (requestDataStartTs < HAL_GetTick()) {
			requestDistance(0);
			requestDataStartTs = HAL_GetTick() + 20;
		}

		if (requestDataGoalTs < HAL_GetTick()) {
			requestDistance(1);
			requestDataGoalTs = HAL_GetTick() + 20;
		}

		if (checkCanRx()) {

		}

		if (sendDataTs < HAL_GetTick()) {
			if (SET_START_ZONE && waitStartFlag == 0 && startFlag == 0) {
				waitStartFlag = 1;
				txData = 0x02;
				HAL_UART_Transmit(&huart3, &txData, 1, 10);
			}

			if (RESET_START_ZONE && waitStartFlag == 1 && startFlag == 0) {
				waitStartFlag = 0;
				startFlag = 1;
			}

			if (startFlag) {
				if (startFlag++ < 200) {
					txData = 0x03;
					HAL_UART_Transmit(&huart3, &txData, 1, 10);
				} else {
					startFlag = 400;
				}

			}

			if (SET_GOAL_ZONE && startFlag > 200) {
				txData = 0x04;
				HAL_UART_Transmit(&huart3, &txData, 1, 10);
				goalFlag = 1;
			}

			if (IS_SW0_PUSHED && startFlag) {
				startFlag = 0;
				txData = 0x04;
				HAL_UART_Transmit(&huart3, &txData, 1, 10);
				goalFlag = 1;
			}

			if (goalFlag) {
				if (goalFlag++ < 10) {
					txData = 0x04;
					HAL_UART_Transmit(&huart3, &txData, 1, 10);
				} else {
					NVIC_SystemReset();
					goalFlag = 100;
				}
				startFlag = 0;
			}

//			if (IS_FOT2_ACTED && waitStartFlag == 0 && startFlag == 0) {
//				waitStartFlag = 1;
//				txData = 0x02;
//				HAL_UART_Transmit(&huart3, &txData, 1, 10);
//			}
//
//			if (IS_NOT_FOT2_ACTED && waitStartFlag == 1 && startFlag == 0) {
//				waitStartFlag = 0;
//				startFlag = 1;
//			}
//
//			if (startFlag) {
//				if (startFlag++ < 10) {
//					txData = 0x03;
//					HAL_UART_Transmit(&huart3, &txData, 1, 10);
//				} else {
//					startFlag = 100;
//				}
//
//			}
//
//			if (IS_FOT1_ACTED && startFlag) {
//				txData = 0x04;
//				HAL_UART_Transmit(&huart3, &txData, 1, 10);
//				goalFlag = 1;
//			}
//
//			if (IS_SW0_PUSHED && startFlag) {
//				startFlag = 0;
//				txData = 0x04;
//				HAL_UART_Transmit(&huart3, &txData, 1, 10);
//				goalFlag = 1;
//			}
//
//			if (goalFlag) {
//				if (goalFlag++ < 10) {
//					txData = 0x04;
//					HAL_UART_Transmit(&huart3, &txData, 1, 10);
//				} else {
//					NVIC_SystemReset();
//					goalFlag = 100;
//				}
//				startFlag = 0;
//			}

			sendDataTs = HAL_GetTick() + 20;
		}

//		if (IS_FOT2_ACTED) {
//			LED1_ON;
//		} else {
//			LED1_OFF;
//		}
//		if (IS_FOT1_ACTED) {
//			LED2_ON;
//		} else {
//			LED2_OFF;
//		}

		if (SET_START_ZONE) {
			LED1_ON;
		} else {
			LED1_OFF;
		}
		if (SET_GOAL_ZONE) {
			LED2_ON;
		} else {
			LED2_OFF;
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  file: The file name as string.
 * @param  line: The line in file as a number.
 * @retval None
 */
void _Error_Handler(char *file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
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
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
