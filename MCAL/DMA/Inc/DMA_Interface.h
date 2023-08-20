/*
 *@file		:	DMA_Interface.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Functions for DMA Peripheral
 */


#ifndef DMA_INC_DMA_INTERFACE_H_
#define DMA_INC_DMA_INTERFACE_H_

/******************* MAIN INCLUDES *********************/
#include <stdint.h>
#include "../../../LIBRARY/ErrTypes.h"
#include "DMA_Private.h"
/*******************************************************/

/************** MAIN USER DEFINED VARIABLES ************/
typedef enum {
	DMA_TC_FLAG,		/*TRANSFER COMPLETE INTERRUPT FLAG*/
	DMA_HT_FLAG,		/*HALF TRANSFER INTERRUPT FLAG*/
	DMA_TE_FLAG,		/*TRANSFER ERROR INTERRUPT FLAG*/
	DMA_DME_FLAG,		/*DIRECT MODE ERROR INTERRUPT FLAG*/
	DMA_FE_FLAG = 5			/*FIFO ERROR INTERRUPT FLAG*/

}FLAG_TYPES_t;

typedef enum {
	STREAM0,
	STREAM1,
	STREAM2,
	STREAM3,
	STREAM4,
	STREAM5,
	STREAM6,
	STREAM7

}STREAM_NUMBERS_t;

typedef enum {
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7
}CHANNEL_NUMBERS_t;

typedef enum {

	PERIPHERAL_TO_MEMORY,
	MEMORY_TO_PERIPHERAL,
	MEMORY_TO_MEMORY

}DATA_DIRECTIONS_t;

typedef enum {
	MEMORY_ADDRESS_FIXED,
	MEMORY_ADDRESS_INCREMENTING,

}MEM_INC_STATE_t;

typedef enum {
	PERIPHERAL_ADDRESS_FIXED,
	PERIPHERAL_ADDRESS_INCREMENTING,
}PER_INC_STATE_t;

typedef enum {
	MEM_DATA_SIZE_ONE_BYTE,
	MEM_DATA_SIZE_HALF_WORD,
	MEM_DATA_SIZE_WORD
}MEM_DATA_SIZE_t;

typedef enum {
	PER_DATA_SIZE_ONE_BYTE,
	PER_DATA_SIZE_HALF_WORD,
	PER_DATA_SIZE_WORD
}PER_DATA_SIZE_t;

typedef enum {
	DIRECT_MODE,
	FIFO_MODE
}FIFO_MODES_t;

typedef enum {
	PRIORITY_LOW,
	PRIORITY_MEDIUM,
	PRIORITY_HIGH,
	PRIORITY_VERY_HIGH
}PRIORITY_LEVELS_t;

typedef enum {
	ONE_QUARTER_FULL_FIFO,
	HALF_FULL_FIFO,
	THREE_QUARTERS_FULL_FIFO,
	FULL_FIFO
}THRESHOLD_Values_t;

typedef enum {

	DME_INT	=	1,	/*Direct mode error interrupt*/
	TE_INT		 ,	/*Transfer Error Interrupt*/
	HT_INT		 ,	/*Half Transfer Interrupt*/
	TC_INT		 ,	/*Transfer Complete interrupt*/
	FE_INT			/*FIFO Error Interrupt*/

}DMA_INTs_NAMES_t;

typedef enum {
	DMA_INT_DISABLE,
	DMA_INT_ENABLE

}DMA_INT_STATE_t;

typedef enum {
	DMA_1,
	DMA_2
}DMA_NUMBER_t;

typedef struct {

	DMA_NUMBER_t		DMA_Num;
	STREAM_NUMBERS_t 	StreamNum;
	CHANNEL_NUMBERS_t 	ChannelNum;
	DATA_DIRECTIONS_t	DATA_Direction;
	MEM_INC_STATE_t 	MemInc_state;
	PER_INC_STATE_t 	PerInc_state;
	MEM_DATA_SIZE_t		MemDataSize;
	PER_DATA_SIZE_t		PerDataSize;
	FIFO_MODES_t		FIFO_Mode;
	PRIORITY_LEVELS_t	Priority_Level;
	THRESHOLD_Values_t	Threshold_Value;

}DMA_Config_t;


/*******************************************************/

/****************** MAIN FUNCTIONS *********************/

/*
 * @function 		:	DMA_ReadINT_Flag
 * @brief			:	Read the desired interrupt flag state
 * @param			:  	DMA Controller Number
 * @param			:	Variable to save the flag state
 * @param			:	Flag type
 * @param			:	STREAM Number
 * @retval			:	Error State
 */
Error_State_t DMA_ReadINT_Flag(DMA_NUMBER_t	DMA_Num , uint8_t * Flag_Val ,FLAG_TYPES_t FLAG_Type , STREAM_NUMBERS_t StreamNum );


/*
 * @function 		:	DMA_ClearINT_Flag
 * @brief			:	CLEAR the desired interrupt flag state
 * @param			:  	DMA Controller Number
 * @param			:	Flag type
 * @param			:	STREAM Number
 * @retval			:	Error State
 */
Error_State_t DMA_ClearINT_Flag(DMA_NUMBER_t DMA_Num , FLAG_TYPES_t FLAG_Type , STREAM_NUMBERS_t StreamNum );



/*
 * @function 		:	DMA_Init
 * @brief			:	initialize the DMA
 * @param			:	Structure of DMA Configurations
 * @retval			:	Error State
 * @warning 		:	Memory to Memory Data direction can only be achieved in DMA2
 */

Error_State_t DMA_Init(const DMA_Config_t * DMA_CONFIGs);

/*
 * @function 		:	DMA_Set_INT_State
 * @brief			:	Set the desired DMA Interrupt state
 * @param			:  	DMA Controller Number
 * @param			:	STREAM Number
 * @param			: 	Interrupt Name
 * @param			:	Interrupt state
 * @retval			:	Error State
 */

Error_State_t DMA_Set_INT_State(DMA_NUMBER_t DMA_Num , STREAM_NUMBERS_t StreamNum , DMA_INTs_NAMES_t INT_Name , DMA_INT_STATE_t INT_State);



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

Error_State_t DMA_Start_Transfer(const DMA_Config_t * DMA_CONFIGs, uint32_t Src_Address , uint32_t Dest_Address , uint16_t Data_Length);


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

Error_State_t DMA_Start_Transfer_IT(const DMA_Config_t * DMA_CONFIGs, uint32_t Src_Address , uint32_t Dest_Address , uint16_t Data_Length ,void (*DMA_CallBack)(void));

/**************** End of MAIN FUNCTIONS ****************/


/***************** STATIC FUNCTIONS ********************/

static Error_State_t DMA_CheckConfig(DMA_Config_t * DMA_Configs);

/************** End of STATIC FUNCTIONS ****************/




#endif /* DMA_INC_DMA_INTERFACE_H_ */
