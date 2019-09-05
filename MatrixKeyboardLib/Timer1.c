#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect)
{
	ColumnScan();
}

void timer1Init()
{
		TCCR1B |= (1<<WGM12) | (1<<CS12);
		TIMSK1 |= (1<<OCIE1A);
		
		OCR1A = 3124;
}