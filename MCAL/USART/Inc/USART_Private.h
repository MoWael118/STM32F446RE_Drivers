/*
 *@file		:	USART_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Privates for USART peripheral
 */


#ifndef USART_INC_USART_PRIVATE_H_
#define USART_INC_USART_PRIVATE_H_


/***************** STATIC FUNCTIONS ********************/

/*
 * @function 		:	USART_Check_Configs
 * @brief			:	Private Function To Check Passed USART Configurations
 * @param			:	USART_Configs
 * @retval			:	Error State
 */
static Error_State_t USART_Check_Configs(const USART_CONFIGS_t * USART_Configs);

/*
 * @function 		:	USART_SetBaudRate
 * @brief			:	Private Function To Calculate the BaudRate and assign it to the register
 * @param			:	BaudRate_Value, The Desired baud rate value
 * @param			:	Clock_Value, The applied clock on the USARTx Peripheral
 * @param			:	OVER_SAMPLE_VALUE, the Applied OverSampling rate
 * @param			:	USART_Num, The Enabled USART Number
 * @retval			:	Error State
 */
static void USART_SetBaudRate(uint32_t BaudRate_Value , uint32_t Clock_Value , uint32_t OVER_SAMPLE_VALUE ,USART_NUMBER_t USART_Num);

/*
 * @function 		:	USART_SetBaudRate
 * @brief			:	Private Function To the Different Sources of the IRQ
 * @param			:	USART_Num, The Enabled USART Number
 * @retval			:	Error State
 */
static void USART_IRQ_Source_HANDLE(USART_NUMBER_t USART_Num);
/************** End of STATIC FUNCTIONS ****************/


/*****************Private Defines***********************/
#define USART_APB2_NUMBER	2
#define USART_APB1_NUMBER	4

#define PARITY_BIT_MASK		1u
#define PARITY_BIT_START	10u

#define PARITY_TYPE_MASK	1u
#define PARITY_TYPE_START	9u

#define STOP_BITS_MASK		3u
#define STOP_BITS_START 	12u

#define WORD_LENGTH_BIT_MASK	1u
#define WORD_LENGTH_BIT_START	12u

#define TX_BIT_START		3u
#define RX_BIT_START		2u

#define OVERSAMPLING_STATE_BIT_START 11u

#define OVERSAMPLING_VALUE_BIT_START 15u

#define CTS_BIT_START		9u
#define RTS_BIT_START		8u

#define USART_ENABLE_BIT_START 13u

#define USART_MAX_NUMBERS		6u
#define	USART_MAX_INTERRUPTS	9u

#define NO_SOURCE				0u
#define SOURCE_TxD				1u
#define SOURCE_RxD				2u
#define SOURCE_TxB				3u
#define SOURCE_RxB				4u

#define DMAR_ENABLE				6u
#define DMAT_ENABLE				7u


#endif /* USART_INC_USART_PRIVATE_H_ */
