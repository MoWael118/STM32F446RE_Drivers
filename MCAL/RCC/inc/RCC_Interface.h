/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : RCC_Interface.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/

#ifndef RCC_INC_RCC_INTERFACE_H_
#define RCC_INC_RCC_INTERFACE_H_

#include <stdint.h>

#include "RCC_Private.h"
#include "RCC_Register.h"



/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetClockStatus()
 *     FUNCTIONALITY : Set the selected clock state (ON/OFF)
 *     ARGUMENT 	 : UINT8 Clock Type {HSE,HSI,LSE,LSI,PLL} , UINT8 State of Clock {ON,OFF}
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetClockStatus(uint8_t CLK_TYPE , uint8_t Status);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetClockConfig()
 *     FUNCTIONALITY : Set the Prescaler for Buses
 *     ARGUMENT 	 : struct {APB2 Prescaler , APB1 Prescaler, AHB Prescaler}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 : 1- APB2 Clock Must not to exceed 90 MHz
 *	   				   2- APB1 Clock Must not to exceed 45 MHz
 *	   				   3- AHB  Clock Must be at least 25 MHz when the Ethernet is used.
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetClockConfig(struct Clock_Configs* Clock_Config);


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetSystemClock()
 *     FUNCTIONALITY : Set the selected clock as System Clock
 *     ARGUMENT 	 : UINT8 Clock Type {HSE,HSI,LSE,LSI,PLL}
 *     RETURN   	 : uint8_t Error State
 *
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetSystemClock(uint8_t CLK_TYPE);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_SetPLL_Configs()
 *     FUNCTIONALITY : Set the PLL With chosen configurations
 *     ARGUMENT 	 : PLL_Configs Structure
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 : Before using this function, PLL state Must be off
 *---------------------------------------------------------------------------------*/
uint8_t RCC_SetPLL_Configs(struct PLL_CONFIGs * PLL_Config);




/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHB1Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB1 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name
 *	   	{GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,CRC,BKPSRAM,DMA1,DMA2,OTGHS,OTGHSULPI}
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_AHB1Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);


/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHB2Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB2 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name {DCMI,OTGFS}
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_AHB2Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);





/*---------------------------------------------------------------------------------
 *
 *     NAME     	 : RCC_Set_AHB3Peripheral_CLK()
 *     FUNCTIONALITY : Set the Clock To AHB3 Peripherals
 *     ARGUMENT 	 : UINT8 Peripheral Name {FMC,QSPI}
 *                     UINT8 Clock State {ENABLED , DISABLED}
 *     RETURN   	 : uint8_t Error State
 *	   NOTES 		 :
 *---------------------------------------------------------------------------------*/
uint8_t RCC_Set_AHB3Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);





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
uint8_t RCC_Set_APB2Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);



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
uint8_t RCC_Set_APB1Peripheral_CLK (uint8_t Periphral_Name ,uint8_t CLK_State);






#endif /* RCC_INC_RCC_INTERFACE_H_ */
