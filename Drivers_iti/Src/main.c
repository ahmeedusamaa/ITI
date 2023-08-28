#include"MCAL/RCC/RCC_Interface.h"
#include"MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"

void MyISR(void)
{
	MCAL_GPIOx_Pin_Toggle(GPIOA, GPIO_PIN_0);
}
int main()
{
	RCC_Config_t MyRCC ;
	MyRCC.RCC_SYS_CLK 	 =  HSI;
	MyRCC.RCC_PERIPHERAL = GPIOA_PERIPHERAL ;
	//MyRCC.RCC_HSE_MODE = HSE_MODE_BYPASS ;
	MyRCC.RCC_BUS_SELECT = AHB1_BUS  ;
	MCAL_RCC_voidInit(&MyRCC);
	MCAL_RCC_voidPeripheral_EN(MyRCC.RCC_PERIPHERAL,MyRCC.RCC_BUS_SELECT );
	MyRCC.RCC_PERIPHERAL = GPIOB_PERIPHERAL ;
	MCAL_RCC_voidPeripheral_EN(MyRCC.RCC_PERIPHERAL,MyRCC.RCC_BUS_SELECT);
	MyRCC.RCC_BUS_SELECT = APB2_BUS  ;
	MyRCC.RCC_PERIPHERAL = SYSCFG_PERIPHERAL ;
	MCAL_RCC_voidPeripheral_EN(MyRCC.RCC_PERIPHERAL,MyRCC.RCC_BUS_SELECT);

	GPIOx_Config_t MyGPIO	;

	/******************Output***************/
	MyGPIO.GPIO_PIN_MODE = GPIO_OUT_PP;
	MyGPIO.GPIO_PIN_NUMBER = GPIO_PIN_0;
	MyGPIO.GPIO_PIN_OUT_SPEED = GPIO_OUT_SPEED_LOW ;
	MCAL_GPIOx_Init(GPIOA ,&MyGPIO);


	/*****************Input*****************/
	MyGPIO.GPIO_PIN_MODE = GPIO_INPUT_FLOAT;
	MyGPIO.GPIO_PIN_NUMBER = GPIO_PIN_0;
	MCAL_GPIOx_Init(GPIOB ,&MyGPIO);
	/****************************************/
	EXTI_Config_t MyEXTI ;
	MyEXTI.EXTI_StateSelection = EXTI_ENABLE ;
	MyEXTI.EXTI_PortSelection = EXTI_PORTB ;
	MyEXTI.EXTI_LineSelection = EXTI_LINE_0 ;
	MyEXTI.EXTI_EdgeSelection = EXTI_ON_CHANGE ;
	MyEXTI.CallBack = MyISR ;
	MCAL_EXTI_Enable(&MyEXTI);
	/*****************************************/
	MCAL_NVIC_EnableIRQ(EXTI0);
	/*****************************************/



	while (1)
	{
	}
	return 0;
}
