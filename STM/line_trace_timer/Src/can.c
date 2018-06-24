/**
 ******************************************************************************
 * File Name          : CAN.c
 * Description        : This file provides code for the configuration
 *                      of the CAN instances.
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
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
static void setCanSidFilter(CAN_HandleTypeDef *_hcan_, uint16_t mask_sid,
		uint16_t filter_sid);

CanTxMsgTypeDef txMessage;
CanRxMsgTypeDef rxMessage;

uint16_t StartLaserValue;
uint16_t GoalLaserValue;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void) {

	hcan.Instance = CAN1;
	hcan.Init.Prescaler = 2;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SJW = CAN_SJW_1TQ;
	hcan.Init.BS1 = CAN_BS1_14TQ;
	hcan.Init.BS2 = CAN_BS2_3TQ;
	hcan.Init.TTCM = DISABLE;
	hcan.Init.ABOM = DISABLE;
	hcan.Init.AWUM = DISABLE;
	hcan.Init.NART = DISABLE;
	hcan.Init.RFLM = DISABLE;
	hcan.Init.TXFP = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle) {

	GPIO_InitTypeDef GPIO_InitStruct;
	if (canHandle->Instance == CAN1) {
		/* USER CODE BEGIN CAN1_MspInit 0 */

		/* USER CODE END CAN1_MspInit 0 */
		/* CAN1 clock enable */
		__HAL_RCC_CAN1_CLK_ENABLE()
		;

		/**CAN GPIO Configuration
		 PA11     ------> CAN_RX
		 PA12     ------> CAN_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN CAN1_MspInit 1 */

		/* USER CODE END CAN1_MspInit 1 */
	}
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle) {

	if (canHandle->Instance == CAN1) {
		/* USER CODE BEGIN CAN1_MspDeInit 0 */

		/* USER CODE END CAN1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_CAN1_CLK_DISABLE();

		/**CAN GPIO Configuration
		 PA11     ------> CAN_RX
		 PA12     ------> CAN_TX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

		/* USER CODE BEGIN CAN1_MspDeInit 1 */

		/* USER CODE END CAN1_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
void initCAN() {
	//Set filter

	setCanSidFilter(&hcan, 0, 0);
	//Set buffer
	hcan.pTxMsg = &txMessage;
	hcan.pRxMsg = &rxMessage;
}

static void setCanSidFilter(CAN_HandleTypeDef *_hcan_, uint16_t mask_sid,
		uint16_t filter_sid) {
	static uint8_t bankNum;
	CAN_FilterConfTypeDef filterConfig;
	uint16_t mskSid = 0x07ff;
	mask_sid &= mskSid;
	filter_sid &= mskSid;

	filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	filterConfig.FilterIdHigh = (uint32_t) filter_sid << 5;
	filterConfig.FilterIdLow = 0x0000;
	filterConfig.FilterMaskIdHigh = (uint32_t) mask_sid << 5;
	filterConfig.FilterMaskIdLow = 0x0000;
	filterConfig.FilterFIFOAssignment = 0;
	filterConfig.FilterActivation = ENABLE;
	filterConfig.BankNumber = 14;

	filterConfig.FilterNumber = bankNum++;
	HAL_CAN_ConfigFilter(&hcan, &filterConfig);
}

uint8_t checkCanRx() {
	//CANメッセージがあるか確認して存在する場合のみ処理する
	if (__HAL_CAN_MSG_PENDING(&hcan, CAN_FIFO0) != 0U) {
		HAL_CAN_Receive(&hcan, CAN_FIFO0, 10);

		switch (getSender(rxMessage.StdId)) {
		case ID_LASER_START:
			StartLaserValue = CAN_Decode_Short(rxMessage.Data);
			print("S %d\n\r", StartLaserValue);
			LED1_TOGGLE;
			break;

		case ID_LASER_GOAL:
			GoalLaserValue = CAN_Decode_Short(rxMessage.Data);
			print("G %d\n\r", GoalLaserValue);
			LED2_TOGGLE;
			break;
		}

		return 1;
	} else {
		return 0;
	}
}

void requestDistance(int num) {
	CanTxMsgTypeDef txData;
	txData.IDE = CAN_ID_STD;

	if (num == 0)
		txData.StdId = createSid(NORMAL_TYPE, ID_MAIN, ID_LASER_START);
	else
		txData.StdId = createSid(NORMAL_TYPE, ID_MAIN, ID_LASER_GOAL);

	txData.RTR = CAN_RTR_REMOTE;
	hcan.pTxMsg = &txData;

	HAL_CAN_Transmit(&hcan, 10);
}

/******************************************************************************************
 * @function  	:createMsg
 * @explain	    :11bitメッセージ作成関数
 * @parameter 	[uint8_t](type)送信するデータの型。canmacro内で定義
 * @parameter 	[uint8_t](sender)送り主
 * @parameter 	[uint8_t](destination)宛先
 * @return		[uint16_t]作成したSID
 * @caution	    (MSB:宛先(4bit)、送り主(4bit)、データ型(3bit):LSB)で格納
 *****************************************************************************************/
uint16_t createSid(uint8_t type, uint8_t sender, uint8_t destination) {
	uint16_t msg = 0;

	type &= 0x07;
	sender &= 0x0f;
	destination &= 0x0f;

	msg = ((uint16_t) destination << 7);
	msg += ((uint16_t) sender << 3);
	msg += type;
	return msg;
}

/******************************************************************************************
 * @function  	:Get_Type
 * @explain	    :メッセージからデータ型を取り出す
 * @parameter 	[uint16_t](receive_msg)受信したSID
 * @return		[uint8_t]抽出したデータ型
 * @caution	    Create_MSGで作成したものに使用する
 *****************************************************************************************/
uint8_t getType(uint16_t receive_msg) {
	return (receive_msg & (0b0000000000000111));
}

/******************************************************************************************
 * @function  	:Get_Sender
 * @explain	    :メッセージから送り主を取り出す
 * @parameter 	[uint16_t](receive_msg)受信したSID
 * @return		[uint8_t]抽出した送り主
 * @caution	    Create_MSGで作成したものに使用する
 *****************************************************************************************/
uint8_t getSender(uint16_t receive_msg) {
	return ((receive_msg & (0b0000000001111000)) >> 3);
}

/******************************************************************************************
 * @function  	:Get_Destination
 * @explain	    :メッセージから宛先を取り出す
 * @parameter 	[uint16_t](receive_msg)受信したSID
 * @return		[uint8_t]抽出した宛先
 * @caution	    Create_MSGで作成したものに使用する
 *****************************************************************************************/
uint8_t getDestination(uint16_t receive_msg) {
	return ((receive_msg & (0b0000011110000000)) >> 7);
}

/******************************************************************************************
 * @function  	:CAN_Encode_Short
 * @explain	    :uint16_t型データをCAN用のuint8_t型データに変換する関数
 * @parameter 	[uint16_t](integer1)変換したいuint16_t型のデータ
 * @parameter	[uint8_t](*send_buf)変換したデータを格納する送信用データバッファ
 * @caution	    CAN_Decode_Shortでデコードする必要がある
 *****************************************************************************************/
void CAN_Encode_Short(uint16_t integer, uint8_t *send_buf) {
	send_buf[0] = integer & 0xff;
	send_buf[1] = (integer >> 8) & 0xff;
}

/******************************************************************************************
 * @function  	:CAN_Decode_Short
 * @explain	    :CAN用のuint8_t型データをuint16_t型に変換する関数
 * @parameter	[uint8_t](*receive_buf)受信したデータバッファ
 * @caution	    CAN_Encode_Shortでエンコードしたものに使う
 *****************************************************************************************/
uint16_t CAN_Decode_Short(uint8_t *receive_buf) {
	uint16_t org_data;
	org_data = receive_buf[0];
	org_data |= receive_buf[1] << 8;
	return org_data;
}
/* USER CODE END 1 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
