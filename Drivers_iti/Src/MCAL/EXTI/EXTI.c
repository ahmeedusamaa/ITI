/*
 * EXTI.c
 *
 *  Created on: Aug 19, 2023
 *      Author: ahmed osama
 */

/********************Includes********************/
#include"../../INC/Macros.h"
#include"../../INC/STD_TYPES.h"
#include"EXTI_Interface.h"
#include"EXTI_Private.h"

/*******************************************
 *
 *
 *
 *
 * Enable the SYSCFG peripheral clock:
 *
 *
 *
 *
 ****************************************************/


/************************Global Variables************************/
void (*ptr[15])(void)={NULL};

/*
	Hardware interrupt selection
	To configure the 23 lines as interrupt sources, use the following procedure:
	• Configure the mask bits of the 23 interrupt lines (EXTI_IMR)
	• Configure the Trigger selection bits of the interrupt lines (EXTI_RTSR and EXTI_FTSR)
	• Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
	external interrupt controller (EXTI) so that an interrupt coming from one of the 23 lines
	can be correctly acknowledged.
 */
ReturnStatus MCAL_EXTI_Enable(EXTI_Config_t  *Configuration)
{
	SET_BIT(EXTI->EXTI_IMR,Configuration->EXTI_LineSelection);
	if(Configuration->EXTI_EdgeSelection==EXTI_RISING_EDGE)
	{
		SET_BIT(EXTI->EXTI_RTSR,Configuration->EXTI_LineSelection);
	}
	else if(Configuration->EXTI_EdgeSelection==EXTI_FALLING_EDGE)
	{
		SET_BIT(EXTI->EXTI_FTSR,Configuration->EXTI_LineSelection);
	}
	else if(Configuration->EXTI_EdgeSelection==EXTI_ON_CHANGE)
	{
		SET_BIT(EXTI->EXTI_RTSR,Configuration->EXTI_LineSelection);
		SET_BIT(EXTI->EXTI_FTSR,Configuration->EXTI_LineSelection);
	}
	switch(Configuration->EXTI_LineSelection)
	{
	case 0:
	case 1:
	case 2:
	case 3:		SYSCFG_EXTI0_3(Configuration->EXTI_PortSelection,(Configuration->EXTI_LineSelection % 4)); break;

	case 4:
	case 5:
	case 6:
	case 7:		SYSCFG_EXTI4_7(Configuration->EXTI_PortSelection,(Configuration->EXTI_LineSelection % 4)); break;

	case 8:
	case 9:
	case 10:
	case 11:	SYSCFG_EXTI8_11(Configuration->EXTI_PortSelection,(Configuration->EXTI_LineSelection % 4)); break;

	case 12:
	case 13:
	case 14:
	case 15:	SYSCFG_EXTI12_15(Configuration->EXTI_PortSelection,(Configuration->EXTI_LineSelection % 4)); break;

	default:	        break;
	}
	ptr[Configuration->EXTI_LineSelection] = Configuration->CallBack;
	return STATUS_SUCCESS;
}




ReturnStatus MCAL_EXTI_Disable(EXTI_Config_t *Configuration)
{
	CLR_BIT(EXTI->EXTI_IMR,Configuration->EXTI_LineSelection);
	return STATUS_SUCCESS;

}

void EXTI0_IRQHandler(void)
{

	SET_BIT(EXTI->EXTI_PR,0);
	ptr[0]();
}
void EXTI1_IRQHandler(void)
{

	SET_BIT(EXTI->EXTI_PR,1);
	ptr[1]();
}
