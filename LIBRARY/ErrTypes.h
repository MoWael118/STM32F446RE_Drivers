/*
 *@file		:	ErrTypes.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Errors FOR STM32F446xx MCU
 */

#ifndef ERRTYPES_H_
#define ERRTYPES_H_

enum ErrorState {  NOK , OK ,Null_Pointer,InvalidPORTPIN
				,WRONG_IRQ_NUM
				,WRONG_PRIORITY_GROUPING
				,WRONG_PRIORITY_NUM
				,WRONG_EXTI_LINE
				,WRONG_EXTI_STATE
				,WRONG_EXTI_TRRIGERTYPE
				,WRONG_EXTI_PORT};
#define NULL ((void *)0)

#endif /* ERRTYPES_H_ */
