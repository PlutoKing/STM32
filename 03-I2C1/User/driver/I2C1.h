#ifndef __I2C1_H
#define __I2C1_H

/* Head Files */
#include "sys.h"
#include "delay.h"

/* Macro Definition */
#define SDA1_IN() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}
#define SDA1_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} 

#define I2C1_SCL PBout(8)		// SCL
#define I2C1_SDA PBout(9)		// SDA	
#define READ1_SDA PBin(9)		// Input

/* Function Declaration */
void I2C1_Init(void);
void I2C1_Start(void);
void I2C1_Stop(void);
u8 I2C1_Wait_Ack(void);
void I2C1_Ack(void);
void I2C1_NAck(void);
void I2C1_Send_Byte(u8 byte);
u8 I2C1_Read_Byte(unsigned char ack);

#endif
