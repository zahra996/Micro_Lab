/*
 * HelloWorld.c
 *
 * Created: 17/08/1400 09:31:56 ب.ظ
 * Author : New Tech
 */ 

#include <avr/io.h>
#include "library/global.h"
#include <util/delay.h>
#include <inttypes.h>

#define LCD_DATA  PORTB
#define ctrl	  PORTD

void LCD_cmd(uint8_t cmd);
void init_LCD(void);
void LCD_write(uint8_t data);

int main(void)
{
    uint8_t text[]="Hello World!";
	DDRB=0xFF;
	DDRD=0x07;
	
	init_LCD();
	LCD_cmd(0x0F);
	
	for (uint8_t i=0; i<13; i++)
	{
		LCD_write(text[i]);
	}
	
	return 0;
   
}
	
void init_LCD(void)
{
	LCD_cmd(0x38);
	_delay_ms(1);
	LCD_cmd(0x01);
	_delay_ms(1);
	LCD_cmd(0x0E);
	_delay_ms(1);
	LCD_cmd(0x80);
	_delay_ms(1);
}

void LCD_cmd(uint8_t cmd)
{
	LCD_DATA=cmd;
	ctrl=0x04;
	_delay_ms(1);
	ctrl=0x00;
	_delay_ms(50);
}

void LCD_write(uint8_t data)
{
	LCD_DATA=data;
	ctrl=0x05;
	_delay_ms(1);
	ctrl=0x01;
	_delay_ms(50);
}


