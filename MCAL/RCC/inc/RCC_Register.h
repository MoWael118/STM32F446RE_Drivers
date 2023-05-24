/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : RCC_Register.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/
#ifndef RCC_INC_RCC_REGISTER_H_
#define RCC_INC_RCC_REGISTER_H_


typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLL_CFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t Reserved1;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t Reserved[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t Reserved4;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;

}RCC_REG_t;

static RCC_REG_t * const RCC = (RCC_REG_t*)0x40023800;


#endif /* RCC_INC_RCC_REGISTER_H_ */
