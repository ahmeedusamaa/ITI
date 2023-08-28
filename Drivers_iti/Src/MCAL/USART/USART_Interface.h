/*
 * USART_Interface.h
 *
 *  Created on: Aug 24, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

#include "../../INC/Macros.h"
#include "USART_Private.h"

typedef struct
{
	uint8_t Mode;						  /*specifies TX/RX Enable/Disable
										  This parameter must be set based on @REF:USART_Mode*/
	uint8_t Word_length;              	  /*specifies word length
										  This parameter must be set based on @REF:USART_Word_length*/
	uint32_t BaudRate;					  /*specifies Baud Rate
										  This parameter must be set based on @REF UART_BaudRate*/
	uint8_t Parity_control;               /*specifies Parity control
										  This parameter must be set based on @REF:USART_Parity_control*/
	uint8_t Interrupt_Enable;			  /*specifies Interrupt Enable
										  This parameter must be set based on @REF:USART_Interrupt_Enable*/
	uint8_t STOP_bits;                    /*specifies STOP bits
										  This parameter must be set based on @REF:USART_STOP_bits*/
	uint8_t	 FlowCtl;		     		  /*specifies Flow Control
										  This parameter must be set based on @REF:UART_FlowCtl*/
	void(*CallBack)(void);

}USART_Config_t;

/**************************************************************************
*****************************reference Macros******************************
**************************************************************************/

/**********************@REF:USART_Mode**********************/
/*USART_CR1*/
#define USART_Mode_TX					(uint32_t)(1<<3)						/*Transmitter enable  */
#define USART_Mode_RX					(uint32_t)(1<<2)						/*Receiver enable*/
#define USART_Mode_TX_RX				(uint32_t)(1<<2 | 1<<2)

/**********************@REF:USART_Word_length**********************/
/*USART_CR1*/
#define USART_Word_8 					(uint32_t)(0) 							/* 0: 1 Start bit, 8 Data bits, n Stop bit */
#define USART_Word_9 					(uint32_t)(1<<12) 						/* 1: 1 Start bit, 9 Data bits, n Stop bit */

/**********************@REF UART_BaudRate**********************/
#define UART_BaudRate_1200 						1200
#define UART_BaudRate_2400 						2400
#define UART_BaudRate_9604 						9604
#define UART_BaudRate_19185 					19185
#define UART_BaudRate_38462 					38462
#define UART_BaudRate_57554 					57554
#define UART_BaudRate_115942 					115942
#define UART_BaudRate_228571 					228571
#define UART_BaudRate_470588 					470588
#define UART_BaudRate_888889 					888889

/**********************@REF:USART_Parity_control**********************/
/*USART_CR1*/
#define USART_Parity_DISABLE					(uint32_t)(0)
#define USART_Parity_ODD						(uint32_t)(1<<9 | 1<<10)
#define USART_Parity_EVEN						(uint32_t)(1<<10)

/**********************@REF:USART_Interrupt_Enable**********************/
/*USART_CR1*/ /*Enable NVIC for USARTx*/
#define USART_Interrupt_NONE					(uint32_t)(0)
#define USART_Interrupt_PEIE					(uint32_t)(1<<8)		/*PE interrupt enable*/
#define USART_Interrupt_TXEIE					(uint32_t)(1<<7)		/*TXE interrupt enable*/
#define USART_Interrupt_TCIE					(uint32_t)(1<<6)		/*Transmission complete interrupt enable*/
#define USART_Interrupt_RXNEIE					(uint32_t)(1<<5)		/*RXNE interrupt enable*/
#define USART_Interrupt_IDLEIE					(uint32_t)(1<<4)		/*IDLE interrupt enable*/

/**********************@REF:USART_STOP_bits**********************/
/*USART_CR2*/
#define USART_STOP_Bit_1							(uint32_t)(0)			/* 1 Stop bit */
#define USART_STOP_Bit_Half	    					(uint32_t)(1<<12)		/* 0.5 Stop bit */
#define USART_STOP_Bit_2							(uint32_t)(2<<12)		/* 2 Stop bit */

/**********************@REF:UART_FlowCtl**********************/
/*USART_CR3*/
#define UART_FlowCtl_CTS_Enable						(uint32_t)(1<<9)		/* 1: CTS hardware flow control enabled */
#define UART_FlowCtl_RTS_Enable						(uint32_t)(1<<8)		/* 1: RTS hardware flow control enabled */

typedef enum
{
	Enable,
	Disable
}Polling_mechanism;


#define USARTDIV(PCLK,BAUD)					(uint32_t) (PCLK/(16*BAUD))
#define USARTDIV_MUL100(PCLK,BAUD)			(uint32_t) (25*PCLK/(4*BAUD))
#define Mantissa_MUL100(PCLK,BAUD)			(uint32_t) (USARTDIV(PCLK,BAUD)*100)
#define Mantissa(PCLK,BAUD)					(uint32_t) (USARTDIV(PCLK,BAUD))
#define DIV_Fraction(PCLK,BAUD)				(uint32_t) (((USARTDIV_MUL100(PCLK,BAUD) - Mantissa_MUL100(PCLK,BAUD) ) * 16) / 100)
#define UART_BRR_Register(PCLK,BAUD)		( (Mantissa(PCLK,BAUD) ) <<4 ) | ( (DIV_Fraction(PCLK,BAUD)) & 0xF )

/*****************************APIs******************************/
void MCAL_UART_Init(USART_Registers_t* USARTx, USART_Config_t* UART_Config);
void MCAL_UART_DeInit(USART_Registers_t* USARTx);
void MCAL_UART_SendData(USART_Registers_t* USARTx, uint16_t* pTxBuffer, Polling_mechanism PollingEn );
void MCAL_UART_ReceiveData(USART_Registers_t* USARTx, uint16_t* pRxBuffer, Polling_mechanism PollingEn );

#endif /* MCAL_USART_USART_INTERFACE_H_ */
