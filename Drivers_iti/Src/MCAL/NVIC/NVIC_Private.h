/*
 * NVIC_Private.h
 *
 *  Created on: Aug 14, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_


#include "../../INC/STD_TYPES.h"

/***************************************************************/
typedef struct {

	volatile uint32_t NVIC_ISER[8] 		;
	volatile uint32_t RESERVED0[24]		;
	volatile uint32_t NVIC_ICER[8]		;
	volatile uint32_t RESERVED1[24]		;
	volatile uint32_t NVIC_ISPR[8]		;
	volatile uint32_t RESERVED2[24]		;
	volatile uint32_t NVIC_ICPR [8]		;
	volatile uint32_t RESERVED3[24]		;
	volatile uint32_t NVIC_IABR[8]		;
	volatile uint32_t RESERVED4[56]		;
	volatile uint8_t NVIC_IPR[240]		;
	volatile uint32_t RESERVED5[580] 	;
	volatile uint32_t NVIC_STIR			;
}NVIC_Registers_t;

/************************Base addresses***********************/
#define NVIC_BASE_ADDRESS	(0xE000E100)
#define SCB_BASE		(0xE000ED00)

/**********************Instant***********************/
#define NVIC	((volatile NVIC_Registers_t*)NVIC_BASE_ADDRESS)


/*********SCB Interrupt Priority Register*****************/
#define SCB_AIRCR	*((volatile uint32_t *)(SCB_BASE+0x0C))

/*********************************************************/
#define VECTKEY			(0x5FA)

/**********************Macros*********************/
#define IRQ_IS_VALID(IRQn)	  ( ((IRQn>=0)&&(IRQn<=18)) || \
								((IRQn>=23)&&(IRQn<=38)) || \
							    ((IRQn>=40)&&(IRQn<=42)) || \
								((IRQn==47))			 || \
								((IRQn>=49)&&(IRQn<=51)) || \
								((IRQn>=56)&&(IRQn<=60)) || \
								((IRQn>=67)&&(IRQn<=73)) || \
								((IRQn==81)) 			 || \
								((IRQn==84))			      )


typedef enum {
	IRQ_NOT_ACTIVE ,
	IRQ_ACTIVE ,
	IRQ_INVALID
}IRQ_State_t;


#endif /* MCAL_NVIC_NVIC_PRIVATE_H_ */
