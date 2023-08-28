/*
 * EXTI_Private.h
 *
 *  Created on: Aug 19, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

/********************Includes********************/
#include "../../INC/STD_TYPES.h"

/********************Base Addresses********************/
#define EXTI_BASE_ADDRESS			0x40013C00
#define SYSCFG_BASE_ADDRESS			0x40013800

/********************Structure********************/

typedef struct
{
	volatile uint32_t EXTI_IMR  ;
	volatile uint32_t EXTI_EMR  ;
	volatile uint32_t EXTI_RTSR ;
	volatile uint32_t EXTI_FTSR ;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR   ;



}EXTI_Registers_t;

typedef struct
{
	volatile uint32_t SYSCFG_MEMRMP  ;
	volatile uint32_t SYSCFG_PMC     ;
	volatile uint32_t SYSCFG_EXTICR1 ;
	volatile uint32_t SYSCFG_EXTICR2 ;
	volatile uint32_t SYSCFG_EXTICR3 ;
	volatile uint32_t SYSCFG_EXTICR4 ;
	volatile uint32_t Reserved		 ;
	volatile uint32_t SYSCFG_CMPCR   ;

}SYSCFG_Registers_t;


/********************Peripherals Instances********************/
#define EXTI 	((volatile EXTI_Registers_t*)EXTI_BASE_ADDRESS)
#define SYSCFG 	((volatile SYSCFG_Registers_t*)SYSCFG_BASE_ADDRESS)

/********************Configuration Macros********************/
#define SYSCFG_EXTI0_3(PORTn,Line)					(SYSCFG->SYSCFG_EXTICR1 |= (PORTn<<(Line*4)))
#define SYSCFG_EXTI4_7(PORTn,Line)					(SYSCFG->SYSCFG_EXTICR2 |= (PORTn<<(Line*4)))
#define SYSCFG_EXTI8_11(PORTn,Line)					(SYSCFG->SYSCFG_EXTICR3 |= (PORTn<<(Line*4)))
#define SYSCFG_EXTI12_15(PORTn,Line)				(SYSCFG->SYSCFG_EXTICR4 |= (PORTn<<(Line*4)))




#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
