/*
 *@file		:	USART_Interface.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Functions for USART peripheral
 */


#ifndef USART_INC_USART_INTERFACE_H_
#define USART_INC_USART_INTERFACE_H_

/******************* MAIN INCLUDES *********************/
#include <stdint.h>
#include "../../../LIBRARY/ErrTypes.h"
/*******************************************************/


/************** MAIN USER DEFINED VARIABLES ************/

/*
 * @enum For USART NUMBERS
 *
 */
typedef enum {

	USART_NUMBER_USART2,
	USART_NUMBER_USART3,
	USART_NUMBER_UART4,
	USART_NUMBER_UART5,
	USART_NUMBER_USART1,
	USART_NUMBER_USART6

}USART_NUMBER_t;

/*
 * @enum For PARITY STATE
 *
 */
typedef enum {
	PARITY_STATE_NO_PARITY,
	PARITY_STATE_PARITY_ENABLED,
}PARITY_STATE_t;

/*
 * @enum For PARITY Types
 *
 */
typedef enum {
	PARITY_TYPE_EVEN,
	PARITY_TYPE_ODD
}PARITY_TYPE_t;

/*
 * @enum For Stop bits Number
 *
 */
typedef enum {
	STOP_BITS_ONE_BIT,
	STOP_BITS_HALF_BIT,
	STOP_BITS_TWO_BIT,
	STOP_BITS_ONE_HALF_BIT,
}STOP_BITS_NUMBER_t;

/*
 * @enum For Word Lengths
 *
 */
typedef enum {
	WORD_LENGTH_8BITS,
	WORD_LENGTH_9BITS,
}WORD_LENGTH_SIZE_t;

/*
 * @enum For Mode Types
 *
 */
typedef enum {
	MODE_TYPE_RX,
	MODE_TYPE_TX,
	MODE_TYPE_RXandTX,
}MODE_TYPE_t;

/*
 * @enum For OVERSAMPLING_STATE_t
 *
 */
typedef enum {
	OVERSAMPLING_STATE_THREE_SAMPLES,
	OVERSAMPLING_STATE_ONE_SAMPLE
}OVERSAMPLING_STATE_t;

/*
 * @enum For OVERSAMPLING_VALUE_t
 *
 */
typedef enum {
	OVERSAMPLING_VALUE_OVER16,
	OVERSAMPLING_VALUE_OVER8
}OVERSAMPLING_VALUE_t;

/*
 * @enum For HW_FLOW_CONTROL_MODE_t
 *
 */
typedef enum {
	HW_FLOW_CONTROL_MODE_DISABLED,
	HW_FLOW_CONTROL_MODE_ENABELD
}HW_FLOW_CONTROL_MODE_t;



/*
 * @enum For USART_FLAGS
 *
 */
typedef enum {
	USART_FLAG_PARITY_ERROR,
	USART_FLAG_FRAMING_ERROR,
	USART_FLAG_NOISE_DETECTED,
	USART_FLAG_OVERRUN_ERROR,
	USART_FLAG_IDLE_LINE_DETECTED,
	USART_FLAG_RXNE,
	USART_FLAG_TC,
	USART_FLAG_TXE,
	USART_FLAG_LBD,
	USART_FLAG_CTS
}USART_FLAGS_t;

/*
 * @enum For USART_INTERRUPTS_t
 *
 */
typedef enum {
	USART_INTERRUPT_EIE,
	USART_INTERRUPT_IDLEIE=4,
	USART_INTERRUPT_RXNEIE,
	USART_INTERRUPT_TCIE,
	USART_INTERRUPT_TXEIE,
	USART_INTERRUPT_PEIE,
	USART_INTERRUPT_CTSIE=10
}USART_INTERRUPTS_t;

/*
 * @enum For USART_CALLBACKs_t
 *
 */
typedef enum {
	USART_CALLBACKS_EI,
	USART_CALLBACKS_IDLEI,
	USART_CALLBACKS_RXNEI,
	USART_CALLBACKS_TCI,
	USART_CALLBACKS_TXEI,
	USART_CALLBACKS_PEI,
	USART_CALLBACKS_CTSI
}USART_CALLBACKs_t;

/*
 * @struct For USART_CONFIGS_t
 *
 */
typedef struct {

	USART_NUMBER_t     		USART_Num;
	PARITY_STATE_t 	   		Parity_State;
	PARITY_TYPE_t			Parity_Type;
	STOP_BITS_NUMBER_t 		StopBits_Num;
	WORD_LENGTH_SIZE_t 		Word_Length;
	MODE_TYPE_t		   		Mode_Type;
	uint32_t 		   		BaudRate_Value;
	uint32_t				USART_Clock_Value;
	OVERSAMPLING_STATE_t	OverSampling_State;
	OVERSAMPLING_VALUE_t	OverSampling_Value;
	HW_FLOW_CONTROL_MODE_t  HWFlow_Control_Mode;


}USART_CONFIGS_t;

/******** END OF MAIN USER DEFINED VARIABLES ***********/


/****************** MAIN FUNCTIONS *********************/

/*
 * @function 		:	USART_Init
 * @brief			:	initialize the USART
 * @param			:	Structure of USART Configurations
 * @retval			:	Error State
 */
Error_State_t USART_Init(const USART_CONFIGS_t * USART_Configs);

/*
 * @function 		:	USART_SendCharPolling
 * @brief			:	Send character using USART
 * @param			:	USART NUMBER
 * @param			:	Character
 * @retval			:	Error State
 */
Error_State_t USART_SendCharPolling(USART_NUMBER_t USART_Num , uint8_t Character);

/*
 * @function 		:	USART_SendStringPolling
 * @brief			:	Send String using USART
 * @param			:	USART NUMBER
 * @param			:	String
 * @retval			:	Error State
 */
Error_State_t USART_SendStringPolling(USART_NUMBER_t USART_Num , const char* String);


/*
 * @function 		:	USART_ReceiveCharPolling
 * @brief			:	Receive character using USART
 * @param			:	USART NUMBER
 * @param			:	variable to hold Character
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveCharPolling(USART_NUMBER_t USART_Num , uint16_t * Character);

/*
 * @function 		:	USART_ReceiveBUFFERPolling
 * @brief			:	Receive Buffer (Several Bytes) of data
 * @param			:	USART NUMBER
 * @param			:	Receiving_Buffer
 * @param			: 	Buffer Size (Received data size)
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveBUFFERPolling(USART_NUMBER_t USART_Num , uint16_t * Receiving_Buffer ,uint16_t Buffer_Size);


/*
 * @function 		:	USART_SendCharWithIT
 * @brief			:	Send character using USART and generate interrupt when Transmission is complete
 * @param			:	USART NUMBER
 * @param			:	Character
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_SendCharIT(USART_NUMBER_t USART_Num , uint8_t Character ,void (*TC_CallBackFunc)(void));


/*
 * @function 		:	USART_SendBufferIT
 * @brief			:	Send Buffer (Several bytes) using USART and
 * 						generate interrupt when Buffer Transmission is complete
 * @param			:	USART NUMBER
 * @param			:	Data Buffer
 * @param			:	Buffer Size (amount of data to be transferred)
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_SendBufferIT(USART_NUMBER_t USART_Num , uint8_t * Data_Buffer ,uint16_t Buffer_Size,void (*TC_CallBackFunc)(void));


/*
 * @function 		:	USART_ReceiveCharIT
 * @brief			:	Receive character using USART and generate interrupt when Receiving is complete
 * @param			:	USART NUMBER
 * @param			:	variable to save Character
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveCharIT(USART_NUMBER_t USART_Num , uint8_t* Character ,void (*TC_CallBackFunc)(void));


/*
 * @function 		:	USART_ReceiveBufferIT
 * @brief			:	Receive Buffer (Several bytes) using USART and
 * 						generate interrupt when Buffer Receiving is complete
 * @param			:	USART NUMBER
 * @param			:	variable to save the Data Buffer
 * @param			:	Buffer Size (amount of data to be transferred)
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveBufferIT(USART_NUMBER_t USART_Num , uint8_t * Data_Buffer ,uint16_t Buffer_Size,void (*RC_CallBackFunc)(void));

/*
 * @function 		:	USART_Enable_DMA_RX
 * @brief			:	Enable DMA RX Line for the required USART
 * @param			:	USART NUMBER
 * @retval			:	Error State
 */
Error_State_t USART_Enable_DMA_RX(USART_NUMBER_t USART_Num);

/*
 * @function 		:	USART_Enable_DMA_TX
 * @brief			:	Enable DMA TX Line for the required USART
 * @param			:	USART NUMBER
 * @retval			:	Error State
 */
Error_State_t USART_Enable_DMA_TX(USART_NUMBER_t USART_Num);

/***************End of MAIN FUNCTIONS*******************/



#endif /* USART_INC_USART_INTERFACE_H_ */
