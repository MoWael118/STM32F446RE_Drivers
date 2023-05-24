/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : RCC_Program.c				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/

#include <stdint.h>

#include "../../../LIBRARY/BitMath.h"
#include "../../../LIBRARY/ErrTypes.h"
#include "../inc/RCC_Interface.h"

/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetClockStatus()
 *     FUNCTIONALITY : Set the selected clock state (ON/OFF)
 *     ARGUMENT 	 : UINT8 Clock Type {HSE,HSI,LSE,LSI,PLL} , UINT8 State of Clock {ON,OFF}
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetClockStatus(uint8_t CLK_TYPE , uint8_t status)
{
	uint8_t ErrorState = OK;
	uint32_t Timer=0;

	/*Switch on Clock Type*/
	switch (CLK_TYPE)
	{
	case HSE :
		if (status == ON)
		{
			/*Set HSE Bit */
			SET_BIT(	RCC->CR	 ,	16	);
			/*Wait until HSE is Ready*/
			while ( !(GET_BIT(RCC->CR,17))  && (Timer <=TIME_OUT)  )
			{
				Timer++;
			}
			/*Check if HSE is Ready or Time is out*/
			if(Timer== TIME_OUT)
			{
				ErrorState= NOK;
				Timer=0;
			}
			else {
				/*	HSE IS READY	*/
			}

		}
		else if (status == OFF)
		{
			CLR_BIT(	RCC->CR	 ,	16	);
		}
		else {
			ErrorState 	= 	NOK	;
		}

		break;


	case HSI :
		if (status == ON)
		{
			/*Set HSI Bit */
			SET_BIT(	RCC->CR	 ,	0);
			/*Wait until HSI is Ready*/
			while ( !(GET_BIT(RCC->CR,1))  && (Timer <=TIME_OUT)  )
			{
				Timer++;
			}
			/*Check if HSI is Ready or Time is out*/
			if(Timer== TIME_OUT)
			{
				ErrorState= NOK;
				Timer=0;
			}
			else {
				/*	HSI IS READY	*/
			}

		}
		else if (status == OFF)
		{
			CLR_BIT(	RCC->CR	 ,	0);
		}
		else {
			ErrorState 	= 	NOK	;
		}
		break;


	case PLL :
		if (status == ON)
		{
			/*Set PLL Bit */
			SET_BIT(	RCC->CR	 ,	24);
			/*Wait until PLL is Ready*/
			while ( !(GET_BIT(RCC->CR,25))  && (Timer <=TIME_OUT)  )
			{
				Timer++;
			}
			/*Check if PLL is Ready or Time is out*/
			if(Timer== TIME_OUT)
			{
				ErrorState= NOK;
				Timer=0;
			}
			else {
				/*	PLL IS READY	*/
			}

		}
		else if (status == OFF)
		{
			CLR_BIT(	RCC->CR	 ,	24);

		}
		else
		{
			ErrorState 	= 	NOK	;
		}

		break;

	default : ErrorState = NOK;
	}
	return ErrorState;
}


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetClockConfig()
 *     FUNCTIONALITY : Set the Prescaler for Buses
 *     ARGUMENT 	 : struct {
 *     							APB2 Prescaler (NOT_DIVIDED,DIVIDED_BY2,DIVIDED_BY4,DIVIDED_BY8,DIVIDED_BY16)
 *     						  , APB1 Prescaler (NOT_DIVIDED,DIVIDED_BY2,DIVIDED_BY4,DIVIDED_BY8,DIVIDED_BY16)
 *     						  , AHB Prescaler (NOT_DIVIDED,DIVIDED_BY2,DIVIDED_BY4,DIVIDED_BY8
 *                                   	,DIVIDED_BY16,DIVIDED_BY64,DIVIDED_BY128,DIVIDED_BY256,DIVIDED_BY512)
 *     						  }
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 : 1- APB2 Clock Must not to exceed 90 MHz
 *	   				   2- APB1 Clock Must not to exceed 45 MHz
 *	   				   3- AHB  Clock Must be at least 25 MHz when the Ethernet is used.
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetClockConfig(struct Clock_Configs* Clock_Config)
{
	uint8_t ErrorState =OK;

	/******************** SET APB2 PRESCALER ******************************/
	if ( Clock_Config->APB2_PRE == NOT_DIVIDED)
	{
		/*SET PRESCALER BITS TO 0*/
		RCC->CFGR &= PPRE2_MASK;
	}
	else if ((Clock_Config->APB2_PRE >=DIVIDED_BY2)	&&	(Clock_Config->APB2_PRE <=DIVIDED_BY16))
	{
		/*MASK PRESCALER BITS TO AVOID OLD VALUES*/
		RCC->CFGR &= PPRE2_MASK;
		/*SET THE NEW PRESCALER*/
		RCC->CFGR |= ((Clock_Config->APB2_PRE)<<13);
	}
	else
	{
		ErrorState = NOK;
	}

	/********************* SET APB1 PRESCALER *****************************/
	if ( Clock_Config->APB1_PRE == NOT_DIVIDED)
	{
		/*SET PRESCALER BITS TO 0*/
		RCC->CFGR &= PPRE1_MASK;
	}
	else if ((Clock_Config->APB1_PRE >=DIVIDED_BY2)	&&	(Clock_Config->APB1_PRE <=DIVIDED_BY16))
	{
		/*MASK PRESCALER BITS TO AVOID OLD VALUES*/
		RCC->CFGR &= PPRE1_MASK;
		/*SET THE NEW PRESCALER*/
		RCC->CFGR |= ((Clock_Config->APB1_PRE)<<10);
	}
	else
	{
		ErrorState = NOK;
	}
	/********************* SET AHB PRESCALER *****************************/
	if ( Clock_Config->AHB_PRE == NOT_DIVIDED)
	{
		/*SET PRESCALER BITS TO 0*/
		RCC->CFGR &= HPRE_MASK;
	}
	else if ((Clock_Config->AHB_PRE >=DIVIDED_BY2)	&&	(Clock_Config->AHB_PRE <=DIVIDED_BY512))
	{
		/*MASK PRESCALER BITS TO AVOID OLD VALUES*/
		RCC->CFGR &= HPRE_MASK;
		/*SET THE NEW PRESCALER*/
		RCC->CFGR |= (((Clock_Config->AHB_PRE)+4)<<4);
	}
	else
	{
		ErrorState = NOK;
	}

	return ErrorState;

}




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetSystemClock()
 *     FUNCTIONALITY : Set the selected clock as System Clock
 *     ARGUMENT 	 : UINT8 Clock Type {HSE,HSI,LSE,LSI,PLL}
 *     RETURN   	 : uint8_t Error State
 *     NOTES 		 : The clock passed to this function must be in ON
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetSystemClock(uint8_t CLK_TYPE)
{
	uint8_t ErrorState=OK;

	/*Masking the SW bits*/
	RCC->CFGR &= CLK_SW_MASK;
	switch (CLK_TYPE)
	{
	case HSE :

		/*Setting HSE as SYSCLK*/
		RCC->CFGR |= HSE ;
		break;

	case HSI :
		/*Setting HSI as SYSCLK*/
		RCC->CFGR |= HSI ;
		break;

	case PLL_P:
		/*Setting PLL_P as SYSCLK*/
		RCC->CFGR |= PLL_P ;
		break;

	case PLL_R:
		/*Setting PLL_R as SYSCLK*/
		RCC->CFGR |= PLL_R ;
		break;

//	default : ErrorState = NOK;
	}
	return ErrorState;
}

/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetPLL_Configs()
 *     FUNCTIONALITY : Set the PLL With chosen configurations
 *     ARGUMENT 	 : PLL_Configs Structure
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 : Before using this function, PLL state Must be off
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetPLL_Configs(struct PLL_CONFIGs * PLL_Config)
{
	uint8_t ErrorState = OK;

	/*1- Select PLL Source*/
	if (PLL_Config -> PLL_Source == HSE)
	{
		SET_BIT( RCC->PLL_CFGR , 22 );
	}
	else if (PLL_Config -> PLL_Source == HSI)
	{
		CLR_BIT( RCC->PLL_CFGR , 22 );
	}
	else
	{
		ErrorState= NOK;
	}

	/*2- SET PLLM Division Factor Value*/

	if ((PLL_Config->PLLM_Value >=2) && (PLL_Config->PLLM_Value <=63))
	{
		/*Clear PLLM Bits to avoid old values*/
		RCC->PLL_CFGR &= PLLM_MASK;
		/*Set the new value*/
		RCC->PLL_CFGR |= PLL_Config->PLLM_Value ;
	}
	else
	{
		ErrorState= NOK;
	}

	/*3- SET PLLN Multiplication Factor Value*/
	if ((PLL_Config->PLLN_Value >=50) && (PLL_Config->PLLN_Value <=432))
	{
		/*Clear PLLN Bits to avoid old values*/
		RCC->PLL_CFGR &= (PLLN_MASK);
		/*Set the new value*/
		RCC->PLL_CFGR |= (PLL_Config->PLLN_Value)<<6;
	}
	else
	{
		ErrorState= NOK;
	}



	/*4- SET PLLP\PLLR Division Factor Value*/
	/*if PLLR Value is zero then its not used and PLLP is used*/
	if (PLL_Config -> PLLR_Value ==0)
	{
		/*SET PLLP Value*/
		switch (PLL_Config -> PLLP_Value)
		{
		case 2 :
			CLR_BIT(RCC->PLL_CFGR,16);
			CLR_BIT(RCC->PLL_CFGR,17);
			break;
		case 4 :
			SET_BIT(RCC->PLL_CFGR,16);
			CLR_BIT(RCC->PLL_CFGR,17);
			break;
		case 6 :
			CLR_BIT(RCC->PLL_CFGR,16);
			SET_BIT(RCC->PLL_CFGR,17);
			break;
		case 8 :
			SET_BIT(RCC->PLL_CFGR,16);
			SET_BIT(RCC->PLL_CFGR,17);
			break;
		default : ErrorState=NOK;
		}
	}
	else if ((PLL_Config -> PLLR_Value >=2) &&(PLL_Config -> PLLR_Value <=7))
	{
		/*Clear PLLN Bits to avoid old values*/
		RCC->PLL_CFGR &= (PLLR_MASK);
		/*Set the new value*/
		RCC->PLL_CFGR |= (PLL_Config->PLLR_Value)<<28;
	}
	else
	{
		ErrorState = NOK;
	}

	return ErrorState;

}
/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHB1Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB1 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name
 *     {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,CRC,BKPSRAM,DMA1,DMA2,OTGHS,OTGHSULPI}
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_AHB1Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	uint8_t ErrorState=OK;
	if (CLK_State == ENABLED)
	{
		SET_BIT(RCC->AHB1ENR,Periphral_Name);
	}
	else if (CLK_State == DISABLED){
		CLR_BIT(RCC->AHB1ENR,Periphral_Name);
	}
	else {
		ErrorState=NOK;
	}
	return ErrorState;
}



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHB2Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB2 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name {DCMI,OTGFS}
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_AHB2Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	uint8_t ErrorState=OK;
	if (CLK_State == ENABLED)
	{
		SET_BIT(RCC->AHB2ENR,Periphral_Name);
	}
	else if (CLK_State == DISABLED){
		CLR_BIT(RCC->AHB2ENR,Periphral_Name);
	}
	else {
		ErrorState=NOK;
	}
	return ErrorState;
}




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHB3Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB3 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name {FMC,QSPI}
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_AHB3Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	uint8_t ErrorState=OK;
	if (CLK_State == ENABLED)
	{
		SET_BIT(RCC->AHB3ENR,Periphral_Name);
	}
	else if (CLK_State == DISABLED){
		CLR_BIT(RCC->AHB3ENR,Periphral_Name);
	}
	else {
		ErrorState=NOK;
	}
	return ErrorState;
}




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_APB2Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To APB2 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name
 *                    {TIM1,TIM8,USART1,USART6,ADC1,ADC2,ADC3,SDIO,SPI1,SPI4,SYSCFG,TIM9,TIM10,TIM11,SAI1,SAI2}
 *     				   UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_APB2Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	uint8_t ErrorState=OK;
	if (CLK_State == ENABLED)
	{
		SET_BIT(RCC->APB2ENR,Periphral_Name);
	}
	else if (CLK_State == DISABLED){
		CLR_BIT(RCC->APB2ENR,Periphral_Name);
	}
	else {
		ErrorState=NOK;
	}
	return ErrorState;
}



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_APB1Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To APB1 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name { TIM2,
 * 	                                           TIM3,
 * 	                                           TIM4,
 * 	                                           TIM5,
 * 	                                           TIM6,
 * 	                                           TIM7,
 * 	                                           TIM12,
 * 	                                           TIM13,
 * 	                                           TIM14,
 * 	                                           WWDG,
 * 	                                           SPI2,
 * 	                                           SPI3,
 * 	                                           SPDIFRX,
 * 	                                           USART2,
 * 	                                           USART3,
 * 	                                           UART4,
 * 	                                           UART5,
 * 	                                           I2C1,
 * 	                                           I2C2,
 * 	                                           I2C3,
 * 	                                           FMPI2C1,
 * 	                                           CAN1,
 * 	                                           CAN2,
 *                                             CEC,
 *                                             PWR,
 *                                             DAC }
 *
 *     				   UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_APB1Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State)
{
	uint8_t ErrorState=OK;
	if (CLK_State == ENABLED)
	{
		SET_BIT(RCC->APB1ENR,Periphral_Name);
	}
	else if (CLK_State == DISABLED){
		CLR_BIT(RCC->APB1ENR,Periphral_Name);
	}
	else {
		ErrorState=NOK;
	}
	return ErrorState;
}
