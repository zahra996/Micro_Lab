/*
 * part1.c
 *
 * Created: 26/07/1400 12:49:12 ب.ظ
 * Author : New Tech
 */ 
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	  DDRB =0xFF;
    /* Replace with your application code */
    while (1) 
    {
		
			PORTB =0xFF;
			_delay_ms(500);
			PORTB =0x00;
			_delay_ms(500);
	
    }
}

