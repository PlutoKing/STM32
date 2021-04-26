/****************************************************
@FileName		: delay.c
@Author			: 
@Version		: 1.0
@CreateDate		: 2020-09-09
@Description	: Functions about delay.
@History		: 
*****************************************************/

/* Head Files */
#include "delay.h"


/* Variables */
static u8  fac_us=0;	// us
static u16 fac_ms=0;	// ms

			   
/** --------------------------------------------------
* @Function	: delay_init
* @Brief	: Initialize delay.
* @param	: SYSCLK : clock of system
* @return	: void
---------------------------------------------------*/
void delay_init(u8 SYSCLK)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SYSCLK/8;		
	fac_ms=(u16)fac_us*1000;
}	


/** --------------------------------------------------
* @Function	: delay_us
* @Brief	: 
* @param	: nus : time in microseconds, <=798915
* @return	: void
---------------------------------------------------*/
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;		 
	SysTick->VAL=0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00; 
}

/** --------------------------------------------------
* @Function	: delay_xms
* @Brief	:  
* @param	: nms : time in milliseconds, <= 0xffffff*8*1000/SYSCLK
* @return	: void
---------------------------------------------------*/
void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD = (u32)nms*fac_ms;
	SysTick->VAL = 0x00; 
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp = SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;   	    
} 

/** --------------------------------------------------
* @Function	: delay_ms
* @Brief	: 
* @param	: nms : time in milliseconds
* @return	: void
---------------------------------------------------*/
void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;

	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)
		delay_xms(remain);
} 
