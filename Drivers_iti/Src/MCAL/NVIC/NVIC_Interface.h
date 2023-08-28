/*
 * NVIC_Interface.h
 *
 *  Created on: Aug 14, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_


/**********************Includes**********************/
#include "../../INC/Macros.h"
#include "../../INC/STD_TYPES.h"
#include "NVIC_Private.h"



/*@ref:IVT */
typedef enum {
	WWDG = 0 						,
	EXTI16_OR_PVD 					,
	EXTI21_OR_TAMP_STAMP 			,
	EXTI22_OR_RTC_WKUP 				,
	FLASH							,
	RCC								,
	EXTI0							,
	EXTI1							,
	EXTI2							,
	EXTI3							,
	EXTI4							,
	DMA1_Stream0					,
	DMA1_Stream1					,
	DMA1_Stream2					,
	DMA1_Stream3					,
	DMA1_Stream4					,
	DMA1_Stream5					,
	DMA1_Stream6					,
	ADC								,
	EXTI9_5 = 23					,
	TIM1_BRK_TIM9					,
	TIM1_UP_TIM10					,
	TIM1_TRG_COM_TIM_11				,
	TIM1_CC							,
	TIM2							,
	TIM3							,
	TIM4							,
	I2C1_EV							,
	I2C1_ER							,
	I2C2_EV							,
	I2C2_ER							,
	SPI1							,
	SPI2							,
	USART1							,
	USART2							,
	EXTI15_10 = 40  				,
	EXTI17_OR_RTC_Alarm				,
	EXTI18_OTG_FS_WKUP				,
	DMA1_Stream7 = 47				,
	SDIO = 49						,
	TIM5							,
	SPI3							,
	DMA2_Stream0 = 56				,
	DMA2_Stream1					,
	DMA2_Stream2					,
	DMA2_Stream3					,
	DMA2_Stream4					,
	OTG_FS = 67						,
	DMA2_Stream5					,
	DMA2_Stream6					,
	DMA2_Stream7					,
	USART6							,
	I2C3_EV							,
	I2C3_ER							,
	FPU = 81						,
	SPI4 = 84
}IRQn_t;


/* @ref: Priority */
typedef enum {
	PRIRORITY_16GROUP = 3 ,
	PRIORITY_8GROUP_2SUB  ,
	PRIORITY_4GROUP_4SUB  ,
	PRIORITY_2GROUP_8SUB  ,
	PRIORITY_16SUB
}Priority_Mode_t;


/*@ref: Priority Groups Reference*/
typedef enum {
	NVIC_PRI_GROUP_0 ,
	NVIC_PRI_GROUP_1 ,
	NVIC_PRI_GROUP_2 ,
	NVIC_PRI_GROUP_3 ,
	NVIC_PRI_GROUP_4 ,
	NVIC_PRI_GROUP_5 ,
	NVIC_PRI_GROUP_6 ,
	NVIC_PRI_GROUP_7 ,
	NVIC_PRI_GROUP_8 ,
	NVIC_PRI_GROUP_9 ,
	NVIC_PRI_GROUP_10 ,
	NVIC_PRI_GROUP_11 ,
	NVIC_PRI_GROUP_12 ,
	NVIC_PRI_GROUP_13 ,
	NVIC_PRI_GROUP_14 ,
	NVIC_PRI_GROUP_15 ,

}Priority_Groups_t;

/* @ref: Priority Sub Group Reference*/
typedef enum {
	NVIC_PRI_SUB_GROUP_0 ,
	NVIC_PRI_SUB_GROUP_1 ,
	NVIC_PRI_SUB_GROUP_2 ,
	NVIC_PRI_SUB_GROUP_3 ,
	NVIC_PRI_SUB_GROUP_4 ,
	NVIC_PRI_SUB_GROUP_5 ,
	NVIC_PRI_SUB_GROUP_6 ,
	NVIC_PRI_SUB_GROUP_7 ,
	NVIC_PRI_SUB_GROUP_8 ,
	NVIC_PRI_SUB_GROUP_9 ,
	NVIC_PRI_SUB_GROUP_10 ,
	NVIC_PRI_SUB_GROUP_11 ,
	NVIC_PRI_SUB_GROUP_12 ,
	NVIC_PRI_SUB_GROUP_13 ,
	NVIC_PRI_SUB_GROUP_14 ,
	NVIC_PRI_SUB_GROUP_15 ,

}Priority_SubGroups_t;

/**********************APIs Supported by "MCAL NVIC DRIVER"**********************/
ReturnStatus MCAL_NVIC_EnableIRQ(IRQn_t  IRQn);
ReturnStatus MCAL_NVIC_DisableIRQ(IRQn_t IRQn);
ReturnStatus MCAL_NVIC_SetPendingIRQ(IRQn_t IRQn);
ReturnStatus MCAL_NVIC_ClearPendingIRQ(IRQn_t IRQn);
IRQ_State_t MCAL_NVIC_IsActive(IRQn_t IRQn);
ReturnStatus MCAL_NVIC_SetGroupMode(Priority_Mode_t GroupMode);
ReturnStatus MCAL_NVIC_SetPriority(IRQn_t IRQn ,Priority_Groups_t group , Priority_SubGroups_t subGroup );


#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
