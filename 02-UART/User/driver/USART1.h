#ifndef __USART1_H
#define __USART1_H

/* Head Files */
#include "sys.h"
#include "string.h"
#include "stm32f4xx_usart.h"

#define USART_REC_LEN		200

extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;

void usart1_init(u32 baudrate);
#endif
