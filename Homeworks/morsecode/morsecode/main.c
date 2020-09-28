/*
***********************************************************************
 * 
 * Blink a LED and use the function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/




/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define SHORT_DELAY 500      // Delay in miliseconds
#define LONG_DELAY 1500		// 3 times short delay for dash
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include <stdio.h>

/* Variables ---------------------------------------------------------*/



/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 * Toggle one LED and use the function from the delay library.
 */
int main(void)
{
	int	a ;   // local variable for more than one dot/dash 
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);  //   << bite shift for PB5   | means or

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);   // logicky sucin &   ~negace

    // Infinite loop
    while (1)
    {																
        // Pause several miliseconds
        _delay_ms(SHORT_DELAY);	
															// D  -..
        // Invert LED in Data Register
        // PORTB = PORTB xor 0010 0000
        PORTB = PORTB ^ (1<<LED_GREEN);						// -
		_delay_ms(LONG_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
			
		for(a=0;a<2;a++)									// ..
			{	
				PORTB = PORTB ^ (1<<LED_GREEN);
				_delay_ms(SHORT_DELAY);
				PORTB = PORTB & ~(1<<LED_GREEN);
				_delay_ms(SHORT_DELAY);
			}
		
		_delay_ms(LONG_DELAY);
		
	
															// E  .
		
		PORTB = PORTB ^ (1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);
		_delay_ms(LONG_DELAY);
		
		
															// 2  ..---
		for(a=0;a<2;a++)
			{
					PORTB = PORTB ^ (1<<LED_GREEN);			// ..
					_delay_ms(SHORT_DELAY);
					PORTB = PORTB & ~(1<<LED_GREEN);
					_delay_ms(SHORT_DELAY);
					
			}
					
		for(a=0;a<3;a++)
				{	
					PORTB = PORTB ^ (1<<LED_GREEN);			// -
					_delay_ms(LONG_DELAY);
					PORTB = PORTB & ~(1<<LED_GREEN);
					_delay_ms(SHORT_DELAY);
					
		}
	
		
		_delay_ms(SHORT_DELAY);
		_delay_ms(SHORT_DELAY);
		_delay_ms(LONG_DELAY);			// 3 short delays+ 1 long delay + 1 short delay in the beginning = 7 => pause between two words	
    }

    // Will never reach this
    return 0;
}

/* Interrupt routines ------------------------------------------------*/
