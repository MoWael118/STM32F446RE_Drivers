/*
 *@file		:	ErrTypes.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Errors FOR STM32F446xx MCU
 */

#ifndef ERRTYPES_H_
#define ERRTYPES_H_

typedef enum  {  NOK , OK ,Null_Pointer,InvalidPORTPIN
				,WRONG_IRQ_NUM
				,WRONG_PRIORITY_GROUPING
				,WRONG_PRIORITY_NUM
				,WRONG_EXTI_LINE
				,WRONG_EXTI_STATE
				,WRONG_EXTI_TRRIGERTYPE
				,WRONG_EXTI_PORT
				,DMA_WRONG_FLAG
				,DMA_WRONG_STREAM
				,DMA_WRONG_INT_NAME
				,DMA_WRONG_INT_STATE
				,DMA_WRONG_DMA_CONTROLLER
				,DMA_WRONG_CHANNEL
				,DMA_WRONG_DATA_DIRECTION
				,DMA_WRONG_THRESHOLD_VALUE
				,DMA_WRONG_PRIORITY_LEVEL
				,DMA_WRONG_PER_INC_STATE
				,DMA_WRONG_PER_DATA_SIZE
				,DMA_WRONG_MEM_INC_STATE
				,DMA_WRONG_MEM_DATA_SIZE
				,DMA_WRONG_FIFO_MODE
				,USART_WRONG_HW_FLOW_MODE
				,USART_WRONG_OVER_SAMPLING_VALUE
				,USART_WRONG_OVER_SAMPLING_STATE
				,USART_WRONG_MODE_TYPE
				,USART_WRONG_WORD_LENGTH
				,USART_WRONG_STOP_BITS_NUMBER
				,USART_WRONG_PARITY_STATE
				,USART_WRONG_NUMBER

}Error_State_t;
#define NULL ((void *)0)

#define ENABLED 	1
#define DISABLED 	0

#endif /* ERRTYPES_H_ */
