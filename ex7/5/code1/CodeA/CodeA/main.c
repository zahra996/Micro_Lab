/*
 * CodeA.c
 *
 * Created: 11/26/2021 5:00:07 PM
 * Author : Tiba_Rayaneh
 */ 

#define F_CPU 8000000UL

#define LCD_DDR  DDRA
#define LCD_PORT PORTA

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
#define LCD_D0 4
#define LCD_D1 5
#define LCD_D2 6
#define LCD_D3 7




#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"

char buffer[17];


unsigned char str[17];



int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	PORTA = 0x00;
	
	uart_init(BAUD_CALC(9600));
	sei();
	
	stdout = &uart0_io;
	stdin = &uart0_io;
	
	lcd_init();
	lcd_on();
	
    while (1) 
    {
		
		//sprintf(buffer,"sdf %d", 5);
		lcd_set_cursor(0,0);
		lcd_puts("Temp: ");
		_delay_ms(1000);
		scanf("%s",buffer);
		lcd_puts(buffer);
		
		//lcd_clear();
		
		
    }
}
