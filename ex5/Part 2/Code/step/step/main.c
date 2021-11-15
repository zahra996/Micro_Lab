
#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz clock speed
#endif 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char flag = 0;
char flag2 = 0;
char d = 0;

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer, interrupt and variable
void timer0_init()
{
	// set up timer with prescaler = 256
	TCCR0 |= (1 << CS02);
	
	// initialize counter
	TCNT0 = 0;
	
	// enable overflow interrupt
	TIMSK |= (1 << TOIE0);
	
	// enable global interrupts
	sei();
	
	// initialize overflow counter variable
	tot_overflow = 0;
}


ISR(TIMER0_OVF_vect)
{
	tot_overflow++;
}

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;
	DDRC = 0x00;
	PORTC = 0xFF;
	
	DDRD |= (1 << 0);
	
	// initialize timer
	timer0_init();
	
    /* Replace with your application code */
    while (1) 
    {
		d = PINC & 0b00000100;
		if (d == 0) {
			flag++;
		}
		
	
		if (tot_overflow >= 50) 
		{
			
			if (TCNT0 >= 53)
			{
				
				flag2++;
				if (flag2 > 4) flag2 = 1;
				TCNT0 = 0;            // reset counter
				tot_overflow = 0;     // reset overflow counter
			}
		}
		if (flag%2 == 0) {
			if (flag2 == 1) {
				PORTA = 0x01;
				} else if (flag2 == 2) {
				PORTA = 0x02;
				} else if (flag2 == 3) {
				PORTA = 0x04;
				} else if (flag2 == 4) {
				PORTA= 0x08;
			}
		} else {
			if (flag2 == 1) {
				PORTA = 0x08;
				} else if (flag2 == 2) {
				PORTA = 0x04;
				} else if (flag2 == 3) {
				PORTA = 0x02;
				} else if (flag2 == 4) {
				PORTA= 0x01;
			}
		}
		
    }
}

