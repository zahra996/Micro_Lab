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

#define Keypad_PORT PORTB
#define Keypad_PIN PINB



#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"

char buffer[30];


unsigned char str[17];
unsigned char key = 0;
unsigned char stp = 4;

signed char flag = 0;

unsigned int username = 12;
unsigned int password = 12;

unsigned int usernameEnter = 0;
unsigned int passwordEnter = 0;

void keypad(void);
void update(char key);


int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRB = 0xF0;
	PORTB = 0x0F;
	
	DDRC = 0xFF;
	PORTC = 0x00;
	
	uart_init(BAUD_CALC(9600));
	sei();
	
	stdout = &uart0_io;
	stdin = &uart0_io;
	
	lcd_init();
	lcd_on();
    while (1) 
    {
		if (flag == 0) {
			lcd_set_cursor(0,0);
			lcd_printf("Username: %d", usernameEnter);
		} else if (flag == 1) {
			lcd_set_cursor(0,0);
			lcd_printf("Password: %d", passwordEnter);
		} else if (flag == -1) {
			lcd_set_cursor(0,0);
			lcd_puts("Erorr");
		} else if (flag == 10) {
			lcd_set_cursor(0,0);
			lcd_puts("Welcome");
			lcd_set_cursor(0,1);
			lcd_printf("Step: %d", stp);
			sprintf(buffer, "%d", stp);
			uart_puts(buffer);
			/*if (key != 100) {
				stp = key;
				key = 100;
				lcd_clear();
				//sprintf(buffer, "%d", stp);
				//uart_puts(buffer);
			}*/
			
		}
		
		

		keypad();
    }
}

void update(char key) {
	if (flag == 0) {
		usernameEnter = usernameEnter * 10 + key;
	} else if (flag == 1) {
		passwordEnter = passwordEnter * 10 + key;
	}
}

void keypad(void) {
	Keypad_PORT = 0xE0;
	if (Keypad_PIN == 0xEE) {
		while(Keypad_PIN == 0xEE);
		key = 1;
		update(1);
	}
	if (Keypad_PIN == 0xED) {
		while(Keypad_PIN == 0xED);
		key = 2;
		update(2);
	}
	if (Keypad_PIN == 0xEB) {
		while(Keypad_PIN == 0xEB);
		key = 3;
		update(3);
	}

	Keypad_PORT = 0xD0;
	if (Keypad_PIN == 0xDE) {
		while(Keypad_PIN == 0xDE);
		key = 4;
		update(4);
	}
	if (Keypad_PIN == 0xDD) {
		while(Keypad_PIN == 0xDD);
		key = 5;
		update(5);
	}
	if (Keypad_PIN == 0xDB) {
		while(Keypad_PIN == 0xDB);
		key = 6;
		update(6);
	}

	Keypad_PORT = 0xB0;
	if (Keypad_PIN == 0xBE) {
		while(Keypad_PIN == 0xBE);
		key = 7;
		update(7);
	}
	if (Keypad_PIN == 0xBD) {
		while(Keypad_PIN == 0xBD);
		key = 8;
		update(8);
	}
	if (Keypad_PIN == 0xBB) {
		while(Keypad_PIN == 0xBB);
		key = 9;
		update(9);
	}

	Keypad_PORT = 0x70;
	if (Keypad_PIN == 0x7E) {
		while(Keypad_PIN == 0x7E);
		//key = '*';
		if (flag == 1 && username == usernameEnter && password == passwordEnter) {
			flag = 10;
			key = 0;
			PORTC = 0b00000010;
		} else if (flag == 1 && (username != usernameEnter || password != passwordEnter)) {
			flag = -1;
			PORTC = 0b00000001;
		} else if (flag == 0){
			flag++;
		}
		lcd_clear();
	}
	if (Keypad_PIN == 0x7D) {
		while(Keypad_PIN == 0x7D);
		key = 0;
		update(0);
	}
	if (Keypad_PIN == 0x7B) {
		while(Keypad_PIN == 0x7B);
		//key = '#';
		flag = 0;
		usernameEnter = 0;
		passwordEnter = 0;
		PORTC = 0x00;
		lcd_clear();
	}
}
