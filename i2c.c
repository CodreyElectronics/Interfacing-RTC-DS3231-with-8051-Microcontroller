/*This file establishes i2c communication with 8051 Microcontroller using Bit banging*/

#include<reg51.h>
#include"header.h"

/*Function for I2C Start condition for Slave DS3231*/
/*This function alerts the RTC*/

void Start_I2C(void)
{
    SCL_DISABLE;
    SDA_ENABLE;
    SCL_ENABLE;
    SDA_DISABLE;
}

/*Function for I2C Stop condition*/

void Stop_I2C(void)
{
    SCL_DISABLE;
    SDA_DISABLE;
    SCL_ENABLE;
    SDA_ENABLE;
}


/*Function for Writing Address to Slave*/

void Slave_Write(unsigned char byte)
{
    unsigned char j,k;
    k = byte;
    for (j= 0; j < 8; j++)
    {
        SCL_DISABLE;
        SDA=(k&(0x80>>j))?1:0;    /*Writing bit_by_bit*/
        SCL_ENABLE;
    }
}

// Function to generate No Acknowledgement signal to slave

void No_Acknowledgement(void)
{
    SCL_DISABLE;
    SDA_ENABLE;
    SCL_ENABLE;
}

/*Function for reading the Acknowledgement from Slave*/

void Read_Ack(void)
{
    SCL_DISABLE;
    SDA_ENABLE;
    SCL_ENABLE;
    while(SDA);
}