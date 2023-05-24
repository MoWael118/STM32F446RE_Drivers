/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : RCC_Private.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/

#ifndef RCC_INC_RCC_PRIVATE_H_
#define RCC_INC_RCC_PRIVATE_H_

enum ClockTypes 		{HSI,HSE,PLL_P,PLL_R,LSE,LSI,PLL};
enum ClockStatus 		{ON,OFF};


struct PLL_CONFIGs {

	/* Main PLL entry clock source {HSE , HSI}*/
	uint8_t PLL_Source;

	/*Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks*/
	/*Set only if PLL_R Clock will be used*/
	/*If not used , Pass 0 */
	uint8_t PLLR_Value; /*Accept Values from 2 -> 7*/

	/*Main PLL (PLL) division factor for main system clock*/
	/*Set if PLL_P Clock will be used*/
	uint8_t PLLP_Value; /*Accept Values ( 2,4,6,8 )*/

	/*Division factor for the main PLL input clock*/
	uint8_t PLLM_Value; /*Accept Values from 2 -> 63*/

	/*Main PLL (PLL) multiplication factor */
	uint16_t PLLN_Value; /*Accept Values from 50 -> 432*/
};

struct Clock_Configs {

	uint8_t APB2_PRE;
	uint8_t APB1_PRE;
	uint8_t AHB_PRE;

};

enum PreScaller {NOT_DIVIDED,DIVIDED_BY2=4,DIVIDED_BY4,DIVIDED_BY8,DIVIDED_BY16,DIVIDED_BY64
				,DIVIDED_BY128,DIVIDED_BY256,DIVIDED_BY512};



#define TIME_OUT 		10000


#define ENABLED			1
#define DISABLED		0

#define CLK_SW_MASK 	0xFFFFFFFC

#define PLLM_MASK 	0xFFFFFFC0

#define PLLN_MASK	0xFFFF803F

#define PLLR_MASK	0x8FFFFFFF

#define PPRE2_MASK 	0xFFFF1FFF

#define PPRE1_MASK 	0xFFFFE3FF

#define HPRE_MASK   0xFFFFFF0F

enum AHB1_Periphrals {
	GPIOA_P,GPIOB_P,GPIOC_P,GPIOD_P,GPIOE_P,GPIOF_P,GPIOG_P,GPIOH_P,CRC=12,BKPSRAM=18,DMA1=21,DMA2,OTGHS=29,OTGHSULPI
};

enum AHB2_Peripherals {
	DCMI,OTGFS=7
};

enum AHB3_Peripherals {
	FMC,QSPI
};
enum APB2_Periphrals {
	TIM1,TIM8,USART1=4,USART6,ADC1=8,ADC2,ADC3,SDIO,SPI1,SPI4,SYSCFG,TIM9=16,TIM10,TIM11,SAI1=22,SAI2

};



enum APB1_Periphrals{
	TIM2,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM12,
	TIM13,
	TIM14,
	WWDG=11,
	SPI2=14,
	SPI3,
	SPDIFRX,
	USART2,
	USART3,
	UART4,
	UART5,
	I2C1,
	I2C2,
	I2C3,
	FMPI2C1,
	CAN1,
	CAN2,
	CEC,
	PWR,
	DAC
};


#endif /* RCC_INC_RCC_PRIVATE_H_ */
