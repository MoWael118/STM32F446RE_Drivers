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
enum ClockStatus 		{OFF,ON};


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
	AHB1_GPIOA_P,
	AHB1_GPIOB_P,
	AHB1_GPIOC_P,
	AHB1_GPIOD_P,
	AHB1_GPIOE_P,
	AHB1_GPIOF_P,
	AHB1_GPIOG_P,
	AHB1_GPIOH_P,
	AHB1_CRC=12,
	AHB1_BKPSRAM=18,
	AHB1_DMA1=21,
	AHB1_DMA2,
	AHB1_OTGHS=29,
	AHB1_OTGHSULPI
};

enum AHB2_Peripherals {
	AHB2_DCMI,
	AHB2_OTGFS=7
};

enum AHB3_Peripherals {
	AHB3_FMC,
	AHB3_QSPI
};
enum APB2_Periphrals {
	APB2_TIM1,
	APB2_TIM8,
	APB2_USART1=4,
	APB2_USART6,
	APB2_ADC1=8,
	APB2_ADC2,
	APB2_ADC3,
	APB2_SDIO,
	APB2_SPI1,
	APB2_SPI4,
	APB2_SYSCFG,
	APB2_TIM9=16,
	APB2_TIM10,
	APB2_TIM11,
	APB2_SAI1=22,
	APB2_SAI2

};



enum APB1_Periphrals{
	APB1_TIM2,
	APB1_TIM3,
	APB1_TIM4,
	APB1_TIM5,
	APB1_TIM6,
	APB1_TIM7,
	APB1_TIM12,
	APB1_TIM13,
	APB1_TIM14,
	APB1_WWDG=11,
	APB1_SPI2=14,
	APB1_SPI3,
	APB1_SPDIFRX,
	APB1_USART2,
	APB1_USART3,
	APB1_UART4,
	APB1_UART5,
	APB1_I2C1,
	APB1_I2C2,
	APB1_I2C3,
	APB1_FMPI2C1,
	APB1_CAN1,
	APB1_CAN2,
	APB1_CEC,
	APB1_PWR,
	APB1_DAC
};


#endif /* RCC_INC_RCC_PRIVATE_H_ */
