/*
 * recive.c
 *
 * Author : New Tech
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"
#include <util/delay.h>
#include "usart.h"

#include "lcd.h"
#include "rprintf.h"

char buffer[200];

int main(void)
{
    /* Replace with your application code */
	uart_init(BAUD_CALC(115200));
	sei();
	 
	stdout = &uart0_io;
	stdin = &uart0_io;
	
	lcdInit();
	rprintfInit(lcdDataWrite);
	
	lcdClear();
	lcdGotoXY(0,0);
	rprintf("ready");
	_delay_ms(200);
	
    while (1) 
    {
		scanf("%s",buffer);
		lcdClear();
		lcdGotoXY(0,0);
		rprintfStr(buffer);
		_delay_ms(200);
    }
}

