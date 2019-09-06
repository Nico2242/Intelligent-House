/**
 Intelligent House
 =================
 
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MKBLibrary.h"
#include "lcd.h"
#include "RGBLibrary.h"
#include "Menu.h"

ISR(ADC_vect)
{
	unsigned int ADC_data = ADC;							// get the ADC value, datasheet 28.9.3
	float ADC_voltage = 5.0 * ADC_data / 1024.0;			// calculate the ADC voltage
	float temp = log(10000.0 * (1024.0 / ADC_data - 1));
	float tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp);
	float tempC = tempK - 273.15;
	
	char buffer[7];
	
	/* convert float into string */
	dtostrf(tempC,4,2,buffer);
	
	lcd_gotoxy(0,1);
	lcd_puts("Temp: ");
	lcd_puts(buffer);
	lcd_puts("C");
	
}

int main(void)
{
	UartInit();

	Init();
	
	timer1Init();
	
	Menu('0');
	
	RGBTimer3Init();
	
	sei();
	
	while(1) {
		int keypressed = ReadRows();
		DecodeKeyBoard(keypressed);
	}
}