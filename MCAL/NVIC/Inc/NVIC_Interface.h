/*
 *@file		:	NVIC_Interafce.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for NVIC peripheral
 */
#ifndef NVIC_INC_NVIC_INTERFACE_H_
#define NVIC_INC_NVIC_INTERFACE_H_

#include "NVIC_Private.h"
/***********************************
 * @function 		:	NVIC_u8EnableIRQ
 * @brief			:	Enable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8EnableIRQ(uint8_t IRQ_Num);

/***********************************
 * @function 		:	NVIC_u8DisableIRQ
 * @brief			:	Disable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8DisableIRQ(uint8_t IRQ_Num);


/***********************************
 * @function 		:	NVIC_u8SetPendingIRQ
 * @brief			:	Set the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8SetPendingIRQ(uint8_t IRQ_Num);


/***********************************
 * @function 		:	NVIC_u8ClearPendingIRQ
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8ClearPendingIRQ(uint8_t IRQ_Num);


/***********************************
 * @function 		:	NVIC_u8ReadActiveFlag
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @parameter[out]  :   Flag_Value (Active Flag Value)
 * @retval			:	Error State
 */

uint8_t NVIC_u8GetActiveIRQ(uint8_t IRQ_Num,uint8_t * Flag_Value);



#endif /* NVIC_INC_NVIC_INTERFACE_H_ */
