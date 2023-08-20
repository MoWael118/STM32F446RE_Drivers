/*
 *@file		:	STM32F446xx.h
 *@author	: 	Mohamed Wael
 *@brief	:	Main Registers definition for STM32F446xx MCU
 */

#ifndef STM32F446XX_H_
#define STM32F446XX_H_



/************************	  	BASE MEMORY ADDRESSES		    	************************/
#define FLASH_BASE_ADDRESS      	0x08000000UL
#define SRAM_BASE_ADDRESS   	   	0x20000000UL
#define ROM_BASE_ADDRESS 	     	0x1FFF0000UL


/************************     	 CORE PERIPHERALS BASE ADDRESSES	************************/
#define SYSTICK_BASE_ADDRESS		0xE000E010UL
#define NVIC_BASE_ADDRESS			0xE000E100UL
#define SCB_BASE_ADDRESS			0xE000E008UL



/************************     	AHB 1 BASE PERIPHERALS ADDRESSES	************************/
#define GPIOA_BASE_ADDRESS			0x40020000UL
#define GPIOB_BASE_ADDRESS          0x40020400UL
#define GPIOC_BASE_ADDRESS          0x40020800UL
#define GPIOD_BASE_ADDRESS          0x40020C00UL
#define GPIOE_BASE_ADDRESS          0x40021000UL
#define GPIOF_BASE_ADDRESS          0x40021400UL
#define GPIOG_BASE_ADDRESS          0x40021800UL
#define GPIOH_BASE_ADDRESS          0x40021C00UL
#define DMA1_BASE_ADDRESS    		0x40026000UL
#define DMA2_BASE_ADDRESS    		0x40026400UL

/************************     	AHB 2 BASE PERIPHERALS ADDRESSES	************************/

/************************     	AHB 3 BASE PERIPHERALS ADDRESSES	************************/

/************************     	APB 1 BASE PERIPHERALS ADDRESSES	************************/
#define USART1_BASE_ADDRESS			0x40011000UL
#define USART6_BASE_ADDRESS         0x40011400UL
/************************     	APB 2 BASE PERIPHERALS ADDRESSES	************************/
#define EXTI_BASE_ADDRESS			0x40013C00UL

#define SYSCFG_BASE_ADDRESS			0x40013800UL

#define USART2_BASE_ADDRESS			0x40004400UL
#define USART3_BASE_ADDRESS         0x40004800UL
#define UART4_BASE_ADDRESS          0x40004C00UL
#define UART5_BASE_ADDRESS          0x40005000UL

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

/************************     	DMA REGISTERS DEFINITION			************************/

typedef struct {

	volatile uint32_t	LISR;		 	/*DMA low interrupt status register */
	volatile uint32_t	HISR;		 	/*DMA high interrupt status register */
	volatile uint32_t	LIFCR;		 	/*DMA low interrupt flag clear register*/
	volatile uint32_t	HIFCR;		 	/*DMA high interrupt flag clear register*/
	volatile uint32_t	STREAM[8][6];	/*8 Streams of 6 Registers 2D Array of Configuration Registers*/
}DMA_REG_t;

#define DMA1 			((DMA_REG_t	*) 	(DMA1_BASE_ADDRESS))
#define DMA2 			((DMA_REG_t	*) 	(DMA2_BASE_ADDRESS))

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

	volatile  uint8_t  NVIC_IPR[240];	/*The NVIC_IPR0-NVIC_IPR59 registers provide an 8-bit priority field for each interrupt
										and each register holds four priority fields. */

}NVIC_REG_t;
#define NVIC 	((NVIC_REG_t*)(NVIC_BASE_ADDRESS))

/************************     	SCB REGISTERS DEFINITION		************************/

typedef struct {

	volatile uint32_t SCB_ACTLR;	    /* The ACTLR register provides disable
								   	       bits for the following processor functions:
									    	• IT folding
									    	• write buffer use for accesses to the default memory map
									    	• interruption of multi-cycle instructions*/

	volatile uint32_t RESERVED1[829];	/* RESERVED	*/

	volatile uint32_t SCB_CPUID;		/*The CPUID register (RO) contains the processor part number,
										version, and implementation information*/

	volatile uint32_t SCB_ICSR;			/*The ICSR
	 	 	 	 	 	 	 	 	 	• Provides:
											– A set-pending bit for the Non-Maskable Interrupt (NMI) exception
											– Set-pending and clear-pending bits for the PendSV and SysTick exceptions
										• Indicates:
											– The exception number of the exception being processed
											– Whether there are preempted active exceptions
											– The exception number of the highest priority pending exception
											– Whether any interrupts are pending*/

	volatile uint32_t SCB_VTOR;		    /*It contains bits [29:9] of the offset of the table base
	 	 	 	 	 	 	 	 	     from memory address 0x00000000*/

	volatile uint32_t SCB_AIRCR;	    /*The AIRCR provides priority grouping control for the exception model,
									    endian status for data accesses, and reset control of the system*/

	volatile uint32_t SCB_SCR;		    /*The SCR controls features of entry to and exit from low power state*/

	volatile uint32_t SCB_CCR;		    /*The CCR controls entry to Thread mode and enables:
									    	• The handlers for NMI, hard fault and faults escalated by FAULTMASK to ignore bus faults
									    	• Trapping of divide by zero and unaligned accesses
									    	• Access to the STIR by unprivileged software,*/

	volatile uint32_t SCB_SHPR[3];	    /*The SHPR1-SHPR3 registers set the priority level, 0 to 255 of the exception handlers that
									    have configurable priority*/

	volatile uint32_t SCB_SHCSR;		/*The SHCSR enables the system handlers, and indicates:
											• The pending status of the bus fault, memory management fault, and SVC exceptions
											• The active status of the system handlers*/

	volatile uint32_t SCB_CFSR;			/*The CFSR indicates the cause of a memory management fault, bus fault, or usage fault*/

	volatile uint32_t SCB_HFSR;			/*The HFSR gives information about events that activate the hard fault handler. */

	volatile uint32_t RESERVED[2];		/*RESERVED*/

	volatile uint32_t SCB_MMAR;			/*this field holds the address of the
										location that generated the memory management fault*/

	volatile uint32_t SCB_BFAR;			/*this field holds the address of the location
										that generated the bus fault*/

	volatile uint32_t SCB_AFSR;			/*The AFSR contains additional system fault information. */

}SCB_REG_t;

#define SCB 	((SCB_REG_t *)(SCB_BASE_ADDRESS))

/************************     	EXTI REGISTERS DEFINITION		************************/

typedef struct {

	volatile uint32_t EXTI_IMR; /*Interrupt mask register, used to enable or disable EXTI Lines*/

	volatile uint32_t EXTI_EMR; /*Event mask register ,used to enable or disable EXTI Lines*/

	volatile uint32_t EXTI_RTSR;/*Rising trigger selection register ,Used enable rising edge trigger*/

	volatile uint32_t EXTI_FTSR;/*Falling trigger selection register, Used enable falling edge trigger*/

	volatile uint32_t EXTI_SWIER; /*Software interrupt event register,
									If interrupt are enabled on line x in the EXTI_IMR register,
									writing '1' to SWIERx bit when it is
									set at '0' sets the corresponding pending bit in EXTI_PR register,
 	 	 	 	 	 	 	 	 	thus resulting in an interrupt request generation.*/

	volatile uint32_t EXTI_PR;	 /* Pending register, used to read and clear Pending Flags state*/


}EXTI_REG_t;
#define EXTI 	((EXTI_REG_t*)(EXTI_BASE_ADDRESS))

/************************     	SYSCFG REGISTERS DEFINITION		************************/

typedef struct {

	volatile uint32_t SYSCFG_MEMRMP;	/*This register is used for specific configurations on memory remap*/

	volatile uint32_t SYSCFG_PMC;		/*SYSCFG peripheral mode configuration register */

	volatile uint32_t SYSCFG_EXTICR[4]; /*SYSCFG external interrupt configuration register,
										These Registers are written by software to select the
										source input (PORT) for the EXTIx external interrupt*/

	volatile uint32_t RESERVED1[2];

	volatile uint32_t SYSCFG_CMPCR;		/*Compensation cell control register , Used to enable Compensation cell */

	volatile uint32_t RESERVED2[2];

	volatile uint32_t SYSCFG_CFGR;		/*SYSCFG configuration register */

}SYSCFG_REG_t;
#define SYSCFG 	((SYSCFG_REG_t*)(SYSCFG_BASE_ADDRESS))

/************************     	UART/USART REGISTERS DEFINITION		************************/
typedef struct {

	volatile uint32_t USART_SR;			/*USART Status Register*/
	volatile uint32_t USART_DR;			/*USART DATA REGISTER*/
	volatile uint32_t USART_BRR;		/*USART BaudRate Register*/
	volatile uint32_t USART_CR1;		/*USART Control Register 1*/
	volatile uint32_t USART_CR2;		/*USART Control Register 2*/
	volatile uint32_t USART_CR3;		/*USART Control Register 3*/
	volatile uint32_t USART_GTPR		/*USART Guard Time and Prescaler Register*/
	;
}USART_REG_t;

#define USART1				((USART_REG_t * )(USART1_BASE_ADDRESS))
#define USART2				((USART_REG_t * )(USART2_BASE_ADDRESS))
#define USART3				((USART_REG_t * )(USART3_BASE_ADDRESS))
#define UART4				((USART_REG_t * )(UART4_BASE_ADDRESS))
#define UART5				((USART_REG_t * )(UART5_BASE_ADDRESS))
#define USART6				((USART_REG_t * )(USART6_BASE_ADDRESS))

/************************     	PERIPHERAL REGISTER BITS DEFINITION	************************/




/************************     	ISR DEFINITIONS 					************************/



#endif /* STM32F446XX_H_ */
