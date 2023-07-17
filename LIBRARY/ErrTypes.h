/*
 * Defines.h
 *
 *  Created on: May 1, 2023
 *      Author: mhmd wael
 */

#ifndef ERRTYPES_H_
#define ERRTYPES_H_

enum ErrorState {  NOK , OK ,Null_Pointer,InvalidPORTPIN,WRONG_IRQ_NUM
				,WRONG_PRIORITY_GROUPING
				,WRONG_PRIORITY_NUM};
#define NULL ((void *)0)

#endif /* ERRTYPES_H_ */
