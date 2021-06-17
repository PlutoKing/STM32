/****************************************************
@FileName		: I2C1.c
@Author			: Xu Zhe
@Version		: 1.0
@CreateDate		: 2020-09-08
@Description	: 
@History		: 
*****************************************************/

/* Head Files */
#include "I2C1.h" 

void I2C1_Init(void)
{
    /* 0. Definitions */
    GPIO_InitTypeDef GPIO_Config;                           // Define the GPIO Config Struct
    /* 1. Clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);    // GPIOB Clock
    /* 2. GPIO Config */
    GPIO_Config.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;         // Pin
    GPIO_Config.GPIO_Mode = GPIO_Mode_OUT;                  // Output
    GPIO_Config.GPIO_Speed = GPIO_Speed_100MHz;             // 50M
    GPIO_Config.GPIO_OType = GPIO_OType_PP;
    GPIO_Config.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB,&GPIO_Config);
    /* 3. Default config */
    I2C1_SCL = 1;
    I2C1_SDA = 1;
}

/** --------------------------------------------------
 * @Function: I2C1_Start
 * @Brief   : Generate the start signal
 * @param   : void
 * @return  : void
 ---------------------------------------------------*/
void I2C1_Start(void)
{
    SDA1_OUT(); 
    I2C1_SDA=1;I2C1_SCL=1;
    delay_us(4);
    I2C1_SDA=0;
    delay_us(4);
    I2C1_SCL=0;
}

/** --------------------------------------------------
 * @Function: I2C1_Stop
 * @Brief   : Generate the stop signal
 * @param   : void
 * @return  : void
 ---------------------------------------------------*/
void I2C1_Stop(void)
{
    SDA1_OUT(); 
    I2C1_SDA=0;I2C1_SCL=0;
    delay_us(4);
    I2C1_SDA=1;I2C1_SCL=1;
    delay_us(4);
}

/** --------------------------------------------------
 * @Function: I2C1_Wait_Ack
 * @Brief   : Wait for ack
 * @param   : void
 * @return  : 0 -- success
              1 -- fail
 ---------------------------------------------------*/
u8 I2C1_Wait_Ack(void)
{
    u8 ucErrTime=0;
    SDA1_IN();
    I2C1_SDA = 1;
	delay_us(1); 
    I2C1_SCL = 1;
	delay_us(1); 
    while(READ1_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            I2C1_Stop();
            return 1;
        }
    }
    I2C1_SCL = 0;
    return 0;
}

/** --------------------------------------------------
 * @Function: I2C1_Ack
 * @Brief   : Generate the ack signal
 * @param   : void
 * @return  : void
 ---------------------------------------------------*/
void I2C1_Ack(void)
{
    I2C1_SCL=0; SDA1_OUT();
    I2C1_SDA=0; delay_us(2);
    I2C1_SCL=1; delay_us(2);
    I2C1_SCL=0;
}

/** --------------------------------------------------
 * @Function: I2C1_NAck
 * @Brief   : Don't generate the ack signal or generate the nack signal
 * @param   : void
 * @return  : void
 ---------------------------------------------------*/
void I2C1_NAck(void)
{
    I2C1_SCL=0;
    SDA1_OUT();
    I2C1_SDA=1;delay_us(2);
    I2C1_SCL=1;delay_us(2);
    I2C1_SCL=0;
}

/** --------------------------------------------------
 * @Function: I2C1_Send_Byte
 * @Brief   : Send a byte via i2c
 * @param   : byte -- the byte to be send
 * @return  : void
 ---------------------------------------------------*/
void I2C1_Send_Byte(u8 byte)
{
    u8 t;
    SDA1_OUT();
    I2C1_SCL=0;
    for(t=0;t<8;t++)
    {
        I2C1_SDA=(byte&0x80)>>7;
        byte<<=1;
        delay_us(2);
        I2C1_SCL=1;delay_us(2);
        I2C1_SCL=0;delay_us(2);
    } 
}

/** --------------------------------------------------
 * @Function    : I2C1_Read_Byte
 * @Brief       : Read a byte via i2c
 * @param       : ack -- if generate the ack signal. If ack = 1, ack;if ack = 0, nack
 * @return  : the byte read form i2c
 ---------------------------------------------------*/
u8 I2C1_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA1_IN();
    for(i=0;i<8;i++ )
    {
        I2C1_SCL=0; delay_us(2);
        I2C1_SCL=1;
        receive<<=1;
        if(READ1_SDA)receive++;
        delay_us(1);
    } 
    if (!ack) I2C1_NAck();
    else I2C1_Ack();
    return receive;
}
