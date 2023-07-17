/*
 *@file		:	SCB_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program for SCB peripheral
 */

#include <stdint.h>
#include "../../../LIBRARY/ErrTypes.h"
#include "../../../LIBRARY/STM32F446xx.h"
#include "../Inc/SCB_Interface.h"

/***********************************
 * @function 		:	SCB_u8SetPriorityGrouping
 * @brief			:	Set the number of Groups and Subgroups
 * @parameter[in]	:	GroupingType (number of Groups and Subgroups)
 * @retval			:	Error State
 */

uint8_t SCB_u8SetPriorityGrouping( GROUP_TYPES_t GroupingType)
{
	uint8_t 	ErrorState= OK;
	uint32_t 	VectKey = 0x05FA0000 ;
	if ((GroupingType == SCBGT_G16_S0))
	{
		VectKey |= (GroupingType<<PRIGROUP);
		SCB->SCB_AIRCR = VectKey;
	}
	else if	((GroupingType >= SCBGT_G8_S2)&&(GroupingType <= SCBGT_G0_S16))
	{
		VectKey |= (GroupingType<<PRIGROUP);
		SCB->SCB_AIRCR = VectKey;
	}
	else
	{
		ErrorState = WRONG_PRIORITY_GROUPING;
	}

	return ErrorState;
}
