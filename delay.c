/*Delay generation of millisecond with for loop*/

#include<reg51.h>
 

void msdelay(int milli_sec)
{
unsigned char j ;
for(;milli_sec>0;milli_sec--)
	{
		for(j=255;j>0;j--);
		    for(j=232;j>0;j--);
	}
}
