/*
 *@file		:	SCB_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Private Defines for SCB peripheral
 */


#ifndef SCB_INC_SCB_PRIVATE_H_
#define SCB_INC_SCB_PRIVATE_H_

typedef enum {

	SCBGT_G16_S0,
	SCBGT_G8_S2		=	4,
	SCBGT_G4_S4,
	SCBGT_G2_S8,
	SCBGT_G0_S16,
}GROUP_TYPES_t;
#define PRIGROUP		8

#endif /* SCB_INC_SCB_PRIVATE_H_ */
