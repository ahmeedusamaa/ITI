/*
 * USART_Private.h
 *
 *  Created on: Aug 24, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_

#include "../../INC/STD_TYPES.h"

/************************USART Registers Structure*****************/
typedef struct
{
	volatile uint32_t USART_SR		;
	volatile uint32_t USART_DR	    ;
	volatile uint32_t USART_BRR     ;
	volatile uint32_t USART_CR1     ;
	volatile uint32_t USART_CR2     ;
	volatile uint32_t USART_CR3     ;
	volatile uint32_t USART_GTPR    ;

}USART_Registers_t;

/************************USART Base Addresses*****************/
#define USART1_BASE			0x40011000
#define USART2_BASE			0x40004400
#define USART6_BASE			0x40011400

/***************************USART Instance************************************/
#define USART1				((volatile USART_Registers_t *)USART1_BASE)
#define USART2				((volatile USART_Registers_t *)USART2_BASE)
#define USART6				((volatile USART_Registers_t *)USART6_BASE)


#endif /* MCAL_USART_USART_PRIVATE_H_ */
