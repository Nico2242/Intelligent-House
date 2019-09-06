#include <avr/io.h>
#include "lcd.h"
#include "MKBLibrary.h"

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
