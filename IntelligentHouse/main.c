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