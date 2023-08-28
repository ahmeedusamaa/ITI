/*
 * USART.c
 *
 *  Created on: Aug 24, 2023
 *      Author: ahmed osama
 */

#include "USART_Private.h"
#include "USART_Interface.h"

/****************************Global Variables*****************************/
static void (*GlobalcallBack)(void) = NULL ;
USART_Config_t* GLOBAL_UART_Config = NULL;



void MCAL_UART_Init(USART_Registers_t* USARTx, USART_Config_t* UART_Config)
{
	GLOBAL_UART_Config = UART_Config;
	uint32_t BRR, pclk;

	/*USART enable*/
	USARTx->USART_CR1 |= (1<<13);

	/*specifies TX/RX Enable/Disable*/
	USARTx->USART_CR1 |= UART_Config->Mode;

	/*Configuration of word length*/
	USARTx->USART_CR1 |= UART_Config->Word_length;

	/*Configuration of Parity control*/
	USARTx->USART_CR1 |= UART_Config->Parity_control;

	/*Configuration of STOP bits*/
	USARTx->USART_CR2 |= UART_Config->STOP_bits;

	/*Configuration of Flow Control*/
	USARTx->USART_CR3 |= UART_Config->FlowCtl;

	/*Configuration of Baud Rate*/
	if(USARTx==USART1)
	{
		pclk=MCAL_Get_APB2_CLK();
	}
	else if(USARTx==USART2)
	{
		pclk=MCAL_Get_APB1_CLK();

	}
	else if(USARTx==USART6)
	{
		pclk=MCAL_Get_APB2_CLK();

	}
	BRR = UART_BRR_Register(pclk,UART_Config->BaudRate);
	USARTx->USART_BRR = BRR ;

	/*Enable Interrupt*/
	if(UART_Config->Interrupt_Enable != USART_Interrupt_NONE)
	{
		USARTx->USART_CR1 |= UART_Config->Interrupt_Enable;
		/*Enable NVIC for USARTx*/
	}
}

void MCAL_UART_SendData(USART_Registers_t* USARTx, uint16_t* pTxBuffer, Polling_mechanism PollingEn )
{
	if (PollingEn==Enable)
	{
		/*Wait until Transmit data register empty*/
		while(!((USARTx->USART_SR >> 7) & 0x1));
	}
	/*When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register), the
		value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because
		it is replaced by the parity.*/
	if(GLOBAL_UART_Config->Word_length == USART_Word_8)
	{
		USARTx->USART_DR = (*pTxBuffer & (uint16_t)0xFF);
	}
	else if(GLOBAL_UART_Config->Word_length == USART_Word_9)
	{
		USARTx->USART_DR = (*pTxBuffer & (uint16_t)0x1FF);
	}
	/*Transmission complete*/
	while(!((USARTx->USART_SR >> 6) & 0x1));

}
void MCAL_UART_ReceiveData(USART_Registers_t* USARTx, uint16_t* pRxBuffer, Polling_mechanism PollingEn )
{
	if (PollingEn==Enable)
	{
		/*Wait until Read data register not empty*/
		while(!((USARTx->USART_SR >> 5) & 0x1));
	}
	/*When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register), the
	      value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because
	      it is replaced by the parity.*/
	if(GLOBAL_UART_Config->Word_length == USART_Word_8)
	{
		if(GLOBAL_UART_Config->Parity_control == USART_Parity_DISABLE)
		{
			*pRxBuffer = (USARTx->USART_DR & (uint16_t)0xFF);
		}
		else
		{
			*pRxBuffer = (USARTx->USART_DR & (uint16_t)0x7F);
		}
	}
	else if(GLOBAL_UART_Config->Word_length == USART_Word_9)
	{
		if(GLOBAL_UART_Config->Parity_control == USART_Parity_DISABLE)
		{
			*pRxBuffer = (USARTx->USART_DR & (uint16_t)0x1FF);
		}
		else
		{
			*pRxBuffer = (USARTx->USART_DR & (uint16_t)0xFF);
		}
	}

}

