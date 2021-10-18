/*
 * part3.c
 *
 * Created: 26/07/1400 10:21:26 ق.ظ
 * Author : New Tech
 */ 

#include <avr/io.h>
#include "global.h"
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRC = 0xFF;
	PORTC = 0;
	
    while (1) 
    {
		for (uint8_t index = 0 ;index < 8; index++)
		{
			PORTC = (1 << index);
			_delay_ms(500);
			if (index == 7)
			{
				for (uint8_t index = 7; index > 0; index--)
				{
					PORTC = (1 << index);
					_delay_ms(500);
				}
			}
		}
		
    }
}

