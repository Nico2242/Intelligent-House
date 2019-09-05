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


void Menu(char menu)
{
	/* initialize display, cursor on */
	lcd_init(LCD_DISP_ON);
	
	/* clear display and home cursor */
	lcd_clrscr();
	
	
	switch (menu)
	{
		case '1':
		lcd_puts("3=Windows");
		lcd_gotoxy(0,1);
		lcd_puts("4=Garage");
		lcd_gotoxy(10,0);
		lcd_puts("0=Back");
		currentMenu = '1';
		break;
		case '2':
		lcd_puts("1=Turn On");
		lcd_gotoxy(0,1);
		lcd_puts("2=Turn Off");
		currentMenu = '2';
		break;
		case '3':
		lcd_puts("3=Color");
		currentMenu = '3';
		break;
		case '4':
		lcd_puts("1=White");
		lcd_gotoxy(8,0);
		lcd_puts("2=Yellow");
		lcd_gotoxy(0,1);
		lcd_puts("3=Blue");
		lcd_gotoxy(10,1);
		lcd_puts("4=Pink");
		currentMenu = '4';
		break;
		default:
		lcd_puts("1=Light");
		lcd_gotoxy(0,1);
		lcd_puts("2=Temp");
		lcd_gotoxy(10,1);
		lcd_puts("9=Next");
		currentMenu = '0';
		break;
	}
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