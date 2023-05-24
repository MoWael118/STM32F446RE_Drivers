/*
 * GPIO_Private.h
 *
 *  Created on: May 7, 2023
 *      Author: mhmd wael
 */

#ifndef GPIO_INC_GPIO_PRIVATE_H_
#define GPIO_INC_GPIO_PRIVATE_H_

#define GPIO_PERIPHRAL_NUM 			8u

#define MODER_MASK					0b11
#define MODER_PIN_ACCESS			2u

#define PUPDR_MASK					0b11
#define PUPDR_PIN_ACCESS			2u

#define OSPEEDR_MASK				0b11
#define OSPEEDR_PIN_ACCESS			2u

#define OTYPER_MASK 				0b1
#define OTYPER_PIN_ACCESS			1u

#define AFR_PIN_ACCESS				4u
#define AFR_MASK					0b1111


#endif /* GPIO_INC_GPIO_PRIVATE_H_ */
