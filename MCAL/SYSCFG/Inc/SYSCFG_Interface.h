/*
 *@file		:	SYSCFG_Interface.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Functions for SYSCFG Peripheral
 */
#ifndef SYSCFG_INC_SYSCFG_INTERFACE_H_
#define SYSCFG_INC_SYSCFG_INTERFACE_H_

#include "SYSCFG_Private.h"

/***********************************
 * @function 		:	SYSCFG_u8SetEXTIPort
 * @brief			:	select the source input for the EXTIx external interrupt.
 * @parameter[in]	:	uint8_t EXTI_LINE	,	uint8_t EXTI_PORT
 * @retval			:	Error State
 */
uint8_t SYSCFG_u8SetEXTIPort(uint8_t EXTI_LINE, uint8_t	EXTI_PORT);

#endif /* SYSCFG_INC_SYSCFG_INTERFACE_H_ */
