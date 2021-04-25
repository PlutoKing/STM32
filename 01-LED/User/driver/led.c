/****************************************************
@FileName		: led.c
@Author			: Xu Zhe
@Version		: 1.0
@CreateDate		: 2020-09-08
@Description	: Initialize LED and design the light.
@History		: 
*****************************************************/

/* Head Files */
#include "led.h" 

/** --------------------------------------------------
* @Function	: LED_Init
* @Brief	: Initialize the GPIO for LED.
* @param	: void
* @return	: void
---------------------------------------------------*/
void led_init(void)
{
	/* 1. Definitions */
	GPIO_InitTypeDef  GPIO_Config;

	/* 2. Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// enable GPIOA clock

	/* 3. GPIO Config */
	GPIO_Config.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;		// pin
	GPIO_Config.GPIO_Mode = GPIO_Mode_OUT;				// alternative function
	GPIO_Config.GPIO_Speed = GPIO_Speed_100MHz;			// 50M
	GPIO_Config.GPIO_OType = GPIO_OType_PP;				// push-pull
	GPIO_Config.GPIO_PuPd = GPIO_PuPd_UP;				// high level
	GPIO_Init(GPIOA,&GPIO_Config);						// initialize the GPIO config
	
	/* 4. Initial State */
	GPIO_SetBits(GPIOA,GPIO_Pin_6 | GPIO_Pin_7);		// high level, led off
}

/** --------------------------------------------------
* @Function	: LED_Test
* @Brief	: LedS take place by turn to flash for testing led.
* @param	: void
* @return	: void
---------------------------------------------------*/
void led_test(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_6); 	// d2 on
	GPIO_SetBits(GPIOA,GPIO_Pin_7);		// d3 off
	delay_ms(500); 
	GPIO_SetBits(GPIOA,GPIO_Pin_6); 	// d2 off
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);	// d3 on
	delay_ms(500);

}
