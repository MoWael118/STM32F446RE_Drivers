/*
 *@file		:	NVIC_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program for NVIC peripheral
 */

#include <stdint.h>
#include "../../../LIBRARY/ErrTypes.h"
#include "../../../LIBRARY/STM32F446xx.h"
#include "../Inc/NVIC_Interface.h"
#include "../Inc/NVIC_Private.h"

/***********************************
 * @function 		:	NVIC_u8EnableInt
 * @brief			:	Enable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8EnableInt(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;

	return Error_State;
}

/***********************************
 * @function 		:	NVIC_u8DisableInt
 * @brief			:	Disable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8DisableInt(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;

		return Error_State;
}


/***********************************
 * @function 		:	NVIC_u8SetPendFlag
 * @brief			:	Set the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8SetPendFlag(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;

		return Error_State;
}


/***********************************
 * @function 		:	NVIC_u8ClearPendFlag
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8ClearPendFlag(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;

		return Error_State;
}


/***********************************
 * @function 		:	NVIC_u8ReadActiveFlag
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @parameter[out]  :   Flag_Value (Active Flag Value)
 * @retval			:	Error State
 */

uint8_t NVIC_u8ReadActiveFlag(uint8_t IRQ_Num,uint8_t * Flag_Value)
{
	uint8_t Error_State = OK;

		return Error_State;
}
