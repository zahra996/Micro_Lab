/*
 * StepUSART.c
 *
 * Created: 11/26/2021 3:15:02 PM
 * Author : Tiba_Rayaneh
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"

char buffer[30];


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD = 0x00;
	PORTD = 0x00;
	
	uart_init(BAUD_CALC(9600));
	sei();
	
	stdout = &uart0_io;
	stdin = &uart0_io;
	
    while (1) 
    {
		scanf("%s",buffer);
		PORTB = buffer[0];
		_delay_ms(100);
		/*for (int i = 0; i < 5; i++) {
			PORTB = 0x01;
			_delay_ms(5);
			PORTB = 0x02;
			_delay_ms(5);
			PORTB = 0x04;
			_delay_ms(5);
			PORTB = 0x08;
			_delay_ms(5);
		}*/
    }
}