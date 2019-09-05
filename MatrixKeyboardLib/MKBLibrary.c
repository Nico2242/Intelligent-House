/**

Port mapping
=============

Coloumn  | Port | Arduino Pin | Keypad Pin
-------	 | ---- | ----------- | ----------
C1		 | PC0	| #37		  | #4
C2		 | PC1	| #36		  | #3
C3		 | PC2	| #35		  | #2
C4		 | PC3	| #34		  | #1

Row		 | Port | Arduino Pin | Keypad Pin
-------	 | ---- | ----------- | ----------
R1		 | PC4	| #33		  | #8
R2		 | PC5	| #32		  | #7
R3		 | PC6	| #31		  | #6
R4		 | PC7	| #30		  | #5



Decoding
=========

R4 | R3 | R2 | R1 | C4 | C3 | C2 | C1 | Key
-- | -- | -- | -- | -- | -- | -- | -- | ---
1  | 1  | 1  | 0  | 1  | 1  | 1  | 0  | "1"
1  | 1  | 0  | 1  | 1  | 1  | 1  | 0  | "4"
1  | 0  | 1  | 1  | 1  | 1  | 1  | 0  | "7"
0  | 1  | 1  | 1  | 1  | 1  | 1  | 0  | "*"
1  | 1  | 1  | 0  | 1  | 1  | 0  | 1  | "2"
1  | 1  | 0  | 1  | 1  | 1  | 0  | 1  | "5"
1  | 0  | 1  | 1  | 1  | 1  | 0  | 1  | "8"
0  | 1  | 1  | 1  | 1  | 1  | 0  | 1  | "0"
1  | 1  | 1  | 0  | 1  | 0  | 1  | 1  | "3"
1  | 1  | 0  | 1  | 1  | 0  | 1  | 1  | "6"
1  | 0  | 1  | 1  | 1  | 0  | 1  | 1  | "9"
0  | 1  | 1  | 1  | 1  | 0  | 1  | 1  | "#"
1  | 1  | 1  | 0  | 0  | 1  | 1  | 1  | "A"
1  | 1  | 0  | 1  | 0  | 1  | 1  | 1  | "B"
1  | 0  | 1  | 1  | 0  | 1  | 1  | 1  | "C"
0  | 1  | 1  | 1  | 0  | 1  | 1  | 1  | "D"

*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "MKBLibrary.h"
#include "RGBLibrary.h"

char currentMenu = '0';

/// Col1 - Col4 goes low one after each other.
/** The columnCounter counts 1, 2, 3 and 4 and stores values static between each call. */
void ColumnScan()
{
	static int counter = 1;
	PORTC = 0b11111111;
	
	switch (counter)
	{
		case 1:
		PORTC = 0b11111110;
		//_delay_ms(100);
		counter++;
		break;
		case 2:
		PORTC = 0b11111101;
		//_delay_ms(100);
		counter++;
		break;
		case 3:
		PORTC = 0b11111011;
		//_delay_ms(100);
		counter++;
		break;
		case 4:
		PORTC = 0b11110111;
		//_delay_ms(100);
		counter++;
		break;
		default:
		counter = 1;
		break;
	}
}

/// Read rows to check if one goes low(0) when clicked.
/** If a key is pressed the corresponding row of the current column scanned, goes low and the key pressed is returned. */
int ReadRows()
{
	int keypressed;
	unsigned char pinC = PINC;
	//printf("%d", pinL);
	if (~pinC & 0xF0) // check if clicked on keypad
	{
		_delay_ms(100);
		keypressed = pinC;
	}
	
	return keypressed;
}

/// Decode which key is pressed and do the right menu function.
void DecodeKeyBoard(int keypressed)
{
	char charKeyPressed;
	switch (keypressed)
	{
		case 0b11101110:
			printf("1");
			if (currentMenu == '0')
			{
				Menu('2');
			}
			if (currentMenu == '4')
			{
				RGBChangeColor(255,255,255);
			}
			if (currentMenu == '2')
			{
				RGBTurnOn();
			}
		break;
		case 0b11011110:
			printf("4"); 
			if (currentMenu == '4')
			{
				RGBChangeColor(255,0,150);
			}
		break;
		case 0b10111110:
			printf("7");
		break;
		case 0b01111110:
			printf("*"); 
		break;
		case 0b11101101:
			printf("2");
			if (currentMenu == '2')
			{
				RGBTurnOff();
			}
			if (currentMenu == '4')
			{
				RGBChangeColor(255,100,0);
			}
		break;
		case 0b11011101:
			printf("5"); 
		break;
		case 0b10111101:
			printf("8"); 
		break;
		case 0b01111101:
			printf("0");
			if (currentMenu == '1')
			{
				Menu('0');
			}
			if (currentMenu == '2')
			{
				Menu('0');
			}
			if (currentMenu == '3')
			{
				Menu('2');
			}
			if (currentMenu == '4')
			{
				Menu('3');
			}
		break;
		case 0b11101011:
			printf("3"); 
			if (currentMenu == '3')
			{
				Menu('4');
			}
			if (currentMenu == '4')
			{
				RGBChangeColor(0,0,255);
			}
		break;
		case 0b10111011:
			printf("9");
			if (currentMenu == '0')
			{
				Menu('1');
			}
			if (currentMenu == '2')
			{
				Menu('3');
			}
		break;
		case 0b11011011:
			printf("6");
		break;
		case 0b01111011:
			printf("#");
			Menu('0'); 
		break;
		case 0b11100111:
			printf("A"); 
		break;
		case 0b11010111:
			printf("B"); 
		break;
		case 0b10110111:
			printf("C"); 
		break;
		case 0b01110111:
			printf("D"); 
		break;
		default:
		
		break;
	}
}

/// Initialize ports.
/** Set output ports and enable pull-ups */
void Init(void)
{
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3); // Set output ports
	PORTC = (1<<PC4) | (1<<PC5) | (1<<PC6) | (1<<PC7); // Enable Pull-up
}

