/*Header file for LCD 16*2 in 4 bit mode*/

#include<reg51.h>
#include<string.h>


typedef unsigned char u8;
typedef unsigned int u32;



extern void lcd_init(void);                                             //Function prototype to initialsie LCD
extern void lcd_command(unsigned char command);                         //Function to operate LCD in command mode
extern void lcd_data_write(unsigned char rs,unsigned char disp_data);   //Function to operate LCD in data_mode
extern void lcd_delay(unsigned int delay_ms);
extern void Disp_Data(unsigned char lineno, unsigned char cursor_position,unsigned char text[20]);

extern void Display_Date_LCD(void);

extern void Display_Time_LCD(void);

/*Assigning 8051 pins for LCD */

/*Pin Definitions for LCD*/

sbit RS=P0^0;                 //P0.0 connected to Register Select for LCD
sbit EN=P0^1;                 //P0.1 connected to Enable pin of LCD
sbit  RW=P0^2;                //P0.2 connected to RW of LCD pin

#define DATAPORT P2           //Data port for LCD

#define LCD_ENABLE      EN=1
#define LCD_DISABLE     EN=0
#define RS_HIGH         RS=1
#define RS_LOW          RS=0
#define RW_ENABLE       RW=1
#define RW_DISABLE      RW=0