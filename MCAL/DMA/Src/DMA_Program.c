/*
 *@file		:	DMA_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program body for DMA Peripheral
 */

/******************* MAIN INCLUDES *********************/
#include <stdint.h>
#include "../../../LIBRARY/STM32F446xx.h"
#include "../../../LIBRARY/ErrTypes.h"
#include "../Inc/DMA_Interface.h"
/*******************************************************/


/********************** MAIN PV ************************/
static DMA_REG_t * DMA[DMA_CONTROLLERS] = {DMA1,DMA2};

/*2D Array of pointers to the call back functions */
static void (*DMA_CALL_BACK_FUNCTIONS[DMA_CONTROLLERS][STREAMS_IRQs])(void)={NULL};
/*******************************************************/


/****************** MAIN FUNCTIONS *********************/

/*
 * @function 		:	DMA_ReadINT_Flag
 * @brief			:	Read the desired interrupt flag state
 * @param			:	Variable to save the flag state
 * @param			:	Flag type
 * @param			:	STREAM Number
 * @retval			:	Error State
 */
Error_State_t DMA_ReadINT_Flag(DMA_NUMBER_t	DMA_Num , uint8_t * Flag_Val ,FLAG_TYPES_t FLAG_Type , STREAM_NUMBERS_t StreamNum )
{
	Error_State_t Error_State = OK;

	/*Check The given variable isn't NULL*/
	if (NULL != Flag_Val)
	{
		/*Check DMA Controller number*/
		if ((DMA_Num >=DMA_1)	&& (DMA_Num <=DMA_2))
		{
			/*Check Stream Number*/
			if ( (StreamNum>=STREAM0) && (StreamNum<=STREAM7))
			{
				/*Check if the flag is valid*/
				if ((FLAG_Type >=DMA_TC_FLAG)	&&	(FLAG_Type <=DMA_FE_FLAG))
				{
					/*Check Which stream to determine it's Register*/
					if(StreamNum<=STREAM3)
					{
						/*If the stream between 0 and 3 ,Access Low Register*/

						/*Variable to determine the flag bit place*/
						uint8_t ROW =StreamNum/2;

						/*Equation to achieve flag bit value*/
						*Flag_Val = (DMA[DMA_Num]->LISR >>(((6*StreamNum+5)+(4*ROW))-FLAG_Type));
					}
					else
					{
						/*if the stream between 4 and 7 access High Register*/

						/*Variable to determine the flag place*/
						uint8_t ROW =(StreamNum%4)/2;

						/*Equation to achieve flag bit value*/
						*Flag_Val = (DMA[DMA_Num]->HISR >>(((6*(StreamNum%4)+5)+(4*ROW))-FLAG_Type));
					}
				}
				else
				{
					Error_State	=	DMA_WRONG_FLAG;
				}
			}
			else
			{
				Error_State	=	DMA_WRONG_STREAM;
			}
		}
		else {
			Error_State = DMA_WRONG_DMA_CONTROLLER;
		}
	}
	else
	{
		Error_State	=	Null_Pointer;
	}

	return Error_State;
}


/*
 * @function 		:	DMA_ClearINT_Flag
 * @brief			:	CLEAR the desired interrupt flag state
 * @param			:	Flag type
 * @param			:	STREAM Number
 * @retval			:	Error State
 */
Error_State_t DMA_ClearINT_Flag(DMA_NUMBER_t DMA_Num , FLAG_TYPES_t FLAG_Type , STREAM_NUMBERS_t StreamNum )
{
	Error_State_t Error_State = OK;

	/*Check DMA Controller number*/
	if ((DMA_Num >=DMA_1)	&& (DMA_Num <=DMA_2))
	{
		/*Check Stream Number*/
		if ( (StreamNum>=STREAM0) && (StreamNum<=STREAM7))
		{
			/*Check if the flag is valid*/
			if ((FLAG_Type >=DMA_TC_FLAG)	&&	(FLAG_Type <=DMA_FE_FLAG))
			{
				/*Check Which stream to determine it's Register*/
				if(StreamNum<=STREAM3)
				{
					/*If the stream between 0 and 3 ,Access Low Register*/

					/*Variable to determine the flag bit place*/
					uint8_t ROW =StreamNum/2;

					/*Equation to achieve flag bit value*/
					DMA[DMA_Num]->LIFCR =( 1<<((	(6*StreamNum+5)	+	(4*ROW)	) - FLAG_Type	));
				}
				else
				{
					/*if the stream between 4 and 7 access High Register*/

					/*Variable to determine the flag place*/
					uint8_t ROW =(StreamNum%4)/2;

					/*Equation to achieve flag bit value*/
					DMA[DMA_Num]->HIFCR = (1 <<(((6*(StreamNum%4)+5)+(4*ROW))-FLAG_Type));
				}
			}
			else
			{
				Error_State	=	DMA_WRONG_FLAG;
			}
		}
		else
		{
			Error_State	=	DMA_WRONG_STREAM;
		}
	}
	else {
		Error_State = DMA_WRONG_DMA_CONTROLLER;
	}

	return Error_State;
}



/*
 * @function 		:	DMA_Init
 * @brief			:	initialize the DMA
 * @param			:	Structure of DMA Configurations
 * @retval			:	Error State
 * @warning 		:	Memory to Memory Data direction can only be achieved in DMA1
 */
Error_State_t DMA_Init(const DMA_Config_t * DMA_CONFIGs)
{
	Error_State_t Error_State = OK;

	if (OK == DMA_CheckConfig(DMA_CONFIGs))
	{
		/* 1- Set Channel Number */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~((CHANNELS_MASK)<<CHANNEL_BITS_START);/*Clear the previous channels */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=  ((DMA_CONFIGs->ChannelNum)<<CHANNEL_BITS_START);/*SET the channel */

		/* 2- Set Priority Level */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~ ((PRIORITY_MASK)<<PRIORITY_BITS_START);
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=	((DMA_CONFIGs->Priority_Level)<<PRIORITY_BITS_START);

		/* 3- Set Data Transfer Direction */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~ ((DIRECTION_MASK)<<(DIRECTION_BITS_START));
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=   ((DMA_CONFIGs->DATA_Direction)<<(DIRECTION_BITS_START));

		/* 4- Set Memory address Increment state*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~ ((MINC_MASK)<<(MINC_BITS_START));
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=   ((DMA_CONFIGs->MemInc_state)<<(MINC_BITS_START));

		/* 5- Set Peripheral address Increment state*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~ ((PINC_MASK)<<(PINC_BITS_START));
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=   ((DMA_CONFIGs->PerInc_state)<<(PINC_BITS_START));

		/* 6- Set Memory Data Size */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~ ((MSIZE_MASK)<<(MSIZE_BITS_START));
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=   ((DMA_CONFIGs->MemDataSize)<<(MSIZE_BITS_START));

		/* 7- Set Peripheral Data Size*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] &= ~ ((PSIZE_MASK)<<(PSIZE_BITS_START));
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |=   ((DMA_CONFIGs->PerDataSize)<<(PSIZE_BITS_START));

		/* 8- Set FIFO Buffer Mode*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_FCR] &= ~ ((DMDIS_MASK)<<(DMDIS_BITS_START));
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_FCR] |=   ((DMA_CONFIGs->FIFO_Mode)<<(DMDIS_BITS_START));

		/* 9- Set threshold value if FIFO mode is selected*/
		if (FIFO_MODE == (DMA_CONFIGs->FIFO_Mode))
		{
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_FCR] &= ~ ((THRESHOLD_MASK)<<(THRESHOLD_BITS_START));
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_FCR] |=   ((DMA_CONFIGs->Threshold_Value)<<(THRESHOLD_BITS_START));
		}
	}
	else
	{
		Error_State = DMA_CheckConfig(DMA_CONFIGs) ;
	}

	return Error_State;
}
/*
 * @function 		:	DMA_Set_INT_State
 * @brief			:	Set the desired DMA Interrupt state
 * @param			:	DMA Number
 * @param			:	STREAM Number
 * @param			: 	Interrupt Name
 * @param			:	Interrupt state
 * @retval			:	Error State
 */

Error_State_t DMA_Set_INT_State(DMA_NUMBER_t DMA_Num , STREAM_NUMBERS_t StreamNum , DMA_INTs_NAMES_t INT_Name , DMA_INT_STATE_t INT_State)
{
	Error_State_t Error_State = OK;
	/*Check DMA Number*/
	if ((DMA_Num == DMA_1) || (DMA_Num == DMA_2))
	{
		/*	Check Stream Number*/
		if ( (StreamNum>=STREAM0) && (StreamNum<=STREAM7))
		{
			/*Check given Interrupt Name*/
			if ((INT_Name>=DME_INT) && (INT_Name<=TC_INT) )
			{
				/*Check Given Interrupt state*/
				if ((INT_State == DMA_INT_ENABLE )	||	(INT_State == DMA_INT_DISABLE ))
				{
					/*Set the desired state to the Corresponding Interrupt*/
					DMA[DMA_Num]->STREAM[StreamNum][Sx_CR]	&=	~ ((IE_MASK)<<(INT_Name));
					DMA[DMA_Num]->STREAM[StreamNum][Sx_CR]	|=	  ((INT_State)<<(INT_Name));
				}
				else
				{
					Error_State	=	DMA_WRONG_INT_STATE;
				}
			}
			/*Check Given Interrupt NAME*/
			else if (FE_INT	==	INT_Name)
			{
				/*Check Given Interrupt state*/
				if ((INT_State == DMA_INT_ENABLE )	||	(INT_State == DMA_INT_DISABLE ))
				{
					/*Set the desired state to the Corresponding Interrupt*/
					DMA[DMA_Num]->STREAM[StreamNum][Sx_FCR] &= ~ ((IE_MASK)<<(FEIE_BITS_START));
					DMA[DMA_Num]->STREAM[StreamNum][Sx_FCR] |=   ((INT_State)<<(FEIE_BITS_START));
				}
				else
				{
					Error_State	=	DMA_WRONG_INT_STATE;
				}

			}
			else
			{
				Error_State	=	DMA_WRONG_INT_NAME;
			}
		}
		else {
			Error_State	=	DMA_WRONG_STREAM;
		}
	}
	else {
		Error_State	=	DMA_WRONG_DMA_CONTROLLER;
	}

	return Error_State;
}


/*
 * @function 		:	DMA_Start_Transfer
 * @brief			:	Start data transfer by DMA
 * @param			:  	Structure of DMA Configurations
 * @param			:  	Source address to transfer from.
 * @param			:  	Destination address to transfer into.
 * @param			: 	length of data to be transfered.
 * @retval			:	Error State
 * @warning			: 	This Function must be called after initializing the DMA
 */

Error_State_t DMA_Start_Transfer(const DMA_Config_t * DMA_CONFIGs, uint32_t Src_Address , uint32_t Dest_Address , uint16_t Data_Length)
{
	Error_State_t	Error_State = OK;

	/*Check Data Transfer Direction*/
	if (DMA_CONFIGs->DATA_Direction == MEMORY_TO_PERIPHERAL)
	{
		/* 1- Set the Source address */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_M0AR] = Src_Address;

		/* 2- Set the Destination address*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_PAR] = Dest_Address;

		/* 3- Set the desired data length to be transferred*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_NDTR] = (uint32_t)Data_Length;

		/* 4- Start the transfer*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |= ENABLED ;
	}
	else if ((DMA_CONFIGs->DATA_Direction == PERIPHERAL_TO_MEMORY) || (DMA_CONFIGs->DATA_Direction == MEMORY_TO_MEMORY) )
	{
		/* 1- Set the Source address */
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_PAR] = Src_Address;

		/* 2- Set the Destination address*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_M0AR] = Dest_Address;

		/* 3- Set the desired data length to be transferred*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_NDTR] = (uint32_t)Data_Length;

		/* 4- Start the transfer*/
		DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |= ENABLED ;
	}


	return Error_State	;
}

/*
 * @function 		:	DMA_Start_Transfer_IT
 * @brief			:	Start data transfer by DMA With interrupt after transfer complete
 * @param			:  	Structure of DMA Configurations
 * @param			:  	Source address to transfer from.
 * @param			:  	Destination address to transfer into.
 * @param			: 	length of data to be transfered.
 * @retval			:	Error State
 * @warning			: 	This Function must be called after initializing the DMA
 */

Error_State_t DMA_Start_Transfer_IT(const DMA_Config_t * DMA_CONFIGs, uint32_t Src_Address , uint32_t Dest_Address , uint16_t Data_Length ,void (*DMA_CallBack)(void))
{
	Error_State_t	Error_State = OK;

	/*Check Call back Function*/
	if (NULL != DMA_CallBack)
	{
		/*Check Data Transfer Direction*/
		if (DMA_CONFIGs->DATA_Direction == MEMORY_TO_PERIPHERAL)
		{
			/* 1- Set the Source address */
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_M0AR] = Src_Address;

			/* 2- Set the Destination address*/
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_PAR] = Dest_Address;

			/* 3- Set the desired data length to be transferred*/
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_NDTR] = (uint32_t)Data_Length;

			/* 4- Set the call back function*/
			DMA_CALL_BACK_FUNCTIONS[DMA_CONFIGs->DMA_Num][DMA_CONFIGs->StreamNum] = DMA_CallBack;

			/* 5- Enable Transfer complete interrupt*/
			DMA_Set_INT_State(DMA_CONFIGs->DMA_Num, DMA_CONFIGs->StreamNum, TC_INT, ENABLED);

			/* 6- Start the transfer*/
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |= ENABLED ;

		}
		else if ((DMA_CONFIGs->DATA_Direction == PERIPHERAL_TO_MEMORY) || (DMA_CONFIGs->DATA_Direction == MEMORY_TO_MEMORY) )
		{
			/* 1- Set the Source address */
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_PAR] = Src_Address;

			/* 2- Set the Destination address*/
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_M0AR] = Dest_Address;

			/* 3- Set the desired data length to be transferred*/
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_NDTR] = (uint32_t)Data_Length;

			/* 4- Set the call back function*/
			DMA_CALL_BACK_FUNCTIONS[DMA_CONFIGs->DMA_Num][DMA_CONFIGs->StreamNum] = DMA_CallBack;

			/* 5- Enable Transfer complete interrupt*/
			DMA_Set_INT_State(DMA_CONFIGs->DMA_Num, DMA_CONFIGs->StreamNum, TC_INT, ENABLED);

			/* 6- Start the transfer*/
			DMA[DMA_CONFIGs->DMA_Num]->STREAM[DMA_CONFIGs->StreamNum][Sx_CR] |= ENABLED ;

		}

	}
	else {
		Error_State	= Null_Pointer;
	}
	return Error_State	;
}

/**************** End of MAIN FUNCTIONS ******************/



/***************** STATIC FUNCTIONS ********************/

static Error_State_t DMA_CheckConfig(DMA_Config_t * DMA_Configs)
{
	Error_State_t Error_State = OK;

	/*Check on null pointer*/
	if (DMA_Configs != NULL)
	{
		/*Check on Channel Number*/
		if ( (DMA_Configs->ChannelNum >= CHANNEL0) && (DMA_Configs->ChannelNum <= CHANNEL7) )
		{
			/*CHECK ON DATA Direction*/
			if ((DMA_Configs->DATA_Direction >=PERIPHERAL_TO_MEMORY)&&(DMA_Configs->DATA_Direction <=MEMORY_TO_MEMORY))
			{
				/*Check on DMA Number*/
				if ((DMA_Configs->DMA_Num >=DMA_1)&&(DMA_Configs->DMA_Num <=DMA_2))
				{
					/*Check on Buffer Mode */
					if ((DMA_Configs->FIFO_Mode >=DIRECT_MODE)&&(DMA_Configs->FIFO_Mode <=FIFO_MODE))
					{
						/*Check on Memory data size*/
						if ((DMA_Configs->MemDataSize >=MEM_DATA_SIZE_ONE_BYTE)&&(DMA_Configs->MemDataSize <=MEM_DATA_SIZE_WORD))
						{
							/*Check on Memory pointer increment state*/
							if ((DMA_Configs->MemInc_state == MEMORY_ADDRESS_FIXED) || (DMA_Configs->MemInc_state ==MEMORY_ADDRESS_INCREMENTING))
							{
								/*Check on PERIPHERAL data size*/
								if ( (DMA_Configs->PerDataSize >=PER_DATA_SIZE_ONE_BYTE) && (DMA_Configs->PerDataSize <=PER_DATA_SIZE_WORD) )
								{
									/*Check on Peripheral pointer increment state*/
									if ((DMA_Configs->PerInc_state == PERIPHERAL_ADDRESS_FIXED) || (DMA_Configs->PerInc_state ==PERIPHERAL_ADDRESS_INCREMENTING))
									{
										/*Check on Priority level*/
										if ((DMA_Configs->Priority_Level >= PRIORITY_LOW) && (DMA_Configs->Priority_Level <= PRIORITY_VERY_HIGH))
										{
											/*Check on Stream Number*/
											if ((DMA_Configs->StreamNum >= STREAM0)&&(DMA_Configs->StreamNum <= STREAM7))
											{
												/*Check on Threshold value*/
												if (((DMA_Configs->Threshold_Value >=ONE_QUARTER_FULL_FIFO)&&(DMA_Configs->Threshold_Value <=FULL_FIFO)) || (DMA_Configs->FIFO_Mode ==DIRECT_MODE))
												{
													/*No Errors on the given Configurations*/
													Error_State = OK;
												}
												else
												{
													/*Wrong Threshold value*/
													Error_State = DMA_WRONG_THRESHOLD_VALUE;
												}
											}
											else {
												/*Error Wrong Priority Level */
												Error_State = DMA_WRONG_STREAM;
											}
										}
										else {
											/*Error Wrong Priority Level */
											Error_State = DMA_WRONG_PRIORITY_LEVEL;
										}
									}
									else
									{
										/*Error Wrong PERIPHERAL INC State */
										Error_State = DMA_WRONG_PER_INC_STATE;
									}
								}
								else
								{
									/*Error Wrong PERIPHERAL DATA SIZE */
									Error_State = DMA_WRONG_PER_DATA_SIZE;
								}
							}
							else
							{
								/*Error Wrong MEMORY INC State */
								Error_State = DMA_WRONG_MEM_INC_STATE;
							}
						}
						else {
							/*Error Wrong MEMORY DATA SIZE */
							Error_State = DMA_WRONG_MEM_DATA_SIZE;
						}
					}
					else
					{
						/*Error Wrong FIFO Buffer Mode*/
						Error_State = DMA_WRONG_FIFO_MODE;
					}
				}
				else
				{
					/*Error Wrong DMA Number*/
					Error_State = DMA_WRONG_DMA_CONTROLLER;
				}

			}
			else {
				/*Wrong Data Direction*/
				Error_State = DMA_WRONG_DATA_DIRECTION;
			}
		}
		else {
			/*Error Wrong Channel Number */
			Error_State = DMA_WRONG_CHANNEL;
		}
	}
	else
	{
		Error_State	=	Null_Pointer;
	}

	return Error_State;
}
/************** End of STATIC FUNCTIONS ****************/


/*************** DMA IRQ HANDLERS *********************/
void DMA1_Stream0_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM0);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM0])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM0]();
	}
}

void DMA1_Stream1_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM1);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM1])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM1]();
	}
}

void DMA1_Stream2_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM2);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM2])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM2]();
	}
}

void DMA1_Stream3_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM3);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM3])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM3]();
	}
}

void DMA1_Stream4_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM4);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM4])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM4]();
	}
}

void DMA1_Stream5_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM5);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM5])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM5]();
	}
}

void DMA1_Stream6_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM6);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM6])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM6]();
	}
}

void DMA1_Stream7_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_1, DMA_TC_FLAG, STREAM7);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM7])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_1][STREAM7]();
	}
}

void DMA2_Stream0_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM0);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM0])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM0]();
	}
}

void DMA2_Stream1_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM1);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM1])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM1]();
	}
}

void DMA2_Stream2_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM2);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM2])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM2]();
	}
}

void DMA2_Stream3_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM3);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM3])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM3]();
	}
}

void DMA2_Stream4_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM4);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM4])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM4]();
	}
}

void DMA2_Stream5_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM5);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM5])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM5]();
	}
}

void DMA2_Stream6_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM6);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM6])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM6]();
	}
}

void DMA2_Stream7_IRQHandler (void)
{
	/*Clear Transfer complete flag*/
	DMA_ClearINT_Flag(DMA_2, DMA_TC_FLAG, STREAM7);
	/*Check the call back Function not NULL*/
	if (NULL != DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM7])
	{
		DMA_CALL_BACK_FUNCTIONS[DMA_2][STREAM7]();
	}
}
/************** End of DMA IRQ HANDLERS ***************/

