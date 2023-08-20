/*
 *@file		:	DMA_Private.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Privates for DMA Peripheral
 */


#ifndef DMA_INC_DMA_PRIVATE_H_
#define DMA_INC_DMA_PRIVATE_H_

/************Stream x Members of array configuration register */
#define		Sx_CR 					0
#define		Sx_NDTR					1
#define		Sx_PAR					2
#define		Sx_M0AR					3
#define		Sx_M1AR					4
#define		Sx_FCR					5

#define 	CHANNELS_MASK			0x7u
#define 	CHANNEL_BITS_START		25u

#define 	PRIORITY_MASK			0x3u
#define 	PRIORITY_BITS_START		16u

#define		DIRECTION_MASK			0x3u
#define 	DIRECTION_BITS_START	6u

#define 	MINC_MASK				0x1u
#define 	MINC_BITS_START			10u

#define 	PINC_MASK				0x1u
#define 	PINC_BITS_START			9u

#define 	PSIZE_MASK				0x3u
#define 	PSIZE_BITS_START		11u

#define		MSIZE_MASK				0x3u
#define 	MSIZE_BITS_START		13u

#define     THRESHOLD_MASK			0x3u
#define     THRESHOLD_BITS_START	0u

#define 	DMDIS_MASK				0x1u
#define		DMDIS_BITS_START		2u

#define 	IE_MASK					0x1u
#define 	FEIE_BITS_START			7u

#define 	DMA_CONTROLLERS 		2u

#define 	STREAMS_IRQs			8u


#endif /* DMA_INC_DMA_PRIVATE_H_ */
