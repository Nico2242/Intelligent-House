#include <avr/io.h>
#include <avr/interrupt.h>
#include "RGBLibrary.h"

void RGBTimer3Init()
{
	
	// Compare Output Mode: Fast PWM Mode: Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at BOTTOM (non-inverting mode) (Table 17-4)
	TCCR3A |= (1<<COM3B1);
	TCCR3A |= (1<<COM3A1);
	TCCR3A |= (1<<COM3C1);				// datasheet 17.11.1
	
	//Waveform Generation Mode: Mode 5 Fast PWM 8 bit: WGM30 = 1, WGM32 = 1 (Table 17-2)
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS31 = 1, CS30 = 1 (Table 17-6), frekv. = 980Hz
	TCCR3B |= (1<<CS31) | (1<<CS30);		// datasheet 17.11.6
}

void RGBTurnOn()
{
	// Set output to OC3A = PE3, OC3B = PE4, OC3C = PE5, Arduino MEGA pin configuration: (#5), (#2), (#3)
	DDRE |= (1<<PE3) | (1<<PE4) | (1<<PE5);
	RGBChangeColor(255,255,255);
}

void RGBTurnOff()
{
	// Set output to OC3A = PE3, OC3B = PE4, OC3C = PE5, Arduino MEGA pin configuration: (#5), (#2), (#3)
	DDRE &= ~(1<<PE3 | 1<<PE4 | 1<<PE5);
	printf("%d",DDRE);
}

void RGBChangeColor(int red, int green, int blue)
{
		OCR3A = red;		// Red, 100% fixed dutycycle, Output Compare Register 3 A, datasheet 17.11.20
		OCR3B = green;		// Green, 0% fixed dutycycle, Output Compare Register 3 B, datasheet 17.11.21
		OCR3C = blue;		// Blue, 50% fixed dutycycle, Output Compare Register 3 C, datasheet 17.11.22
}