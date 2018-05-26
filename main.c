/***********************************************************
Project:   DS3231 RTC interfacing with 8051 Microcontroller
Author:    Kumar B
Codrey Electronics
https://www.Codrey.com
Description: Sets and display the Date and Time on 16x2 LCD
*************************************************************/
#include<reg51.h>
#include"header.h"

/*Main code starts from here*/

void main()
{
    lcd_init();

    lcd_delay(2);

    Disp_Data(1,0, "DS3231 Interface");
    Disp_Data(2,0, "By Codrey.com");

    lcd_delay(10);

    Disp_Data(1,0, "                ");
    Disp_Data(2,0, "                ");

    Initialize_RTC();                       /*Initializing RTC DS3231*/



    lcd_delay(2);

    setTime(10,20,25,0,0);          /*Set Hour,Minute,Second */
    setDate(2,16,05,18);           /*Set Day,Date,Month,Year*/


    /*Infinite WHILE Loop for reading date and time of RTC*/


    Disp_Data(1,0, "DATE:");
    Disp_Data(2,0, "TIME:");

    ReadDate();                 //Gets the Day,month and year
    Display_Date_LCD();

    ReadTime();                /*Gets the time from DS3231*/
    Display_Time_LCD();


}