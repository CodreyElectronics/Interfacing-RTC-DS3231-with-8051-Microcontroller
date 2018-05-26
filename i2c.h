/*Header for I2C routines*/

#include<reg51.h>

extern void Stop_I2C(void);
extern void Start_I2C(void);
extern void Slave_Write (unsigned char byte);
extern void Read_Ack(void);
extern void No_Acknowledgement(void);
 
extern unsigned char Read_From_RTC(unsigned char address);                    
extern void Write_To__RTC(unsigned char address, unsigned char val);      
extern void Initialize_RTC(void);                                                                                          
extern void ReadTime(void);    
extern void ReadDate(void);                 
extern void setTime(unsigned char sethour, unsigned char setmonth, unsigned char setsecond, short am_pm, short hour_twelve_twentyfour);
extern void setDate(unsigned char setday, unsigned char setdate, unsigned char setmonth, unsigned char setyear);    
extern unsigned char Read_I2C_Data(void); 