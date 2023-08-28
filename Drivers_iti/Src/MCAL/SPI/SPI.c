/*
 * SPI.c
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmed osama
 */

#include "SPI_Private.h"
#include "SPI_Interface.h"

/****************************Global Variables*****************************/
SPI_Config_t* Global_SPI_Config;


/****************************APIs*****************************/
void MCAL_SPI_Init(SPI_Registers_t* SPIx, SPI_Config_t* SPI_Config)
{

	/******************************************************/
	/*try Safety for registers*/
	/******************************************************/

	Global_SPI_Config = SPI_Config;

	/*specifies Master/Slave selection*/
	SPIx->SPI_CR1 |= SPI_Config->Mode;

	/*specifies data directional mode*/
	SPIx->SPI_CR1 |= SPI_Config->Communication_Mode;

	/*specifies Data frame format*/
	SPIx->SPI_CR1 |= SPI_Config->Data_frame;

	/*specifies NSS*/
	/*Software slave management disabled*/
	if(SPI_Config->NSS==SPI_NSS_Hardware_slave)
	{
		SPIx->SPI_CR1 |= SPI_Config->NSS;
	}
	/*output is disabled in master mode and the cell can work in multimaster configuration*/
	else if(SPI_Config->NSS==SPI_NSS_Hardware_Master_SS_output_disabled)
	{
		SPIx->SPI_CR2 &= SPI_Config->NSS;
	}
	/*output is enabled in master mode and when the cell is enabled. The cell cannot work in a multimaster environment.*/
	else if(SPI_Config->NSS==SPI_NSS_Hardware_Master_SS_output__Enable)
	{
		SPIx->SPI_CR2 |= SPI_Config->NSS;
	}
	else if(SPI_Config->NSS==SPI_NSS_Software_Internal_reset)
	{
		SPIx->SPI_CR1 |= SPI_Config->NSS;
	}
	else if(SPI_Config->NSS==SPI_NSS_Software_Internal_set)
	{
		SPIx->SPI_CR1 |= SPI_Config->NSS;
	}

	/*specifies MSB/LSB  transmitted first*/
	SPIx->SPI_CR1 |= SPI_Config->Frame_format;

	/*specifies Baud rate control*/
	SPIx->SPI_CR1 |= SPI_Config->Prescaler;

	/*specifies Clock polarity*/
	SPIx->SPI_CR1 |= SPI_Config->Clock_polarity;

	/*specifies Clock phase*/
	SPIx->SPI_CR1 |= SPI_Config->Clock_phase;

	/*specifies Interrupt Enable*/
	SPIx->SPI_CR2 |= SPI_Config->IRQ_Enable;

	/*SPI enable*/
	SPIx->SPI_CR1 |= (1<<6);
}
void MCAL_SPI_DeInit(SPI_Registers_t* SPIx)
{

}
void MCAL_SPI_SendData(SPI_Registers_t* SPIx, uint16_t *TxPuffer, Polling_mechanism PollingEn)
{
	/*
	 *  The transmit sequence begins when a byte is written in the Tx Buffer.
	 *	The data byte is parallel-loaded into the shift register (from the internal bus) during the first
	 *	bit transmission and then shifted out serially to the MOSI pin MSB first or LSB first
	 *	depending on the LSBFIRST bit in the SPI_CR1 register. The TXE flag is set on the transfer
	 *	of data from the Tx Buffer to the shift register and an interrupt is generated if the TXEIE bit in
	 *	the SPI_CR2 register is set.
	 */
	if(PollingEn==PollingEnable)
	{
		/*wait until TXE not empty*/
		while( !( (SPIx->SPI_SR >> 1) & 0x1) );
	}

	/*Data transmitted*/
	if(Global_SPI_Config->Data_frame == SPI_Data_frame_8Bit)
	{
		SPIx->SPI_DR = (*TxPuffer & 0xFF);
	}
	if(Global_SPI_Config->Data_frame == SPI_Data_frame_16Bit)
	{
		SPIx->SPI_DR = (*TxPuffer & 0xFFFF);
	}

}
void MCAL_SPI_ReceiveData(SPI_Registers_t* SPIx, uint16_t *RxPuffer, Polling_mechanism PollingEn)
{
	/*Clear the MSTR bit and set the SPE bit (both in the SPI_CR1 register) to assign the
	pins to alternate functions.*/

	if(PollingEn==PollingEnable)
	{
		/*The Data in shift register is transferred to Rx Buffer and the RXNE flag (SPI_SR
	register) is set*/
		while(!(SPIx->SPI_SR & 0x1));
	}

	/*Data transmitted*/
	if(Global_SPI_Config->Data_frame == SPI_Data_frame_8Bit)
	{
		*RxPuffer = (SPIx->SPI_DR & 0xFF);
	}
	if(Global_SPI_Config->Data_frame == SPI_Data_frame_16Bit)
	{
		*RxPuffer = (SPIx->SPI_DR & 0xFFFF);
	}

}



void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC IRQ_SRC;
	IRQ_SRC.TXE=	((SPI1->SPI_SR >> 1) & 0x1);
	IRQ_SRC.RXNE=	((SPI1->SPI_SR >> 0) & 0x1);

	Global_SPI_Config->CALLBACK(IRQ_SRC);
}



