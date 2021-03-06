
#ifndef F_CPU
#define F_CPU 8000000UL 
#endif

#define D4 eS_PORTC4
#define D5 eS_PORTC5
#define D6 eS_PORTC6
#define D7 eS_PORTC7
#define RS eS_PORTC0
#define EN eS_PORTC2 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"


void adc_init(void){
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0));   // 8Mhz/64 = 125Khz the ADC reference clock
	ADMUX |= (1<<REFS0); // Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN); // Turn on ADC
	ADCSRA |= (1<<ADSC); 
}

uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0; // Clear the older channel that was read
	ADMUX |= channel; // Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC); // Starts a new conversion
	while(ADCSRA & (1<<ADSC)); // Wait until the conversion is done
	return ADCW; // Returns the ADC value of the chosen channel
}

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRA = 0x00;
	PORTA = 0x00;
	
	adc_init(); //Setup the ADC
	
	char str[17];
	uint16_t adc_value;
	Lcd4_Init();
	
    while (1) 
    {
		//v = read_adc(0) * 255 / 5;
		adc_value = (read_adc(0) / 2.054);
		
		sprintf(str,"Temp: %d \xDF\x43", adc_value);
		
		Lcd4_Set_Cursor(0,1);
		Lcd4_Write_String(str);
		_delay_ms(100);
		Lcd4_Clear();
    }
}

