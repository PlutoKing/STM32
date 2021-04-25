/** --------------------------------------------------
* @Project	: Lanfeng Intelligent Flight(LFIF)
* @Version	: V 2.0 (Test Version)
* @Hardware	: STM32F4XX
* @Author	: Xu Zhe
* @Date		: 2020-09-08
* @Brief	: Communication Test
			  MPU9250 Test
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
