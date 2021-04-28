/** --------------------------------------------------
* @Project	: Lanfeng STM32 Project(LFSTM32)
* @Version	: V 1.0
* @Hardware	: STM32F4XX
* @Author	: Xu Zhe
* @Date		: 2021-04-25
* @Brief	: 00-Template
---------------------------------------------------*/

/* Head Files */
#include "delay.h"
#include "USART1.h"
#include "led.h"

/** --------------------------------------------------
* @Function	: main
* @Brief	: Main function for this project.
* @param	: void
* @return	: int
---------------------------------------------------*/
int main(void)
{
	u8 t,len;
	delay_init(168);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	usart1_init(115200);
	
	led_init();
	
	while(1)
	{
		led_test();
		if(USART_RX_STA&0x8000)
		{
			len = USART_RX_STA&0x3fff;
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);
			}
			USART_RX_STA=0;
		}
		
		USART1->DR=0xAA;
	}
}
