/*External header file for accessing global variables*/

#include<reg51.h>

extern void Show_Integer_Ascii( unsigned char lineno, unsigned char cursor_position, unsigned long value);

extern unsigned char Convert_BCD_DECIMAL(unsigned char val);                       
extern unsigned char Convert_DECIMAL_BCD(unsigned char val);    
extern unsigned char RTCsec,RTChour,RTCmonth,RTCyear,RTCday,RTCdate,RTCmin;



