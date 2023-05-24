/*
 * SYSTICK_Private.h
 *
 *  Created on: May 11, 2023
 *      Author: mhmd wael
 */

#ifndef SYSTICK_INC_SYSTICK_PRIVATE_H_
#define SYSTICK_INC_SYSTICK_PRIVATE_H_

#define 	ENABLE_MASK				0b1
#define 	ENABLE_BIT_ACCESS		0

#define 	INTERRUPT_MASK			0b1
#define 	INTERRUPT_BIT_ACCESS	1u

#define		CLKSRC_MASK				0b1
#define 	CLKSRC_BIT_ACCESS		2u

#define 	TICK_TIME				0.0625

#define 	COUNTFLAG				16u


#endif /* SYSTICK_INC_SYSTICK_PRIVATE_H_ */
