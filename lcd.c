#include<reg51.h>
#include<string.h>                        //Header file for using the memset function
#include"header.h"

void Readtime(void);

unsigned char Comm1[] = { 0x80, 0xC0 };

void lcd_init(void)             //Initialising the LCD for displaying the data
{
    lcd_command(0x01);              //8 bit_mode with 2 lines
    lcd_command(0x06);              // Display on cursor OFF
    lcd_command(0x0C);              //clear the screen
    lcd_command(0x3C);      	       //move cursor automatically right
}


void lcd_command(unsigned char command)  //Function to send command instruction to LCD
{
    DATAPORT = command;
    RS_LOW;
    RW_DISABLE;
    LCD_ENABLE;
    lcd_delay(1);
    LCD_DISABLE;
}

void lcd_data_write(unsigned char rs,unsigned char disp_data)  //Function to write to LCD display
{
    DATAPORT = disp_data;
    lcd_delay(1);
    if(rs)
        RS_HIGH;

    else
        RS_LOW;
    lcd_delay(1);
    RW_DISABLE;
    lcd_delay(1);
    LCD_ENABLE;
    lcd_delay(1);
    LCD_DISABLE;
}

void Disp_Data(unsigned char lineno, unsigned char cursor_position, unsigned char text[20])
{
    unsigned char i;

    lcd_data_write(0,(Comm1[lineno - 1] + cursor_position ));

    for (i=0; text[i]!='\0'; i++)

        lcd_data_write(1, text[i]);

}

void lcd_delay(unsigned int delay_ms)   //Function for generating delay in milli seconds
{
    u32 m,n ;
    for(m=0; m<delay_ms; m++)
        for(n=0; n<1275; n++);
}


/***************Function to convert Ascii value to integer in a particular line and Postion**************/

void Show_Integer_Ascii(unsigned char lineno, unsigned char cursor_position, unsigned long value)
{
    unsigned char a[11], b[11], i, m, n;

    if (value == 0 && cursor_position == 4) {
        goto loop1;
    } else if (value == 0) {
        b[0] = '0';
        b[1] = '\0';
        goto loop;
    }


loop1:
    for (i = 0; i < 11; i++)
    {
        a[i] = (value % 10) + 0x30;
        value = value / 10;
        if (value == 0)
            break;
    }
    a[i + 1] = '\0';
    n= 0;
    for (m = i; m >= 0; m--) {
        b[n] = a[m];
        n++;
        if (m == 0)
            break;
    }
    b[n] = '\0';

loop:
    if (lineno == 1)
        Disp_Data(lineno, cursor_position, b);

    if (lineno == 2)
        Disp_Data(lineno, cursor_position, b);

    memset(b,0,sizeof(b));

}


/****************Function to display RTC Date on LCD*********************/

void Display_Date_LCD(void)
{
    ReadDate();

    Disp_Data(1, 7, "/");

    if(RTCdate>=0  && RTCdate <=9)
    {
        Disp_Data(1, 5, "0");
        Show_Integer_Ascii(1,6,RTCdate);
    }

    else
    {
        Show_Integer_Ascii(1,5,RTCdate);
    }

    Disp_Data(1, 10, "/");

    if(RTCmonth>=0  && RTCmonth <=9)
    {
        Disp_Data(1, 8, "0");
        Show_Integer_Ascii(1,9,RTCmonth);
    }

    else
    {
        Show_Integer_Ascii(1,8,RTCmonth);
    }

    if(RTCyear>=0  && RTCyear <=9)
    {
        Disp_Data(1, 11, "0");
        Show_Integer_Ascii(1,12,RTCyear);
    }

    else
    {
        Show_Integer_Ascii(1,11,RTCyear);
    }
}

/*******Function to display RTC Time on LCD************************/


void Display_Time_LCD(void)
{

    do {
        Readtime();

        if(RTChour>=0  && RTChour <=9)
        {
            Disp_Data(2, 5, "0");
            lcd_delay(2);
            Show_Integer_Ascii(2,6,RTChour);
        }

        else
        {
            Show_Integer_Ascii(2,5,RTChour);
        }

        Show_Integer_Ascii(2,5,RTChour);

        Disp_Data(2, 7, ":");

        Show_Integer_Ascii(2,8,RTCmin);
        Disp_Data(2, 10, ":");

        Show_Integer_Ascii(2,11,RTCsec);
        Disp_Data(2, 7, ":");



        Disp_Data(2, 10, ":");

        if(RTCmin>=0  && RTCmin <=9)
        {
            Disp_Data(2, 8, "0");
            Show_Integer_Ascii(2,9,RTCmin);
        }

        else
        {
            Show_Integer_Ascii(2,8,RTCmin);
        }

        if(RTCsec>=0  && RTCsec <=9)
        {
            Disp_Data(2, 11, "0");
            Show_Integer_Ascii(2,12,RTCsec);
        }

        else
        {
            Show_Integer_Ascii(2,11,RTCsec);
        }
    } while(1) ;
}