/*
 * keyLCD.c
 *
 * Created: 11/21/2021 2:00:59 PM
 * Author : Tiba_Rayaneh
 */

#define F_CPU 8000000UL

#define LCD_DDR  DDRC
#define LCD_PORT PORTC

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
#define LCD_D0 4
#define LCD_D1 5
#define LCD_D2 6
#define LCD_D3 7


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"


unsigned char str[17];
unsigned char key;

signed char flag = 0;

unsigned int username = 1234;
unsigned int password = 5678;

unsigned int usernameEnter = 0;
unsigned int passwordEnter = 0;

void keypad(void);
void update(char key);


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	
	DDRD = 0xF0;
	PORTD = 0x0F;
	
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
		}
		
		

		keypad();
    }
}

void update(char key) {
	if (flag == 0) {
		usernameEnter = usernameEnter * 10 + key;
	} else {
		passwordEnter = passwordEnter * 10 + key;
	}
}

void keypad(void) {
	PORTD = 0xE0;
	if (PIND == 0xEE) {
		while(PIND == 0xEE);
		//key = '1';
		update(1);
	}
	if (PIND == 0xED) {
		while(PIND == 0xED);
		//key = '2';
		update(2);
	}
	if (PIND == 0xEB) {
		while(PIND == 0xEB);
		//key = '3';
		update(3);
	}

	PORTD = 0xD0;
	if (PIND == 0xDE) {
		while(PIND == 0xDE);
		//key = '4';
		update(4);
	}
	if (PIND == 0xDD) {
		while(PIND == 0xDD);
		//key = '5';
		update(5);
	}
	if (PIND == 0xDB) {
		while(PIND == 0xDB);
		//key = '6';
		update(6);
	}

	PORTD = 0xB0;
	if (PIND == 0xBE) {
		while(PIND == 0xBE);
		//key = '7';
		update(7);
	}
	if (PIND == 0xBD) {
		while(PIND == 0xBD);
		//key = '8';
		update(8);
	}
	if (PIND == 0xBB) {
		while(PIND == 0xBB);
		//key = '9';
		update(9);
	}

	PORTD = 0x70;
	if (PIND == 0x7E) {
		while(PIND == 0x7E);
		//key = '*';
		if (flag == 1 && username == usernameEnter && password == passwordEnter) {
			flag = 10;
			PORTB = 0b00000010;
		} else if (flag == 1 && (username != usernameEnter || password != passwordEnter)) {
			flag = -1;
			PORTB = 0b00000001;
		} else {
			flag++;
		}
		lcd_clear();
	}
	if (PIND == 0x7D) {
		while(PIND == 0x7D);
		//key = '0';
		update(0);
	}
	if (PIND == 0x7B) {
		while(PIND == 0x7B);
		//key = '#';
		flag = 0;
		usernameEnter = 0;
		passwordEnter = 0;
		PORTB = 0x00;
		lcd_clear();
	}
}

