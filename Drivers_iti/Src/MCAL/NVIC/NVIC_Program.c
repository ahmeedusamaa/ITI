/*
 * NVIC_Program.c
 *
 *  Created on: Aug 14, 2023
 *      Author: ahmed osama
 */


/****************************Includes****************************/
#include "NVIC_Private.h"
#include "NVIC_Interface.h"


/****************************Global Variables****************************/
uint8_t Global_uint8_GroupSelection ;


/****************************APIs Implementation****************************/

/**************************************************************************
 * @Fn    		: MCAL_NVIC_EnableIRQ
 * @brief 		: Enable IRQ in NVIC
 * @param [in] 	: Interrupt Index  ---> @ref: IRQn_t
 * @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
				  relevant STM32 product for related information
 **************************************************************************/
ReturnStatus MCAL_NVIC_EnableIRQ(IRQn_t  IRQn)
{

	uint8_t RegisterNumber = IRQn/32 ;
	uint8_t BitNumber = IRQn%32 ;
	NVIC->NVIC_ISER[RegisterNumber] |= (1<<BitNumber);
	return STATUS_SUCCESS;

}

/**************************************************************************
 * @Fn    		: MCAL_NVIC_DisableIRQ
 * @brief 		: Disable the IRQ in NVIC
 * @param [in] 	: Interrupt Index  ---> @ref: IRQn_t
 * @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
			      relevant STM32 product for related information
 **************************************************************************/
ReturnStatus MCAL_NVIC_DisableIRQ(IRQn_t IRQn)
{
	if(IRQ_IS_VALID(IRQn))
	{
		uint8_t RegisterNumber = IRQn/32 ;
		uint8_t BitNumber = IRQn%32 ;
		NVIC->NVIC_ICER[RegisterNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**************************************************************************
 * @Fn    		: MCAL_NVIC_SetPendingIRQ
 * @brief 		: Set IRQ pending in the NVIC
 * @param [in] 	: Interrupt Index  ---> @ref: IRQn_t
 * @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
			      relevant STM32 product for related information
 **************************************************************************/
ReturnStatus MCAL_NVIC_SetPendingIRQ(IRQn_t IRQn)
{
	if(IRQ_IS_VALID(IRQn))
	{
		uint8_t RegisterNumber = IRQn/32 ;
		uint8_t BitNumber = IRQn%32 ;
		NVIC->NVIC_ISPR[RegisterNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**************************************************************************
 * @Fn    		: MCAL_NVIC_ClearPendingIRQ
 * @brief 		: Clear IRQ pending in the NVIC
 * @param [in] 	: Interrupt Index  ---> @ref: IRQn_t
 * @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
			      relevant STM32 product for related information
 **************************************************************************/
ReturnStatus MCAL_NVIC_ClearPendingIRQ(IRQn_t IRQn)
{
	if(IRQ_IS_VALID(IRQn))
	{
		uint8_t RegisterNumber = IRQn/32 ;
		uint8_t BitNumber = IRQn%32 ;
		NVIC->NVIC_ICPR[RegisterNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**************************************************************************
 * @Fn    		: MCAL_NVIC_Is_Active
 * @brief 		: Read the state of a given IRQ_Index
 * @param [in] 	: Interrupt Index  ---> @ref: IRQn_t
 * @param [out] 	: Function State [IRQ_ACTIVE , IRQ_NOT_ACTIVE , IRQ_INVALID]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
			      relevant STM32 product for related information
 **************************************************************************/
IRQ_State_t MCAL_NVIC_IsActive(IRQn_t IRQn)
{
	if(IRQ_IS_VALID(IRQn))
	{
		uint8_t RegisterNumber = IRQn/32 ;
		uint8_t BitNumber = IRQn%32 ;
		if(GET_BIT(NVIC->NVIC_IABR[RegisterNumber] ,BitNumber) == 1)
		{
			return IRQ_ACTIVE;
		}
		else
			return IRQ_NOT_ACTIVE;

	}
	else
		return IRQ_INVALID;
}

/**************************************************************************
 * @Fn    		: MCAL_NVIC_SetGroupMode
 * @brief 		: Configure the SCB_AIRC register to select the number of groups and sub groups
 * @param [in] 	: Group Mode selection  --->@ ref:Priority_GroupsMode_t
 * @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
			      relevant STM32 product for related information
 **************************************************************************/
ReturnStatus MCAL_NVIC_SetGroupMode(Priority_Mode_t GroupMode)
{
	if(GroupMode>=PRIRORITY_16GROUP || GroupMode<=PRIORITY_16SUB )
	{
		Global_uint8_GroupSelection = GroupMode ;
		SCB_AIRCR = VECTKEY | (GroupMode<<8);
		return STATUS_SUCCESS ;
	}
	else
		return STATUS_ERROR ;

}

/**================================================================
 * @Fn    		: MCAL_NVIC_SetPriority
 * @brief 		: Configure the priority of a given peripheral
 * @param [in] 	: IRQn , group , subGroup
 * @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
 * Note			: The number of interrupts is product-dependent. Refer to reference manual/datasheet of
			      relevant STM32 product for related information
 *===================================================================*/
ReturnStatus MCAL_NVIC_SetPriority(IRQn_t IRQn ,Priority_Groups_t Group , Priority_SubGroups_t SubGroup )
{
	if( ( IRQ_IS_VALID(IRQn) ) && ( (Group>=NVIC_PRI_GROUP_0) || (Group>=NVIC_PRI_GROUP_15 ) ) && ( (SubGroup>=NVIC_PRI_SUB_GROUP_0) || (Group>=NVIC_PRI_SUB_GROUP_15) ) )
	{
		switch(Global_uint8_GroupSelection)
		{
		case PRIRORITY_16GROUP :
			NVIC->NVIC_IPR[IRQn] |= (Group<<4);break ;
		case PRIORITY_8GROUP_2SUB :
			NVIC->NVIC_IPR[IRQn] |= (Group<<5) | (SubGroup<<4); break ;
		case PRIORITY_4GROUP_4SUB  :
			NVIC->NVIC_IPR[IRQn] |= (Group<<6) | (SubGroup<<4); break ;
		case PRIORITY_2GROUP_8SUB  :
			NVIC->NVIC_IPR[IRQn] |= (Group<<7) | (SubGroup<<4); break ;
		case PRIORITY_16SUB  :
			NVIC->NVIC_IPR[IRQn] |=  (SubGroup<<4); break ;
		default :
			return STATUS_ERROR;
		}
		return STATUS_SUCCESS ;
	}
	else
	{
		STATUS_ERROR ;
	}
}
/**************************************************************************************/
