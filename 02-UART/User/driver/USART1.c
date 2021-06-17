/****************************************************
@FileName		: USART1.c
@Author			: Xu Zhe
@Version		: 1.0
@CreateDate		: 2020-09-16
@Description	: USART1
@History		: 
*****************************************************/

/* Head Files */
#include "usart1.h"

u16 USART_RX_STA = 0;
u8 USART_RX_BUF[USART_REC_LEN];

/** --------------------------------------------------
* @Function	: 
* @Brief	: 
* @param	: void
* @return	: void
---------------------------------------------------*/
void usart1_init(u32 baudrate)
{
	/* 0. Definitions */
	GPIO_InitTypeDef GPIO_Config;	// Define the GPIO configuration struct
	USART_InitTypeDef UART_Config;	// Define the UART configuration struct
	NVIC_InitTypeDef NVIC_Config;	// Define the NVIC configuration struct

	/* 1. Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	// Enable GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	// Enable USART1 clock

	/* 2. Mapping */
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	/* 3. GPIO Config */
	GPIO_Config.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;	// Pin
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF;				// Alternative function
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;			// 50M
	GPIO_Config.GPIO_OType = GPIO_OType_PP;				// Push-pull
	GPIO_Config.GPIO_PuPd = GPIO_PuPd_UP;				// High level
	GPIO_Init(GPIOA,&GPIO_Config);						// Initialize the GPIO config

	/* 4. UART Config */
	UART_Config.USART_BaudRate = baudrate;				// Baud rate
	UART_Config.USART_WordLength = USART_WordLength_8b;	// Data bit
	UART_Config.USART_StopBits = USART_StopBits_1;		// Stop bit
	UART_Config.USART_Parity = USART_Parity_No;			// Parity
	UART_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_Config.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&UART_Config);
	USART_Cmd(USART1,ENABLE);
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	/* 5. NVIC Config */
	NVIC_Config.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Config.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Config.NVIC_IRQChannelSubPriority = 2;
	NVIC_Config.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Config);
}

/*--------------------------------------------------
* @Function	: USART1_IRQHandler
* @Brief	: Interruption function for USART1.
* @param	: void
* @return	: void
---------------------------------------------------*/
void USART1_IRQHandler(void)
{
	u8 res;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		res = USART_ReceiveData(USART1);
		if((USART_RX_STA & 0X8000) == 0)
		{
			if(USART_RX_STA & 0x4000)
			{
				if(res != 0x0A)
					USART_RX_STA = 0;
				else
					USART_RX_STA |= 0x8000;
			}
			else
			{
				if(res == 0x0d)
					USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF] = res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA = 0;
				}
			}
		}
	}
}
