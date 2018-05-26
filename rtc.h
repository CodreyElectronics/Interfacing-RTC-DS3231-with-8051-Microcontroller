/*Header file for reading and writing DS3231 registers*/
#include<reg51.h>

/*Memory addresses and registers to access DS3231*/

#define RTC_Address                0x68             //Slave address of ds3231                                         

#define DS3231_Read                ((RTC_Address << 1) | 0x01)      //Read address for RTC            
#define DS3231_Write               ((RTC_Address << 1) & 0xFE)      //Write address for RTC               


#define date                        0x04
#define month                       0x05
#define year                        0x06
#define second                      0x00
#define minute                      0x01
#define hour                        0x02
#define control_Register            0x0E
#define day                         0x03
#define Status_Register             0x0F
#define _24_hour_format             0
#define _12_hour_format             1
#define am                          0
#define pm                          1