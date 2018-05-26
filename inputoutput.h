/*Header file for Input Ouput Configuration of DS3231 RTC with 8051 Microcontroller*/

#include<reg51.h>
 

#define SDA_OUT          P1=0x00                  //Configuring Port 1 as Output
#define SDA_IN           P1=0XFF                  //Configuring Port 1 as Input

sbit SCL=P1^4;                                   //SCL connected to Port 1.4 of 8051
sbit SDA=P1^5;                                   //SDA connected to port 1.5 of 8051


#define SCL_ENABLE       SCL=1                   /*Make the SCL HIGH*/
#define SCL_DISABLE      SCL=0                   /*Make the SCL LOW*/
#define SDA_ENABLE       SDA=1                   /*Make the SDA HIGH*/
#define SDA_DISABLE      SDA=0                   /*Make the SDA LOW*/