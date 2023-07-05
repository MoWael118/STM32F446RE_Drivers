/*
 *@file		:	NVIC_Interafce.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for NVIC peripheral
 */
#ifndef NVIC_INC_NVIC_INTERFACE_H_
#define NVIC_INC_NVIC_INTERFACE_H_

/***********************************
 * @function 		:	NVIC_u8EnableInt
 * @brief			:	Enable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8EnableInt(uint8_t IRQ_Num);

/***********************************
 * @function 		:	NVIC_u8DisableInt
 * @brief			:	Disable the NVIC Interrupt for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8DisableInt(uint8_t IRQ_Num);


/***********************************
 * @function 		:	NVIC_u8SetPendFlag
 * @brief			:	Set the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8SetPendFlag(uint8_t IRQ_Num);


/***********************************
 * @function 		:	NVIC_u8ClearPendFlag
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @retval			:	Error State
 */

uint8_t NVIC_u8ClearPendFlag(uint8_t IRQ_Num);


/***********************************
 * @function 		:	NVIC_u8ReadActiveFlag
 * @brief			:	Clear the Interrupt Pending flag for specific IRQ
 * @parameter[in]	:	IRQ_Num
 * @parameter[out]  :   Flag_Value (Active Flag Value)
 * @retval			:	Error State
 */

uint8_t NVIC_u8ReadActiveFlag(uint8_t IRQ_Num,uint8_t * Flag_Value);



#endif /* NVIC_INC_NVIC_INTERFACE_H_ */
