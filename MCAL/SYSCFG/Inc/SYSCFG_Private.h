/*
 *@file		:	SYSCFG_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Privates for SYSCFG Peripheral
 */

#ifndef SYSCFG_INC_SYSCFG_PRIVATE_H_
#define SYSCFG_INC_SYSCFG_PRIVATE_H_

enum SYSCFG_EXTIPorts{
	EXTI_PortA,
	EXTI_PortB,
	EXTI_PortC,
	EXTI_PortD,
	EXTI_PortE,
	EXTI_PortF,
	EXTI_PortG,
	EXTI_PortH
};

#define EXTI_PORT_MASK		0xF

#endif /* SYSCFG_INC_SYSCFG_PRIVATE_H_ */
