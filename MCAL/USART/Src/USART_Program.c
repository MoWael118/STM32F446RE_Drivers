/*
 *@file		:	USART_Program.c
 *@author	: 	Mohamed Wael
 *@brief	:	Main Program body for USART Peripheral
 */

/******************* MAIN INCLUDES *********************/
#include <stdint.h>
#include "../../../LIBRARY/STM32F446xx.h"
#include "../../../LIBRARY/ErrTypes.h"
#include "../../../LIBRARY/BitMath.h"
#include "../Inc/USART_Interface.h"
#include "../Inc/USART_Private.h"

/*******************************************************/

/********************** MAIN PV ************************/

/*USART1 and USART6 Registers array*/
static USART_REG_t * USART_APB2[USART_APB2_NUMBER]={USART1,USART6};

/*USART2,USART3,UART4,UART5 Registers array*/
static USART_REG_t * USART_APB1[USART_APB1_NUMBER]={USART2,USART3,UART4,UART5};

/*2D array of USARTs Call back functions*/
static void (*USART_pf_CallBackFuncs[USART_MAX_NUMBERS][USART_MAX_INTERRUPTS])(void)={NULL};

/*Array To define Different IRQ Sources for the USARTs*/
uint8_t IRQ_Source[USART_MAX_NUMBERS]={NO_SOURCE};

/*Variable to Save the Data buffer size globally*/
static uint16_t Global_Data_Size=0;

/*Variable to Save the Data buffer globally*/
static uint8_t* Global_Data_Buffer=NULL;

/*Variable to Save the Received globally*/
static uint8_t* Global_Received_Data=NULL;

/*******************************************************/

/****************** MAIN FUNCTIONS *********************/

/*
 * @function 		:	USART_Init
 * @brief			:	initialize the USART
 * @param			:	Structure of USART Configurations
 * @retval			:	Error State
 */
Error_State_t USART_Init(const USART_CONFIGS_t * USART_Configs)
{
	Error_State_t Error_State = OK;

	/*Check USART Configurations*/
	if (OK == USART_Check_Configs(USART_Configs))
	{
		/*Check USART number to access its Registers*/
		if ((USART_Configs->USART_Num >= USART_NUMBER_USART2)&&(USART_Configs->USART_Num <= USART_NUMBER_UART5))
		{
			/*Enable USART*/
			USART_APB1[USART_Configs->USART_Num]->USART_CR1 |= (1<<USART_ENABLE_BIT_START);
			/*1- Set Parity State*/
			USART_APB1[USART_Configs->USART_Num]->USART_CR1 &= ~(PARITY_BIT_MASK<<PARITY_BIT_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (USART_Configs->Parity_State<<PARITY_BIT_START);
			/*2- Set Parity type if Parity state is enabled*/
			if (USART_Configs->Parity_State == PARITY_STATE_PARITY_ENABLED)
			{
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 &= ~(PARITY_TYPE_MASK<<PARITY_TYPE_START);
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (USART_Configs->Parity_Type<<PARITY_TYPE_START);
			}
			/*3- Set Stop bits Number*/
			USART_APB1[USART_Configs->USART_Num]->USART_CR2 &= ~(STOP_BITS_MASK<<STOP_BITS_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR2 |=  (USART_Configs->StopBits_Num<<STOP_BITS_START);
			/*4- Set Word Length Size*/
			USART_APB1[USART_Configs->USART_Num]->USART_CR1 &= ~(WORD_LENGTH_BIT_MASK<<WORD_LENGTH_BIT_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (USART_Configs->Word_Length<<WORD_LENGTH_BIT_START);
			/*5- Set Mode Type*/
			if (USART_Configs->Mode_Type == MODE_TYPE_RX)
			{
				/*Disable TX Circuit*/
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 &= ~(1<<TX_BIT_START);
				/*Enable RX Circuit*/
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 |= (1<<RX_BIT_START);
			}
			else if (USART_Configs->Mode_Type == MODE_TYPE_TX)
			{
				/*Enable TX Circuit*/
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (1<<TX_BIT_START);
				/*Disable RX Circuit*/
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 &= ~(1<<RX_BIT_START);
			}
			else if (USART_Configs->Mode_Type == MODE_TYPE_RXandTX){
				/*Enable TX Circuit*/
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (1<<TX_BIT_START);
				/*Disable RX Circuit*/
				USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (1<<RX_BIT_START);
			}
			/*6- Set OverSampling state*/

			USART_APB1[USART_Configs->USART_Num]->USART_CR3 &= ~(1<<OVERSAMPLING_STATE_BIT_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR3 |=  (USART_Configs->OverSampling_State<<OVERSAMPLING_STATE_BIT_START);

			/*7- Set OverSampling Value*/

			USART_APB1[USART_Configs->USART_Num]->USART_CR1 &= ~(1<<OVERSAMPLING_VALUE_BIT_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR1 |=  (USART_Configs->OverSampling_Value<<OVERSAMPLING_VALUE_BIT_START);

			/*8- Set HW Flow control mode state*/
			/*set CTS*/
			USART_APB1[USART_Configs->USART_Num]->USART_CR3 &= ~(1<<CTS_BIT_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR3 |= (USART_Configs->HWFlow_Control_Mode<<CTS_BIT_START);
			/*set RTS*/
			USART_APB1[USART_Configs->USART_Num]->USART_CR3 &= ~(1<<RTS_BIT_START);
			USART_APB1[USART_Configs->USART_Num]->USART_CR3 |= (USART_Configs->HWFlow_Control_Mode<<RTS_BIT_START);
		}
		else if ((USART_Configs->USART_Num == USART_NUMBER_USART1)||(USART_Configs->USART_Num == USART_NUMBER_USART6))
		{
			/*Enable USART*/
			USART_APB2[USART_Configs->USART_Num-4]->USART_CR1 |= (1<<USART_ENABLE_BIT_START);
			/*1- Set Parity State*/
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 &= ~(PARITY_BIT_MASK<<PARITY_BIT_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (USART_Configs->Parity_State<<PARITY_BIT_START);
			/*2- Set Parity type if Parity state is enabled*/
			if (USART_Configs->Parity_State == PARITY_STATE_PARITY_ENABLED)
			{
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 &= ~(PARITY_TYPE_MASK<<PARITY_TYPE_START);
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (USART_Configs->Parity_Type<<PARITY_TYPE_START);
			}
			/*3- Set Stop bits Number*/
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR2 &= ~(STOP_BITS_MASK<<STOP_BITS_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR2 |=  (USART_Configs->StopBits_Num<<STOP_BITS_START);
			/*4- Set Word Length Size*/
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 &= ~(WORD_LENGTH_BIT_MASK<<WORD_LENGTH_BIT_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (USART_Configs->Word_Length<<WORD_LENGTH_BIT_START);
			/*5- Set Mode Type*/
			if (USART_Configs->Mode_Type == MODE_TYPE_RX)
			{
				/*Disable TX Circuit*/
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 &= ~(1<<TX_BIT_START);
				/*Enable RX Circuit*/
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |= (1<<RX_BIT_START);
			}
			else if (USART_Configs->Mode_Type == MODE_TYPE_TX)
			{
				/*Enable TX Circuit*/
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (1<<TX_BIT_START);
				/*Disable RX Circuit*/
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 &= ~(1<<RX_BIT_START);
			}
			else if (USART_Configs->Mode_Type == MODE_TYPE_RXandTX){
				/*Enable TX Circuit*/
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (1<<TX_BIT_START);
				/*ENABLE RX Circuit*/
				USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (1<<RX_BIT_START);
			}
			/*6- Set OverSampling state*/

			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR3 &= ~(1<<OVERSAMPLING_STATE_BIT_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR3 |=  (USART_Configs->OverSampling_State<<OVERSAMPLING_STATE_BIT_START);

			/*7- Set OverSampling Value*/

			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 &= ~(1<<OVERSAMPLING_VALUE_BIT_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR1 |=  (USART_Configs->OverSampling_Value<<OVERSAMPLING_VALUE_BIT_START);

			/*8- Set HW Flow control mode state*/
			/*set CTS*/
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR3 &= ~(1<<CTS_BIT_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR3 |= (USART_Configs->HWFlow_Control_Mode<<CTS_BIT_START);
			/*set RTS*/
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR3 &= ~(1<<RTS_BIT_START);
			USART_APB2[(USART_Configs->USART_Num)-4]->USART_CR3 |= (USART_Configs->HWFlow_Control_Mode<<RTS_BIT_START);

		}
		/*9- Set Baud Rate*/
		USART_SetBaudRate((USART_Configs->BaudRate_Value), (USART_Configs->USART_Clock_Value),(USART_Configs->OverSampling_Value),(USART_Configs->USART_Num));
	}
	else {
		Error_State = USART_Check_Configs(USART_Configs);
	}

	return Error_State	;
}

/*
 * @function 		:	USART_SendCharPolling
 * @brief			:	Send character using USART
 * @param			:	Character
 * @retval			:	Error State
 */
Error_State_t USART_SendCharPolling(USART_NUMBER_t USART_Num , uint8_t Character)
{
	Error_State_t Error_State=OK;

	if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
	{
		/*wait till DR is Empty*/
		while (!(GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TXE)));
		/*Store data in the DR Register*/
		USART_APB1[USART_Num]->USART_DR = Character;
		/*wait till Transmission is complete*/
		while (!(GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TC)));
	}
	else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
	{
		/*wait till DR is Empty*/
		while (!(GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_TXE)));
		/*Store data in the DR Register*/
		USART_APB2[USART_Num-4]->USART_DR = Character;
		/*wait till Transmission is complete*/
		while (!(GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_TC)));
	}
	else {
		Error_State = USART_WRONG_NUMBER;
	}


	return Error_State ;
}

/*
 * @function 		:	USART_SendStringPolling
 * @brief			:	Send String using USART
 * @param			:	String
 * @retval			:	Error State
 */
Error_State_t USART_SendStringPolling(USART_NUMBER_t USART_Num , const char* String)
{
	Error_State_t Error_State = OK;
	uint16_t Counter=0;
	if (NULL != String)
	{
		while (String[Counter] != '\0')
		{
			if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
			{
				/*wait till DR is Empty*/
				while (!(GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TXE)));
				/*Store data in the DR Register*/
				USART_APB1[USART_Num]->USART_DR = String[Counter];
				/*wait till Transmission is complete*/
				while (!(GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TC)));
			}
			else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
			{
				/*wait till DR is Empty*/
				while (!(GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_TXE)));
				/*Store data in the DR Register*/
				USART_APB2[USART_Num-4]->USART_DR = String[Counter];
				/*wait till Transmission is complete*/
				while (!(GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_TC)));
			}
			else {
				Error_State = USART_WRONG_NUMBER;
				break;
			}
			Counter++;
		}
	}
	else {
		Error_State = Null_Pointer;
	}
	return Error_State ;
}

/*
 * @function 		:	USART_ReceiveCharPolling
 * @brief			:	Receive character using USART
 * @param			:	USART NUMBER
 * @param			:	variable to hold Character
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveCharPolling(USART_NUMBER_t USART_Num , uint16_t * Character)
{
	Error_State_t Error_State = OK;
	if (NULL != Character)
	{
		if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
		{
			/*Wait till the Received data is ready to be read*/
			while (!GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_RXNE));

			/*Read the data*/
			*Character = USART_APB1[USART_Num]->USART_DR;
		}
		else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
		{
			/*Wait till the Received data is ready to be read*/
			while (!GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_RXNE));

			/*Read the data*/
			*Character = USART_APB2[USART_Num-4]->USART_DR;
		}
		else {
			Error_State = USART_WRONG_NUMBER;
		}
	}
	else {
		Error_State = Null_Pointer;
	}
	return Error_State;
}

/*
 * @function 		:	USART_ReceiveBUFFERPolling
 * @brief			:	Receive Buffer (Several Bytes) of data
 * @param			:	USART NUMBER
 * @param			:	Receiving_Buffer to receive the data
 * @param 			:	Buffer Size (Received data size)
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveBUFFERPolling(USART_NUMBER_t USART_Num , uint16_t * Receiving_Buffer ,uint16_t Buffer_Size)
{

	Error_State_t Error_State = OK;
	uint8_t Counter=0;
	if (NULL != Receiving_Buffer)
	{
		while (Counter<Buffer_Size)
		{
			if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
			{
				/*Wait until first word (8 bits or 9 bits) received*/
				while (!GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_RXNE));

				/*Read the first word*/
				Receiving_Buffer[Counter]= USART_APB1[USART_Num]->USART_DR;
			}
			else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
			{
				/*Wait until first word (8 bits or 9 bits) received*/
				while (!GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_RXNE));

				/*Read the first word*/
				Receiving_Buffer[Counter]= USART_APB2[USART_Num-4]->USART_DR;

			}
			else {
				Error_State = USART_WRONG_NUMBER;
				break;
			}
		}
	}
	else {
		Error_State = Null_Pointer;
	}
	return Error_State ;

}

/*
 * @function 		:	USART_SendCharWithIT
 * @brief			:	Send character using USART and generate interrupt when Transmission is complete
 * @param			:	USART NUMBER
 * @param			:	Character
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_SendCharIT(USART_NUMBER_t USART_Num , uint8_t Character ,void (*TC_CallBackFunc)(void))
{
	Error_State_t Error_State = OK;

	uint8_t Flag_State = 0 ;


	if (NULL != TC_CallBackFunc)
	{
		/*Set Call Back Globally*/
		USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_TCI]= TC_CallBackFunc ;

		/*Set IRQ Source for the Given USART*/
		IRQ_Source[USART_Num] = SOURCE_TxD;

		/*Check Which USART is selected*/
		if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
		{
			/*wait till Transmit data register is empty*/
			while (!Flag_State)
			{
				Flag_State = GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TXE);
			}

			/*Send the data*/
			USART_APB1[USART_Num]->USART_DR  = Character;

			/*Enable Transfer Complete Interrupt*/
			USART_APB1[USART_Num]->USART_CR1 |= (1<<USART_INTERRUPT_TCIE);

		}
		else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
		{

			/*wait till Transmit data register is empty*/
			while (!Flag_State)
			{
				Flag_State = GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TXE);
			}
			/*Send the data*/
			USART_APB2[USART_Num-4]->USART_DR  = Character;

			/*Enable Transfer Complete Interrupt*/
			USART_APB2[USART_Num-4]->USART_CR1 |= (1<<USART_INTERRUPT_TCIE);
		}
		else {
			Error_State = USART_WRONG_NUMBER;
		}
	}
	else {
		Error_State = Null_Pointer ;
	}
	return Error_State ;
}

/*
 * @function 		:	USART_SendBufferIT
 * @brief			:	Send Buffer (Several bytes) using USART and
 * 						generate interrupt when Buffer Transmission is complete
 * @param			:	USART NUMBER
 * @param			:	Data Buffer
 * @param			:	Buffer Size (amount of data to be transferred)
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_SendBufferIT(USART_NUMBER_t USART_Num , uint8_t * Data_Buffer ,uint16_t Buffer_Size,void (*TC_CallBackFunc)(void))
{
	Error_State_t Error_State = OK;
	uint8_t Flag_State = 0 ;

	if (NULL != TC_CallBackFunc)
	{
		/*SET the IRQ Source*/
		IRQ_Source[USART_Num] = SOURCE_TxB;
		/*Set Call Back Globally*/
		USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_TCI]= TC_CallBackFunc ;

		/*Set Data Buffer to be sent Globally*/

		Global_Data_Buffer = Data_Buffer;

		/*Set buffer Size Globally*/
		Global_Data_Size = Buffer_Size;

		/*Check Which USART is selected*/
		if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
		{
			/*wait till Transmit data register is empty*/
			while (!Flag_State)
			{
				Flag_State = GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TXE);
			}
			/*Send First Data element of the buffer*/
			USART_APB1[USART_Num]->USART_DR  = Data_Buffer[0];

			/*Enable Transfer Complete Interrupt*/
			USART_APB1[USART_Num]->USART_CR1 |= (1<<USART_INTERRUPT_TCIE);

		}
		else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
		{
			/*Send First Data element of the buffer*/
			USART_APB2[USART_Num-4]->USART_DR  = Data_Buffer[0];

			/*Enable Transfer Complete Interrupt*/
			USART_APB2[USART_Num-4]->USART_CR1 |= (1<<USART_INTERRUPT_TCIE);
		}
		else {
			Error_State = USART_WRONG_NUMBER;
		}
	}
	else {
		Error_State = Null_Pointer ;
	}
	return Error_State ;
}

/*
 * @function 		:	USART_ReceiveCharIT
 * @brief			:	Receive character using USART and generate interrupt when Receiving is complete
 * @param			:	USART NUMBER
 * @param			:	variable to save Character
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveCharIT(USART_NUMBER_t USART_Num , uint8_t* Character ,void (*RC_CallBackFunc)(void))
{
	Error_State_t Error_State = OK;

	if (NULL != RC_CallBackFunc)
	{
		/*Set Call Back Globally*/
		USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_RXNEI]= RC_CallBackFunc ;

		/*Set IRQ Source for the Given USART*/
		IRQ_Source[USART_Num] = SOURCE_RxD;

		/*Set the character variable globally*/
		Global_Received_Data = Character ;

		/*Check Which USART is selected*/
		if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
		{
			/*Enable Receive Not Empty Interrupt*/
			USART_APB1[USART_Num]->USART_CR1 |= (1<<USART_INTERRUPT_RXNEIE);
		}
		else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
		{
			/*Enable Receive Not Empty Interrupt*/
			USART_APB2[USART_Num-4]->USART_CR1 |= (1<<USART_INTERRUPT_RXNEIE);
		}
		else {
			Error_State = USART_WRONG_NUMBER;
		}
	}
	else {
		Error_State = Null_Pointer ;
	}
	return Error_State ;
}

/*
 * @function 		:	USART_ReceiveBufferIT
 * @brief			:	Receive Buffer (Several bytes) using USART and
 * 						generate interrupt when Buffer Receiving is complete
 * @param			:	USART NUMBER
 * @param			:	variable to save the Data Buffer
 * @param			:	Buffer Size (amount of data to be transferred)
 * @param			:	Call Back function
 * @retval			:	Error State
 */
Error_State_t USART_ReceiveBufferIT(USART_NUMBER_t USART_Num , uint8_t * Data_Buffer ,uint16_t Buffer_Size,void (*RC_CallBackFunc)(void))
{
	Error_State_t Error_State = OK;

	if (NULL != RC_CallBackFunc)
	{
		/*Set Call Back Globally*/
		USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_RXNEI]= RC_CallBackFunc ;

		/*Set IRQ Source for the Given USART*/
		IRQ_Source[USART_Num] = SOURCE_RxB;

		/*Set the character variable globally*/
		Global_Data_Buffer = Data_Buffer ;

		/*Set the buffer size globally*/
		Global_Data_Size = Buffer_Size;

		/*Check Which USART is selected*/
		if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
		{
			/*Enable Receive Not Empty Interrupt*/
			USART_APB1[USART_Num]->USART_CR1 |= (1<<USART_INTERRUPT_RXNEIE);
		}
		else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
		{
			/*Enable Receive Not Empty Interrupt*/
			USART_APB2[USART_Num-4]->USART_CR1 |= (1<<USART_INTERRUPT_RXNEIE);
		}
		else {
			Error_State = USART_WRONG_NUMBER;
		}
	}
	else {
		Error_State = Null_Pointer ;
	}
	return Error_State ;

}
/*
 * @function 		:	USART_Enable_DMA_RX
 * @brief			:	Enable DMA RX Line for the required USART
 * @param			:	USART NUMBER
 * @retval			:	Error State
 */
Error_State_t USART_Enable_DMA_RX(USART_NUMBER_t USART_Num)
{
	Error_State_t Error_State = OK;

	/*Check Which USART is selected*/
	if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
	{
		/*Enable DMA RX Line*/
		USART_APB1[USART_Num]->USART_CR3 |= (1<<DMAR_ENABLE);
	}
	else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
	{
		/*Enable DMA RX Line*/
		USART_APB2[USART_Num-4]->USART_CR3 |= (1<<DMAR_ENABLE);
	}
	else {
		Error_State = USART_WRONG_NUMBER;
	}

	return Error_State;
}
/*
 * @function 		:	USART_Enable_DMA_TX
 * @brief			:	Enable DMA TX Line for the required USART
 * @param			:	USART NUMBER
 * @retval			:	Error State
 */
Error_State_t USART_Enable_DMA_TX(USART_NUMBER_t USART_Num)
{
	Error_State_t Error_State = OK;

	/*Check Which USART is selected*/
	if ((USART_Num >= USART_NUMBER_USART2) && (USART_Num <= USART_NUMBER_UART5))
	{
		/*Enable DMA RX Line*/
		USART_APB1[USART_Num]->USART_CR3 |= (1<<DMAT_ENABLE);
	}
	else if ((USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6) )
	{
		/*Enable DMA RX Line*/
		USART_APB2[USART_Num-4]->USART_CR3 |= (1<<DMAT_ENABLE);
	}
	else {
		Error_State = USART_WRONG_NUMBER;
	}

	return Error_State;
}

/***************End of MAIN FUNCTIONS*******************/


/***************** STATIC FUNCTIONS ********************/

static Error_State_t USART_Check_Configs(const USART_CONFIGS_t * USART_Configs)
{
	Error_State_t Error_State = OK;

	if (NULL != USART_Configs)
	{
		if ((USART_Configs -> USART_Num >= USART_NUMBER_USART2) && (USART_Configs -> USART_Num <= USART_NUMBER_USART6))
		{
			if ((PARITY_STATE_NO_PARITY==USART_Configs->Parity_State)||((PARITY_STATE_PARITY_ENABLED==USART_Configs->Parity_State)))
			{
				if ((USART_Configs->StopBits_Num >= STOP_BITS_ONE_BIT)&&(USART_Configs->StopBits_Num <= STOP_BITS_ONE_HALF_BIT))
				{
					if ((USART_Configs -> Word_Length == WORD_LENGTH_8BITS)||(USART_Configs -> Word_Length == WORD_LENGTH_9BITS))
					{
						if ((USART_Configs -> Mode_Type >= MODE_TYPE_RX )&&(USART_Configs -> Mode_Type <= MODE_TYPE_RXandTX))
						{
							if ((USART_Configs->OverSampling_State == OVERSAMPLING_STATE_THREE_SAMPLES)||(USART_Configs->OverSampling_State == OVERSAMPLING_STATE_ONE_SAMPLE))
							{
								if ((USART_Configs->OverSampling_Value == OVERSAMPLING_VALUE_OVER8)||(USART_Configs->OverSampling_Value == OVERSAMPLING_VALUE_OVER16))
								{
									if ((USART_Configs->HWFlow_Control_Mode == HW_FLOW_CONTROL_MODE_ENABELD)||((USART_Configs->HWFlow_Control_Mode == HW_FLOW_CONTROL_MODE_DISABLED)))
									{
										Error_State = OK;
									}
									else {
										Error_State = USART_WRONG_HW_FLOW_MODE;
									}
								}
								else {
									Error_State = USART_WRONG_OVER_SAMPLING_VALUE;
								}
							}
							else {
								Error_State = USART_WRONG_OVER_SAMPLING_STATE;
							}
						}
						else {
							Error_State = USART_WRONG_MODE_TYPE;
						}
					}
					else {
						Error_State = USART_WRONG_WORD_LENGTH;
					}
				}
				else {
					Error_State = USART_WRONG_STOP_BITS_NUMBER;
				}
			}
			else {
				Error_State = USART_WRONG_PARITY_STATE;
			}
		}
		else {
			Error_State = USART_WRONG_NUMBER;
		}
	}
	else {
		Error_State = Null_Pointer;
	}

	return Error_State ;
}

static void USART_SetBaudRate(uint32_t BaudRate_Value , uint32_t Clock_Value , uint32_t OVER_SAMPLE_VALUE ,USART_NUMBER_t USART_Num)
{
	uint32_t USARTDIV = ((uint64_t)Clock_Value*1000)/(8*(2-(OVER_SAMPLE_VALUE))*BaudRate_Value);

	uint32_t Mantessa_Part = USARTDIV /1000;
	uint32_t Division_Factor = USARTDIV % 1000;

	if (OVER_SAMPLE_VALUE == OVERSAMPLING_VALUE_OVER16)
	{
		Division_Factor = ((Division_Factor * 16)+500)/1000;
	}
	else {
		Division_Factor = ((Division_Factor * 8)+500)/1000;
	}

	if ( (USART_Num == USART_NUMBER_USART1) || (USART_Num == USART_NUMBER_USART6))
	{
		USART_APB2[USART_Num-4]->USART_BRR  = 0 ;
		USART_APB2[USART_Num-4]->USART_BRR |= (Division_Factor)  ;
		USART_APB2[USART_Num-4]->USART_BRR |= (Mantessa_Part<<4)  ;

	}
	else {
		USART_APB1[USART_Num]->USART_BRR  = 0 ;
		USART_APB1[USART_Num]->USART_BRR |= (Division_Factor)  ;
		USART_APB1[USART_Num]->USART_BRR |= (Mantessa_Part<<4)  ;
	}


}

static void USART_IRQ_Source_HANDLE(USART_NUMBER_t USART_Num)
{
	uint8_t Flag_State=0;
	if (IRQ_Source[USART_Num]==SOURCE_TxD)
	{
		/*Check Which USART And Disable the TC Interrupt*/
		if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
		{
			CLR_BIT(USART_APB1[USART_Num]->USART_CR1 , USART_INTERRUPT_TCIE);
		}
		else {
			CLR_BIT(USART_APB2[USART_Num-4]->USART_CR1 , USART_INTERRUPT_TCIE);
		}
		/*Clear the Source*/
		IRQ_Source[USART_Num]= NO_SOURCE;

		/*Call the CallBack Function*/
		if (NULL != USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_TCI])
		{
			USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_TCI]();
		}
	}
	else if (IRQ_Source[USART_Num]==SOURCE_TxB)
	{
		static uint8_t Counter=1;

		/*wait till Transmit data register is empty*/
		while (!Flag_State)
		{
			/*Check which USART Group and Read the Flag*/
			if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
			{
				Flag_State = GET_BIT(USART_APB1[USART_Num]->USART_SR,USART_FLAG_TXE);
			}
			else {
				Flag_State = GET_BIT(USART_APB2[USART_Num-4]->USART_SR,USART_FLAG_TXE);
			}

		}
		/*Check which USART Group and Send the next data element*/
		if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
		{
			/*Send the Next Data Element*/
			USART_APB1[USART_Num]->USART_DR = Global_Data_Buffer[Counter];
			Counter++;
		}
		else {
			/*Send the Next Data Element*/
			USART_APB2[USART_Num-4]->USART_DR = Global_Data_Buffer[Counter];
			Counter++;
		}

		/*data buffer sent completely*/
		if (Counter == Global_Data_Size)
		{
			/*Check Which USART And Disable TC the Interrupt*/
			if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
			{
				CLR_BIT(USART_APB1[USART_Num]->USART_CR1 , USART_INTERRUPT_TCIE);
			}
			else {
				CLR_BIT(USART_APB2[USART_Num-4]->USART_CR1 , USART_INTERRUPT_TCIE);
			}

			/*Clear the Source*/
			IRQ_Source[USART_Num]= NO_SOURCE;
			/*Call the Call Back Function*/
			if (NULL != USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_TCI])
			{
				USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_TCI]();
			}
		}

	}
	else if (IRQ_Source[USART_NUMBER_USART2]==SOURCE_RxD)
	{
		/*Check Which USART And Disable RXNE the Interrupt*/
		if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
		{
			CLR_BIT(USART_APB1[USART_Num]->USART_CR1 , USART_INTERRUPT_RXNEIE);
		}
		else {
			CLR_BIT(USART_APB2[USART_Num-4]->USART_CR1 , USART_INTERRUPT_RXNEIE);
		}
		/*Clear the IRQ Source*/
		IRQ_Source[USART_Num]= NO_SOURCE;

		/*Check Which USART Group and Read the Received data*/
		if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
		{
			*Global_Received_Data = USART_APB1[USART_Num]->USART_DR ;
		}
		else {
			*Global_Received_Data = USART_APB2[USART_Num-4]->USART_DR ;
		}

		/*Call the CALLBACK Function*/
		if (NULL != USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_RXNEI])
		{
			USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_RXNEI]();
		}
	}
	else if(IRQ_Source[USART_NUMBER_USART2]==SOURCE_RxB)
	{
		/*Counter variable to move on the buffer elements*/
		static uint8_t Counter=0;

		/*Check Which USART Group and Read the Received data element*/
		if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
		{
			Global_Data_Buffer[Counter++] = USART_APB1[USART_Num]->USART_DR ;
		}
		else {
			Global_Data_Buffer[Counter++] = USART_APB2[USART_Num-4]->USART_DR ;
		}

		/*The total Buffer received completely*/
		if (Counter == Global_Data_Size)
		{

			/*Check Which USART And Disable the RXNE Interrupt*/
			if ((USART_Num >= USART_NUMBER_USART2)&&(USART_Num <= USART_NUMBER_UART5))
			{
				CLR_BIT(USART_APB1[USART_Num]->USART_CR1 , USART_INTERRUPT_RXNEIE);
			}
			else {
				CLR_BIT(USART_APB2[USART_Num-4]->USART_CR1 , USART_INTERRUPT_RXNEIE);
			}

			/*Clear the IRQ Source*/
			IRQ_Source[USART_Num]= NO_SOURCE;

			/*Call the CALLBACK Function*/
			if (NULL != USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_RXNEI])
			{
				USART_pf_CallBackFuncs[USART_Num][USART_CALLBACKS_RXNEI]();
			}
		}

	}
}

/************** End of STATIC FUNCTIONS ****************/


/********************* IRQ HANDLERS ********************/

void USART1_IRQHandler(void)
{
	USART_IRQ_Source_HANDLE(USART_NUMBER_USART1);
}

void USART2_IRQHandler(void)
{
	USART_IRQ_Source_HANDLE(USART_NUMBER_USART2);
}

void USART3_IRQHandler(void)
{
	USART_IRQ_Source_HANDLE(USART_NUMBER_USART3);
}

void UART4_IRQHandler(void)
{
	USART_IRQ_Source_HANDLE(USART_NUMBER_UART4);
}

void UART5_IRQHandler(void)
{
	USART_IRQ_Source_HANDLE(USART_NUMBER_UART5);
}

void USART6_IRQHandler(void)
{
	USART_IRQ_Source_HANDLE(USART_NUMBER_USART6);
}

/****************** End OF IRQ HANDLERS ****************/
