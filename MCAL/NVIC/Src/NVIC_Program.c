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
 * @function 		:	NVIC_u8EnableIRQ
 * @brief			:	Enable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8EnableIRQ(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;

	if (IRQ_Num >=0 && IRQ_Num<97)
	{
		/*Set (Enable) The Corresponding IRQ Bit*/
		NVIC->NVIC_ISER[IRQ_Num/32] = (1<<(IRQ_Num%32));
	}
	else
	{
		Error_State = WRONG_IRQ_NUM;
	}
	return Error_State;
}

/***********************************
 * @function 		:	NVIC_u8DisableIRQ
 * @brief			:	Disable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8DisableIRQ(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;
	if (IRQ_Num >=0 && IRQ_Num<97)
	{
		/*Set (Disable) The Corresponding IRQ Bit*/
		NVIC->NVIC_ICER[IRQ_Num/32] = (1<<(IRQ_Num%32));
	}
	else
	{
		Error_State = WRONG_IRQ_NUM;
	}
	return Error_State;
}


/***********************************
 * @function 		:	NVIC_u8SetPendingIRQ
 * @brief			:	Set the Interrupt State into Pending for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8SetPendingIRQ(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;

	if (IRQ_Num >=0 && IRQ_Num<97)
	{
		/*Set (Enable) The Corresponding IRQ Bit*/
		NVIC->NVIC_ISPR[IRQ_Num/32] = (1<<(IRQ_Num%32));
	}
	else
	{
		Error_State = WRONG_IRQ_NUM;
	}
	return Error_State;
}


/***********************************
 * @function 		:	NVIC_u8ClearPendingIRQ
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8ClearPendingIRQ(uint8_t IRQ_Num)
{
	uint8_t Error_State = OK;
	if (IRQ_Num >=0 && IRQ_Num<97)
	{
		/*Set (CLear Pending) The Corresponding IRQ Bit*/
		NVIC->NVIC_ICPR[IRQ_Num/32] = (1<<(IRQ_Num%32));
	}
	else
	{
		Error_State = WRONG_IRQ_NUM;
	}
	return Error_State;
}


/***********************************
 * @function 		:	NVIC_u8GetActiveIRQ
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @parameter[out]  :   Flag_Value (Active Flag Value)
 * @retval			:	Error State
 */

uint8_t NVIC_u8GetActiveIRQ(uint8_t IRQ_Num,uint8_t * Flag_Value)
{
	uint8_t Error_State = OK;
	if (IRQ_Num >=0 && IRQ_Num<97)
	{
		/*Get The Corresponding IRQ Bit State*/
		*Flag_Value = ((NVIC->NVIC_IABR[IRQ_Num/32]>>(IRQ_Num%32))&1);
	}
	else
	{
		Error_State = WRONG_IRQ_NUM;
	}
	return Error_State;
}
