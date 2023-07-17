/*
 * GPIO_Interface.h
 *
 *  Created on: May 7, 2023
 *      Author: mhmd wael
 */

#ifndef GPIO_INC_GPIO_INTERFACE_H_
#define GPIO_INC_GPIO_INTERFACE_H_

#include <stdint.h>
#include "GPIO_Private.h"

typedef enum {
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH
}Port_t;

typedef enum {
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
}Pin_t;

typedef enum {
	MODE_INPUT=0,
	MODE_OUTPUT,
	MODE_ALT_FUNC,
	MODE_ANALOG
}Mode_t;

typedef enum {
	OUTPUT_PUSH_PULL=0,
	OUTPUT_OPEN_DRAIN
}OutputType_t;

typedef enum {
	OUTPUTSPEED_LOW=0,
	OUTPUTSPEED_MEDIUM,
	OUTPUTSPEED_FAST,
	OUTPUTSPEED_HIGH
}OutputSpeed_t;

typedef enum {
	PULLTYPE_NOPULL=0,
	PULLTYPE_PULLUP,
	PULLTYPE_PULLDOWN
}PullUp_PullDown_t;

typedef enum {
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AlternateFunction_t;

typedef enum
{
	LOW=0,High
}PinVal_t;
typedef struct {
	Port_t Port_Num;
	Pin_t Pin_Num;
	Mode_t Mode;
	OutputSpeed_t Speed;
	OutputType_t Output_Type;
	PullUp_PullDown_t PullType;
	AlternateFunction_t AltFunc;
}PinConfig_t;


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8PinInit()
 *     FUNCTIONALITY : Initialize the selected pin
 *     ARGUMENT 	 : Pointer to structure PinConfig_t * Pin_Config
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8PinInit(PinConfig_t * Pin_Config);



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8SetPinStatus()
 *     FUNCTIONALITY : Set the selected PIN state
 *     ARGUMENT 	 : PORT - PIN - Value
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8SetPinStatus(Port_t Port,Pin_t Pin,PinVal_t State );


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8ReadPinStatus()
 *     FUNCTIONALITY : READ the selected PIN state
 *     ARGUMENT 	 : Port - PIN - Variable address to save the state
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8ReadPinStatus(Port_t Port,Pin_t Pin, PinVal_t * State );


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : GPIO_u8TogglePinStatus()
 *     FUNCTIONALITY : Toggle the selected PIN state
 *     ARGUMENT 	 : Port - PIN
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t GPIO_u8TogglePinStatus(Port_t Port,Pin_t Pin);



#endif /* GPIO_INC_GPIO_INTERFACE_H_ */
