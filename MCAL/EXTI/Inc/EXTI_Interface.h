/*
 *@file		:	EXTI_Interface.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Functions for EXTI Peripheral
 */


#ifndef EXTI_INC_EXTI_INTERFACE_H_
#define EXTI_INC_EXTI_INTERFACE_H_

#include "EXTI_Private.h"

/***********************************
 * @function 		:	EXTI_u8Init
 * @brief			:	Initialize the required EXTI
 * @parameter[in]	:	EXTI_Configs struct {
 * 							uint8_t Trriger_Type;  (EXTI_TRRIGERTYPE_RISING_EDGE,
 * 													EXTI_TRRIGERTYPE_FALLING_EDGE,
 * 													EXTI_TRRIGERTYPE_BOTH_EDGES)
 *
 *							uint8_t State;			(EXTI_ENABLED,
 *													 EXTI_DISABLED)
 *
 *							void (*EXTI_CallBackFunction)(void);	(The desired Handler)
 *							}
 * @retval			:	Error State
 */

uint8_t EXTI_u8Init( EXTI_Configs * EXTI_CONFIGs);


/***********************************
 * @function 		:	EXTI_u8EnableINT
 * @brief			:	Enable the desired EXTI
 * @parameter[in]	:	EXTI_LINE
 * @retval			:	Error State
 */
uint8_t EXTI_u8EnableINT(EXTI_LINES EXTI_LINE);


/***********************************
 * @function 		:	EXTI_u8DisableINT
 * @brief			:	Disable the desired EXTI
 * @parameter[in]	:	EXTI_LINE
 * @retval			:	Error State
 */
uint8_t EXTI_u8DisableINT(EXTI_LINES EXTI_LINE);


/***********************************
 * @function 		:	EXTI_u8ReadPendingFlag
 * @brief			:	Read the pending flag of the required EXTI LIne
 * @parameter[in]	:	uint8_t EXTI_LINE
 * @parameter[out]	:   uint8_t Flag_State
 * @retval			:	Error State
 */
uint8_t EXTI_u8ReadPendingFlag( uint8_t	EXTI_LINE	,	uint8_t * Flag_State);


/***********************************
 * @function 		:	EXTI_u8ClearPendingFlag
 * @brief			:	Clear the pending flag of the required EXTI LIne
 * @parameter[in]	:	uint8_t EXTI_LINE
 * @retval			:	Error State
 */
uint8_t EXTI_u8ClearPendingFlag( uint8_t	EXTI_LINE);

#endif /* EXTI_INC_EXTI_INTERFACE_H_ */
