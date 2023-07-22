/*
 *@file		:	EXTI_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Privates for EXTI Peripheral
 */

#ifndef EXTI_INC_EXTI_PRIVATE_H_
#define EXTI_INC_EXTI_PRIVATE_H_

typedef struct {

	uint8_t EXTI_LINE;

	uint8_t EXTI_Trriger_Type;

	uint8_t EXTI_State;

	void (*EXTI_CallBackFunction)(void);

}EXTI_Configs;

typedef enum  {

	LINE_0,LINE_1,LINE_2,LINE_3,LINE_4,LINE_5,LINE_6,LINE_7,LINE_8,LINE_9,
	LINE_10,LINE_11,LINE_12,LINE_13,LINE_14,LINE_15,LINE_16,LINE_17,LINE_18,
	LINE_20=20,LINE_21,LINE_22

}EXTI_LINES;
typedef enum {
	EXTI_TRRIGERTYPE_RISING_EDGE,
	EXTI_TRRIGERTYPE_FALLING_EDGE,
	EXTI_TRRIGERTYPE_BOTH_EDGES
}EXTI_TRRIGER_TYPES;

typedef enum  {

	EXTI_DISABLED,
	EXTI_ENABLED
}EXTI_STATE;

#define EXTI_IRQ_NUMBERS	23
#define EXTI9_5_IRQ			5
#define EXTI10_15_IRQ		6

#endif /* EXTI_INC_EXTI_PRIVATE_H_ */
