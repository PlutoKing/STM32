#ifndef __LED_H
#define __LED_H

/* Head Files */
#include "sys.h"
#include "delay.h"

/* Macro Definition */
#define LED0 PAout(6)		// D2
#define LED1 PAout(7)		// D3	 

/* Function Declaration */
void led_init(void);	
void led_test(void);
#endif
