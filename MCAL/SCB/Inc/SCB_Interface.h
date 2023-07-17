/*
 *@file		:	SCB_Interafce.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main functions for SCB peripheral
 */


#ifndef SCB_INC_SCB_INTERFACE_H_
#define SCB_INC_SCB_INTERFACE_H_

#include "SCB_Private.h"
/***********************************
 * @function 		:	SCB_u8SetPriorityGrouping
 * @brief			:	Set the number of Groups and Subgroups
 * @parameter[in]	:	GroupingType (number of Groups and Subgroups)
 * @retval			:	Error State
 */

uint8_t SCB_u8SetPriorityGrouping(  GROUP_TYPES_t GroupingType);



#endif /* SCB_INC_SCB_INTERFACE_H_ */
