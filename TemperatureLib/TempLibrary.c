#include <avr/io.h>
#include <avr/interrupt.h>

void Temp_Timer4_init()
{
	TCCR0B |= (1<<WGM02);						// Mode 4, CTC = WGM40 - WGM43 = 0100, Table 17-2 (page 145)
	TIMSK0 |= (1<<OCIE0B);						// Timer/Counter4, Output Compare B Match Interrupt Enable, 17.11.35 (page 161)
	OCR0A = 62499;								// OCR0A = (Tdelay * F_CPU / (N * 1000)) - 1 => 174 gives 700 µSek
	TCCR0B |= (1<<CS02);
	
}

void Temp_ADC_start()
{
	Temp_Timer4_init();
	
	ADMUX = (1 << REFS0);	// 5V supply used for ADC reference, select ADC channel 0, datasheet 26.8.1
	DIDR0 = (1 << ADC0D);	// disable digital input on ADC0 pin, datasheet 26.8.6
	// enable ADC, start ADC, Enable Interrupt, ADC clock = 16MHz / 128 = 125kHz, datasheet 28.9.2
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADCSRB = (1<<ADTS1) | (1<<ADTS0);	// ADC Auto Trigger Source, ADTS = 011, Table 26-6 (Page 287)
}

void Temp_ADC_stop()
{
	Temp_Timer4_init();
	
	ADCSRA &= ~(1<<ADEN | 1<<ADSC);
}
