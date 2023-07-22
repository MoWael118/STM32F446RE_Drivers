/*
 *@file		:	EXTI_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program body for EXTI Peripheral
 */

/*************************** Main Includes *******************************************/
#include <stdint.h>

#include "../../../LIBRARY/STM32F446xx.h"
#include "../../../LIBRARY/ErrTypes.h"
#include "../../../LIBRARY/BitMath.h"
#include "../Inc/EXTI_Interface.h"
/*************************************************************************************/


/*Global array of pointers to functions that will be called in the handlers*/
static void (*EXTI_pvCallBackFuncs[EXTI_IRQ_NUMBERS])(void)={NULL};

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

uint8_t EXTI_u8Init( EXTI_Configs * EXTI_CONFIGs)
{
	uint8_t ErrorState	=	OK;

	if (EXTI_CONFIGs != NULL)
	{
		if (	((EXTI_CONFIGs->EXTI_LINE)<=LINE_22)	&&	((EXTI_CONFIGs->EXTI_LINE)>=LINE_0))
		{
				/**************Set the trigger for the interrupt****************************/
				if ((EXTI_CONFIGs->EXTI_Trriger_Type	==	EXTI_TRRIGERTYPE_RISING_EDGE))
				{
					/*Deactivate Falling edge in case it was activated before*/
					EXTI->EXTI_FTSR	&=	~(1<<(EXTI_CONFIGs->EXTI_LINE));
					/*Activate the Rising edge trigger*/
					EXTI->EXTI_RTSR	|=	(1<<(EXTI_CONFIGs->EXTI_LINE));
				}
				else if ((EXTI_CONFIGs->EXTI_Trriger_Type	==	EXTI_TRRIGERTYPE_FALLING_EDGE))
				{
					/*DeActivate the Rising edge trigger*/
					EXTI->EXTI_RTSR	&=	~(1<<(EXTI_CONFIGs->EXTI_LINE));
					/*Activate Falling edge*/
					EXTI->EXTI_FTSR	|=	(1<<(EXTI_CONFIGs->EXTI_LINE));
				}
				else if ((EXTI_CONFIGs->EXTI_Trriger_Type	==	EXTI_TRRIGERTYPE_BOTH_EDGES))
				{
					/*Activate the Rising edge trigger*/
					EXTI->EXTI_RTSR	|=	(1<<(EXTI_CONFIGs->EXTI_LINE));
					/*Activate the Falling edge trigger*/
					EXTI->EXTI_FTSR	|=	(1<<(EXTI_CONFIGs->EXTI_LINE));
				}
				else
				{
					ErrorState	=	WRONG_EXTI_TRRIGERTYPE;
				}

				/******************SET the ISR Function**************************************/
				if (ErrorState!= WRONG_EXTI_TRRIGERTYPE)
				{
					if((EXTI_CONFIGs->EXTI_CallBackFunction) != NULL)
					{
						EXTI_pvCallBackFuncs[EXTI_CONFIGs->EXTI_LINE] = EXTI_CONFIGs->EXTI_CallBackFunction;
					}
					else
					{
						ErrorState	=	Null_Pointer;
					}
				}
				/*********************SET The Interrupt initial state************************/
				if ((EXTI_ENABLED	==	EXTI_CONFIGs->EXTI_State) ||(EXTI_DISABLED	==	EXTI_CONFIGs->EXTI_State) )
				{
					EXTI->EXTI_IMR |= (	 EXTI_CONFIGs->EXTI_State 	<<	(EXTI_CONFIGs->EXTI_LINE)	);
				}
				else
				{
					ErrorState	=	WRONG_EXTI_STATE;
				}
		}
		else
		{
			ErrorState	=	WRONG_EXTI_LINE;
		}
	}
	else
	{

		ErrorState = Null_Pointer;
	}
	return ErrorState;
}

/***********************************
 * @function 		:	EXTI_u8EnableINT
 * @brief			:	Enable the desired EXTI
 * @parameter[in]	:	EXTI_LINE
 * @retval			:	Error State
 */
uint8_t EXTI_u8EnableINT(EXTI_LINES EXTI_LINE)
{
	uint8_t ErrorState	=	OK	;

	if ( (EXTI_LINE	>= LINE_0)	&& (EXTI_LINE	<= LINE_22)	)
	{
		EXTI->EXTI_IMR	|=	(	1	<<	EXTI_LINE	);
	}
	else
	{
		ErrorState	=	WRONG_EXTI_LINE;
	}

	return 	ErrorState	;
}

/***********************************
 * @function 		:	EXTI_u8DisableINT
 * @brief			:	Disable the desired EXTI
 * @parameter[in]	:	EXTI_LINE
 * @retval			:	Error State
 */
uint8_t EXTI_u8DisableINT(EXTI_LINES EXTI_LINE)
{
	uint8_t ErrorState	=	OK	;

		if ( (EXTI_LINE	>= LINE_0)	&& (EXTI_LINE	<= LINE_22)	)
		{
			EXTI->EXTI_IMR	&=	( 	~ 	(1	<<	EXTI_LINE)	);
		}
		else
		{
			ErrorState	=	WRONG_EXTI_LINE;
		}

		return 	ErrorState	;
}

/***********************************
 * @function 		:	EXTI_u8ReadPendingFlag
 * @brief			:	Read the pending flag of the required EXTI LIne
 * @parameter[in]	:	uint8_t EXTI_LINE
 * @parameter[out]	:   uint8_t Flag_State
 * @retval			:	Error State
 */
uint8_t EXTI_u8ReadPendingFlag( uint8_t	EXTI_LINE	,	uint8_t * Flag_State)
{
	uint8_t ErrorState	=	OK;

	if (Flag_State	!=	NULL)
	{
		if (	(EXTI_LINE >= LINE_0)	&&	(EXTI_LINE <= LINE_22) )
		{
			*Flag_State	=	GET_BIT( (EXTI->EXTI_PR) , EXTI_LINE );
		}
		else
		{
			ErrorState	=	WRONG_EXTI_LINE;
		}
	}
	else {
		ErrorState	=	Null_Pointer;
	}

	return ErrorState;
}


/***********************************
 * @function 		:	EXTI_u8ClearPendingFlag
 * @brief			:	Clear the pending flag of the required EXTI LIne
 * @parameter[in]	:	uint8_t EXTI_LINE
 * @retval			:	Error State
 */
uint8_t EXTI_u8ClearPendingFlag( uint8_t	EXTI_LINE)
{
	uint8_t ErrorState	=	OK;

	if (	(EXTI_LINE >= LINE_0)	&&	(EXTI_LINE <= LINE_22) )
	{
		EXTI->EXTI_PR	|=	(1<<EXTI_LINE);
	}
	else
	{
		ErrorState	=	WRONG_EXTI_LINE;
	}

	return ErrorState;
}
/******************************* IRQ HANDLERS *****************************************************/

void EXTI0_IRQHandler(void)
{
	/*Clear pending flag*/
	EXTI_u8ClearPendingFlag(LINE_0);
	/*Call the CallBack Function*/
	EXTI_pvCallBackFuncs[LINE_0]();

}
void EXTI1_IRQHandler(void)
{
	/*Clear pending flag*/
	EXTI_u8ClearPendingFlag(LINE_1);
	/*Call the CallBack Function*/
	EXTI_pvCallBackFuncs[LINE_1]();
}
void EXTI2_IRQHandler(void)
{
	/*Clear pending flag*/
	EXTI_u8ClearPendingFlag(LINE_2);
	/*Call the CallBack Function*/
	EXTI_pvCallBackFuncs[LINE_2]();
}
void EXTI3_IRQHandler(void)
{
	/*Clear pending flag*/
	EXTI_u8ClearPendingFlag(LINE_3);
	/*Call the CallBack Function*/
	EXTI_pvCallBackFuncs[LINE_3]();
}
void EXTI4_IRQHandler(void)
{
	/*Clear pending flag*/
	EXTI_u8ClearPendingFlag(LINE_4);
	/*Call the CallBack Function*/
	EXTI_pvCallBackFuncs[LINE_4]();
}
void EXTI9_5_IRQHandler(void)
{
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_5	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_5]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_5);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_5]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_6	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_6]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_6);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_6]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_7	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_7]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_7);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_7]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_8	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_8]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_8);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_8]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_9	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_9]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_9);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_9]();
		}
	}

}
void EXTI15_10_IRQHandler(void)
{
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_10	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_10]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_10);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_10]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_11	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_11]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_11);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_11]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_12	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_12]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_12);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_12]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_13	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_13]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_13);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_13]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_14	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_14]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_14);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_14]();
		}
	}
	if (	GET_BIT( (EXTI->EXTI_PR)	,	LINE_15	)	)
	{
		if (EXTI_pvCallBackFuncs[LINE_15]!=NULL)
		{
			/*Clear pending flag*/
			EXTI_u8ClearPendingFlag(LINE_15);

			/*Call the CallBack Function*/
			EXTI_pvCallBackFuncs[LINE_15]();
		}
	}
}


