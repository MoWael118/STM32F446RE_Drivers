/*
 *@file		:	SYSCFG_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program body for SYSCFG Peripheral
 */

#include <stdint.h>

#include "../../../LIBRARY/STM32F446xx.h"
#include "../../../LIBRARY/ErrTypes.h"
#include "../../../LIBRARY/BitMath.h"
#include "../Inc/SYSCFG_Interface.h"

/***********************************
 * @function 		:	SYSCFG_u8SetEXTIPort
 * @brief			:	select the source input for the EXTIx external interrupt.
 * @parameter[in]	:	uint8_t EXTI_LINE	,	uint8_t EXTI_PORT
 * @retval			:	Error State
 */
uint8_t SYSCFG_u8SetEXTIPort(uint8_t EXTI_LINE, uint8_t	EXTI_PORT)
{
	uint8_t ErrorState = OK	;

	if(	(EXTI_LINE	<=	22))
	{
		if (EXTI_PORT <=EXTI_PortH)
		{
			SYSCFG->SYSCFG_EXTICR[EXTI_LINE/4]	&=	~(EXTI_PORT_MASK <<((EXTI_LINE%4)*4));

			SYSCFG->SYSCFG_EXTICR[EXTI_LINE/4]	|=	(EXTI_PORT <<((EXTI_LINE%4)*4))		;
		}
		else
		{
			ErrorState	=	WRONG_EXTI_PORT;
		}
	}
	else
	{
		ErrorState	=	WRONG_EXTI_LINE;
	}

	return 	ErrorState	;
}
