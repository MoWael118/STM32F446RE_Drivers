/***************************************/
/* @file 		GPIO_Program.c
 * @author		Mohamed Wael
 * @brief		The main source file for GPIO
 *
 */

#include <stdint.h>
#include <stddef.h>


#include "../../../LIBRARY/ErrTypes.h"
#include "../../../LIBRARY/STM32F446xx.h"

#include "../Inc/GPIO_Interface.h"

static GPIO_RegDef_t * GPIO_PORT[GPIO_PERIPHRAL_NUM]= {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH};

/*
 * @function		GPIO_u8PinInit
 * @brief			main initialization for selected pin
 * @param[in]		PinConfig : Initialization values of the pin
 * @retval			ErrorState
 */
uint8_t GPIO_u8PinInit(PinConfig_t * Pin_Config)
{
	uint8_t ErrorState=OK;
	/*****************Make Sure the received pointer isn't NULL*************/
	if (Pin_Config != NULL)
	{
		/*Check Valid PORT and PIN*/
		if ((Pin_Config->Port_Num)<=PORTH	&&	(Pin_Config->Pin_Num<=PIN15))
		{
			/********Select GPIO MODE************/
			GPIO_PORT[Pin_Config->Port_Num]->MODER &= ~(MODER_MASK << MODER_PIN_ACCESS * (Pin_Config->Pin_Num));/*Clear the PINS from old values*/
			GPIO_PORT[Pin_Config->Port_Num]->MODER |= ((Pin_Config->Mode)<< MODER_PIN_ACCESS * (Pin_Config->Pin_Num) );/*Set the new mode*/
			/*********Select PULL type***********/
			GPIO_PORT[Pin_Config->Port_Num]->PUPDR &= ~ (PUPDR_MASK << (PUPDR_PIN_ACCESS * (Pin_Config->Pin_Num)));/*Clear the PINS from old values*/
			GPIO_PORT[Pin_Config->Port_Num]->PUPDR |= (Pin_Config->PullType)<<((PUPDR_PIN_ACCESS * (Pin_Config->Pin_Num)));	/*Set the new VAlue*/
			/*********if Output or AF set output speed & type**********/
			if ((Pin_Config->Mode == OUTPUT) ||(Pin_Config->Mode == ALT_FUNC))
			{
				/**************Set OUTPUT Speed******************/
				GPIO_PORT[Pin_Config->Port_Num]->OSPEEDR &= ~ (OSPEEDR_MASK<<((Pin_Config->Pin_Num)*OSPEEDR_PIN_ACCESS));/*Clear the PINS from old values*/
				GPIO_PORT[Pin_Config->Port_Num]->OSPEEDR |= ((Pin_Config->Speed)<<((Pin_Config->Pin_Num)*OSPEEDR_PIN_ACCESS));/*Set the new VALUE*/
				/**************Set OUTPUT Type*******************/
				GPIO_PORT[Pin_Config->Port_Num]->OTYPER &= ~ (OTYPER_MASK<<((Pin_Config->Pin_Num)*OTYPER_PIN_ACCESS));/*Clear the PINS from old values*/
				GPIO_PORT[Pin_Config->Port_Num]->OTYPER |= ((Pin_Config->Output_Type)<<((Pin_Config->Pin_Num)*OTYPER_PIN_ACCESS));/*Set the new VALUE*/
				/***********if AF Set the functionality**********/
				if (Pin_Config->Mode == ALT_FUNC)
				{
					GPIO_PORT[Pin_Config->Port_Num]->AFR[(Pin_Config->Pin_Num)/8u] &= ~ (AFR_MASK<<(((Pin_Config->Pin_Num)%8u) * AFR_PIN_ACCESS));/*Clear the PINS from old values*/
					GPIO_PORT[Pin_Config->Port_Num]->AFR[(Pin_Config->Pin_Num)/8u] |=  ((Pin_Config->AltFunc)<<(((Pin_Config->Pin_Num)%8u) * AFR_PIN_ACCESS));/*Set the new VALUE*/
				}
			}

		}
		else
		{
			ErrorState = InvalidPORTPIN;
		}
	}
	else
	{
		ErrorState= Null_Pointer;
	}
	return ErrorState;
}

/*
 * @function		GPIO_u8SetPinStatus
 * @brief			Setting The selected pin State
 * @param[in]		Port Number
 * 					Pin Number
 * 					State
 * @retval			ErrorState
 */
uint8_t GPIO_u8SetPinStatus(Port_t Port,Pin_t Pin,PinVal_t State )
{
	uint8_t Local_u8ErrorState = OK;
	if (Port <=PORTH && Pin<=PIN15)
	{
		if (State == LOW)
		{
			GPIO_PORT[Port]->BSRR = 1<<(Pin+16);

		}
		else if (State == High)
		{
			GPIO_PORT[Port]->BSRR = 1<<Pin;
		}
	}
	else
	{
		Local_u8ErrorState = InvalidPORTPIN;
	}
	return Local_u8ErrorState;
}


/*
 * @function		GPIO_u8ReadPinStatus
 * @brief			Reading value of selected pin
 * @param[in]		Port Number , Pin Number
 * @param[out]		Address of state Variable
 * @retval			ErrorState
 */
uint8_t GPIO_u8ReadPinStatus(Port_t Port,Pin_t Pin, PinVal_t * State )
{
	uint8_t Local_u8ErrorState = OK;

	if (State != NULL)
	{
		if (Port <=PORTH && Pin<=PIN15)
		{
			*State = ((GPIO_PORT[Port]->IDR)>>Pin)&1;
		}
		else
		{
			Local_u8ErrorState = InvalidPORTPIN;
		}
	}
	else {
		Local_u8ErrorState = Null_Pointer;

	}
	return Local_u8ErrorState;
}

/*
 * @function		GPIO_u8TogglePinStatus
 * @brief			Toggle value of selected pin
 * @param[in]		Port Number
 * 					Pin Number
 * @retval			ErrorState
 */
uint8_t GPIO_u8TogglePinStatus(Port_t Port,Pin_t Pin)
{
	uint8_t Local_u8ErrorState = OK;

	if (Port <=PORTH && Pin<=PIN15)
	{
		GPIO_PORT[Port]->ODR ^= 1<<Pin;
	}
	else
	{
		Local_u8ErrorState = InvalidPORTPIN;
	}

	return Local_u8ErrorState;
}

