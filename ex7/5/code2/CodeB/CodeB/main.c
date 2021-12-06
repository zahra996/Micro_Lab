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

char buffer[17];
int temp;

void ADC_Init(){
	DDRA = 0x00;	        /* Make ADC port as input */
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)
{
	ADMUX = 0x40 | (channel & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD = 0x00;
	PORTD = 0x00;
	
	
	ADC_Init();
	 
	uart_init(BAUD_CALC(9600));
	sei();
	
	
    while (1) 
    {
		temp = ADC_Read(0) * 0.48;
		sprintf(buffer," %d", temp);
		uart_puts(buffer);
		_delay_ms(1000);
    }
}