/*******************************************************************/
/*******************************************************************/
/********* OWNER     : Mohamed Wael				      **************/
/********* DATE      : 1/5/2023					  	  **************/
/********* FILE NAME : STM32446RExx.h				  **************/
/********* Version   : V1.0                           **************/
/*******************************************************************/
/*******************************************************************/

#ifndef STM32F446XX_H_
#define STM32F446XX_H_



/************************	  	BASE MEMORY ADDRESSES		    	************************/
#define FLASH_BASE_ADDRESS      	0x08000000UL
#define SRAM_BASE_ADDRESS   	   	0x20000000UL
#define ROM_BASE_ADDRESS 	     	0x1FFF0000UL


/************************     	 CORE PERIPHERALS BASE ADDRESSES	************************/
#define SYSTICK_BASE_ADDRESS		0xE000E010UL
#define NVIC_BASE_ADDRESS			0xE000E100UL


/************************     	AHB 1 BASE PERIPHERALS ADDRESSES	************************/
#define GPIOA_BASE_ADDRESS			0x40020000UL
#define GPIOB_BASE_ADDRESS          0x40020400UL
#define GPIOC_BASE_ADDRESS          0x40020800UL
#define GPIOD_BASE_ADDRESS          0x40020C00UL
#define GPIOE_BASE_ADDRESS          0x40021000UL
#define GPIOF_BASE_ADDRESS          0x40021400UL
#define GPIOG_BASE_ADDRESS          0x40021800UL
#define GPIOH_BASE_ADDRESS          0x40021C00UL

/************************     	AHB 2 BASE PERIPHERALS ADDRESSES	************************/

/************************     	AHB 3 BASE PERIPHERALS ADDRESSES	************************/

/************************     	APB 1 BASE PERIPHERALS ADDRESSES	************************/

/************************     	APB 2 BASE PERIPHERALS ADDRESSES	************************/

/************************     	GPIO REGISTERS DEFINITION			************************/

typedef struct {
	volatile uint32_t  MODER;				/*MODE REGISTER*/
	volatile uint32_t  OTYPER;				/*OUTPUT TYPE REGISTER*/
	volatile uint32_t  OSPEEDR;				/*OUTPUT SPEED REGISTER*/
	volatile uint32_t  PUPDR;				/*PULL UP PULL DOWN REGISTER*/
	volatile uint32_t  IDR;					/*INPUT DATA REGISTER*/
	volatile uint32_t  ODR;					/*OUTPUT DATA REGISTER*/
	volatile uint32_t  BSRR;				/*BIT SET RESET REGISTER*/
	volatile uint32_t  LCKR;				/*LOCK REGISTER*/
	volatile uint32_t  AFR[2];				/*ALTERNATE FUNCTION REGISTER*/
}GPIO_RegDef_t;

/************************     	GPIO PERIPHERAL DEFINITION			************************/
#define GPIOA				((GPIO_RegDef_t *) (GPIOA_BASE_ADDRESS))
#define GPIOB               ((GPIO_RegDef_t *) (GPIOB_BASE_ADDRESS))
#define GPIOC               ((GPIO_RegDef_t *) (GPIOC_BASE_ADDRESS))
#define GPIOD               ((GPIO_RegDef_t *) (GPIOD_BASE_ADDRESS))
#define GPIOE               ((GPIO_RegDef_t *) (GPIOE_BASE_ADDRESS))
#define GPIOF               ((GPIO_RegDef_t *) (GPIOF_BASE_ADDRESS))
#define GPIOG               ((GPIO_RegDef_t *) (GPIOG_BASE_ADDRESS))
#define GPIOH               ((GPIO_RegDef_t *) (GPIOH_BASE_ADDRESS))

/************************     	SYSTICK REGISTERS DEFINITION		************************/

typedef struct{

	volatile uint32_t	CTRL;			/*SysTick control and status register*/
	volatile uint32_t	LOAD;			/*SysTick Reload value register*/
	volatile uint32_t	VAL;			/*SysTick Current value register*/

}SYSTICK_REG_t;

#define SYSTICK 					((SYSTICK_REG_t *)(SYSTICK_BASE_ADDRESS))

/************************     	NVIC REGISTERS DEFINITION		************************/
typedef struct
{
	volatile  uint32_t NVIC_ISER[8]; 	/*The NVIC_ISER0-NVIC_ISER7 registers enable interrupts,
										and show which interrupts are enabled.*/

	volatile  uint32_t RESERVED1[24];	/*Reserved*/

	volatile  uint32_t NVIC_ICER[8];	/*The NVIC_ICER0-NVIC_ICER7 registers disable interrupts
										and show which interrupts are enabled*/

	volatile  uint32_t RESERVED2[24];   /*Reserved*/

	volatile  uint32_t NVIC_ISPR[8];	/*The NVIC_ISPR0-NVIC_ISPR7 registers force interrupts into the pending state,
	 	 	 	 	 	 	 	 	 	 and show which interrupts are pending.*/

	volatile  uint32_t RESERVED3[24];	/*Reserved*/

	volatile  uint32_t NVIC_ICPR[8];	/*The NVIC_ICPR0-NCVIC_ICPR7 registers remove the pending state from interrupts,
	 	 	 	 	 	 	 	 	 	 and show which interrupts are pending*/

	volatile  uint32_t RESERVED4[24];	/*REserved*/

	volatile  uint32_t NVIC_IABR[8];	/*The NVIC_IABR0-NVIC_IABR7 registers indicate
	 	 	 	 	 	 	 	 	 	 which interrupts are active. */

	volatile  uint32_t RESERVED5[56];	/*Reserved*/

	volatile  uint32_t NVIC_IPR[60];	/*The NVIC_IPR0-NVIC_IPR59 registers provide an 8-bit priority field for each interrupt
										and each register holds four priority fields. */

}NVIC_REG_t;
#define NVIC 	((NVIC_REG_t*)(NVIC_BASE_ADDRESS))
/************************     	PERIPHERAL REGISTER BITS DEFINITION	************************/




/************************     	ISR DEFINITIONS 					************************/



#endif /* STM32F446XX_H_ */
