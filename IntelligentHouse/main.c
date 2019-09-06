/**

Menu
=========

Keypad standard function all time:

0=Back - 9=Next - #=MainMenu

Code | Name
:--: | ----
0	 | Main Menu Part 1
1	 | Main Menu Part 2
2	 | Light Control Menu Part 1
3	 | Light Control Menu Part 2
4	 | Light Color Menu
5	 | Temperature Control Menu
6	 | Windows Control Menu


Menu					  | Functions
:----:					  | ---------
Main Menu Part 1		  | 1. Light <br> 2. Temperature
Main Menu Part 2		  | 1. Windows <br> 2. Garage
Light Control Menu Part 1 | 1. Turn On <br> 2. Turn off
Light Control Menu Part 2 | 1. Color
Light Color Menu		  | 1. White <br> 2. Yellow <br> 2. Blue <br> 2. Pink
Temperature Control Menu  | 1. Adjust
Windows Control Menu 	  | 1. Open Half <br> 2. Open Full
*/

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "MKBLibrary.h"
#include <avr/interrupt.h>
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