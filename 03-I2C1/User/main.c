/** --------------------------------------------------
* @Project	: Lanfeng STM32 Project(LFSTM32)
* @Version	: V 1.0
* @Hardware	: STM32F4XX
* @Author	: Xu Zhe
* @Date		: 2021-04-25
* @Brief	: 01-LED Test
---------------------------------------------------*/

/* Head Files */
#include "delay.h"
#include "led.h"

/** --------------------------------------------------
* @Function	: main
* @Brief	: Main function for this project.
* @param	: void
* @return	: int
---------------------------------------------------*/
int main(void)
{
	delay_init(168);
	led_init();
	while(1)
	{
		led_test();
	}
}
