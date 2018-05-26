/* This file explains the implementation of DS3231 RTC*/

#include<reg51.h>  
#include"header.h"

unsigned char RTCsec,RTChour,RTCmonth,RTCyear,RTCday,RTCdate,RTCmin;


unsigned char Convert_BCD_DECIMAL(unsigned char val)                
{                                                                                          
         return ((val & 0x0F) + (((val & 0xF0) >> 4) * 10)); 
}                                
                                                              

unsigned char Convert_DECIMAL_BCD(unsigned char val) 
{ 
         return (((val / 10) << 4) & 0xF0) | ((val % 10) & 0x0F); 
}                                                    
                                        
                  
unsigned char Read_From_RTC(unsigned char Address) 
{                                      
         unsigned char val= 0; 
         Start_I2C();                                                 	
         Slave_Write (DS3231_Write);  
         Read_Ack();  
         Slave_Write (Address);  
         Read_Ack(); 
         Start_I2C();                  
         Slave_Write (DS3231_Read);   
         Read_Ack(); 
         val=Read_I2C_Data();
         No_Acknowledgement( );  
         Stop_I2C();
         return val;  
}       



 unsigned char Read_I2C_Data(void)
 {
    unsigned char m,data_byte=0;

	for(m=0;m<8;m++)
	{
	SCL_DISABLE;
	SCL_ENABLE;
	
	if(SDA)
	data_byte|=0x80>>m;
	}
   return data_byte;  
 }               


void Write_To__RTC(unsigned char regaddress, unsigned char val)    
{  
         unsigned char loop_time;
         Start_I2C();                  
         Slave_Write(DS3231_Write); 
         Read_Ack();
         Slave_Write(regaddress); 
         Read_Ack();
         Slave_Write(val);
         Read_Ack();
         Stop_I2C(); 
	       for(loop_time=0;loop_time<255;loop_time++);
	           for(loop_time=0;loop_time<255;loop_time++);
	}  


void Initialize_RTC(void) 
{                                    
         Write_To__RTC(control_Register, 0x00);  
         Write_To__RTC(Status_Register, 0x08); 
}                        

void Readtime(void) 
{

  unsigned char temp = 0,hour_twelve_twentyfour,t;

         RTCsec = Read_From_RTC(second);
         RTCsec = Convert_BCD_DECIMAL(RTCsec);
         RTCmin = Read_From_RTC(minute);
         RTCmin = Convert_BCD_DECIMAL(RTCmin);
 
       
         hour_twelve_twentyfour=0;     //For 24 hour type
 
        switch(hour_twelve_twentyfour)
         {
                  case 1:
                  {
                           temp = Read_From_RTC(hour);
                           temp &= 0x20;
                           t= (short)(temp>> 5);
                           RTChour = (0x1F & Read_From_RTC(hour));
                           RTChour = Convert_BCD_DECIMAL(RTChour);
                           break;
                  }
                  default:
                  {
                	  RTChour = (0x3F & Read_From_RTC(hour));
                	  RTChour = Convert_BCD_DECIMAL(RTChour);
                           break;
                  }
         }
				 
			PC_Write ("Time= ");		 
      Convert_Int_To_String(RTChour,&stringvalue);	 
      PC_Write (stringvalue);
      PC_Write_SendByte('\0');			
     	PC_Write (":"); 
				 		 
		  Convert_Int_To_String(RTCmin,&stringvalue);
      PC_Write (stringvalue);	
			PC_Write (":"); 
				 
	     Convert_Int_To_String(RTCsec,&stringvalue);
	     PC_Write (stringvalue);	
	     PC_Write ("\r\n");
}                 
                                                      
                                
void ReadDate(void) 
{ 
        RTCyear = Read_From_RTC(year); 
        RTCyear  = Convert_BCD_DECIMAL(RTCyear );                  
        RTCmonth = (0x1F & Read_From_RTC(month)); 
        RTCmonth = Convert_BCD_DECIMAL(RTCmonth );                                
        RTCdate= (0x3F & Read_From_RTC(date)); 
        RTCdate= Convert_BCD_DECIMAL(RTCdate);    
        RTCday= (0x07 & Read_From_RTC(day));    
        RTCday= Convert_BCD_DECIMAL(RTCday);  

        PC_Write ("\t \t \t");	
        PC_Write ("Date= ");		 
        Convert_Int_To_String(RTCdate,&stringvalue);	 
        PC_Write (stringvalue);
        PC_Write_SendByte('\0');			
     	  PC_Write ("-"); 
				 		 
		    Convert_Int_To_String(RTCmonth,&stringvalue);
        PC_Write (stringvalue);	
			  PC_Write ("-"); 
				 
	      Convert_Int_To_String(RTCyear,&stringvalue);
	      PC_Write (stringvalue);	
         PC_Write ("\t \t \t");					
} 

                                                    
void setTime(unsigned char sethour, unsigned char setminute, unsigned char setsecond, short am_pm, short hour_twelve_twentyfour)  
{                                                                                                              
         unsigned char temp = 0; 
         Write_To__RTC(second, Convert_DECIMAL_BCD(setsecond)); 
         Write_To__RTC(minute, Convert_DECIMAL_BCD(setminute));        
         switch(hour_twelve_twentyfour) 
         { 
                  case 1: 
                  {        
                           switch(am_pm) 
                           { 
                                    case 1: 
                                    {            
                                             temp = 0x60; 
                                             break; 
                                    } 
                                    default: 
                                    {    
                                             temp = 0x40; 
                                             break; 
                                    } 
                           }                            
                           Write_To__RTC(hour, ((temp | (0x1F & (Convert_DECIMAL_BCD(sethour))))));                    
                           break; 
                  }                                              
                  
                  default: 
                  { 
                           Write_To__RTC(hour, (0x3F & (Convert_DECIMAL_BCD(sethour)))); 
                           break; 
                  }  
         }    
}                                                  

                                    
void setDate(unsigned char setday, unsigned char setdate, unsigned char setmonth, unsigned char setyear) 
{          
         Write_To__RTC(day, (Convert_DECIMAL_BCD(setday)));            
         Write_To__RTC(date, (Convert_DECIMAL_BCD(setdate)));  
         Write_To__RTC(month, (Convert_DECIMAL_BCD(setmonth))); 
         Write_To__RTC(year, (Convert_DECIMAL_BCD(setyear)));    
} 

                                
