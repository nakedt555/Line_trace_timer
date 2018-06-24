/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED0_ON 		(HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET))
#define LED0_OFF 		(HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET))
#define LED0_TOGGLE 	(HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin))
#define LED1_ON 		(HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET))
#define LED1_OFF 		(HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET))
#define LED1_TOGGLE 	(HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin))
#define LED2_ON 		(HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET))
#define LED2_OFF 		(HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET))
#define LED2_TOGGLE 	(HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin))

#define SW0_STATE 		(HAL_GPIO_ReadPin(SW0_GPIO_Port, SW0_Pin))
#define IS_SW0_PUSHED	(SW0_STATE == 0)
#define SW1_STATE 		(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin))
#define IS_SW1_PUSHED	(SW1_STATE == 0)

#define FOT0_STATE 		(HAL_GPIO_ReadPin(FOT0_GPIO_Port, FOT0_Pin))
#define IS_FOT0_ACTED	(FOT0_STATE == 1)
#define FOT1_STATE 		(HAL_GPIO_ReadPin(FOT1_GPIO_Port, FOT1_Pin))
#define IS_FOT1_ACTED	(FOT1_STATE == 1)
#define FOT2_STATE 		(HAL_GPIO_ReadPin(FOT2_GPIO_Port, FOT2_Pin))
#define IS_FOT2_ACTED	(FOT2_STATE == 0)
#define FOT3_STATE 		(HAL_GPIO_ReadPin(FOT3_GPIO_Port, FOT3_Pin))
#define IS_FOT3_ACTED	(FOT3_STATE == 0)

#define IS_NOT_FOT0_ACTED	(FOT0_STATE == 0)
#define IS_NOT_FOT1_ACTED	(FOT1_STATE == 0)
#define IS_NOT_FOT2_ACTED	(FOT2_STATE == 1)
#define IS_NOT_FOT3_ACTED	(FOT3_STATE == 1)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
