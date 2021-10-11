/*
 * send.c
 *
 * Author : New Tech
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"
#include <util/delay.h>
#include "usart.h"

int i = 0;

int main(void)
{
    /* Replace with your application code */
	uart_init(BAUD_CALC(115200));
	sei();
	_delay_ms(1000);
	uart_puts("faradars\r\n");
	_delay_ms(1000);
	
    while (1) 
    {
		uart_putint(i);
		uart_puts("\r\n");
		_delay_ms(1000);
		i++;
    }
}

