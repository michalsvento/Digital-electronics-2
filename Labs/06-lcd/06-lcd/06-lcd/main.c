/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function


uint8_t customChar[40] = {
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	
	0b11110,
	0b11110,
	0b11110,
	0b11110,
	0b11110,
	0b11110,
	0b11110,
	0b11110,
	
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	
};
/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
int main(void)
{
	// Initialize LCD display
	lcd_init(LCD_DISP_ON);

	// Set pointer to beginning of CGRAM memory
	lcd_command(1 << LCD_CGRAM);
	for (uint8_t i = 0; i < 40; i++)
	{
		// Store all new chars to memory line by line
		lcd_data(customChar[i]);
	}
	// Set DDRAM address
	lcd_command(1 << LCD_DDRAM);
	
	// Display first custom character
	
	
	

    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
	
	lcd_gotoxy(11, 0);
	lcd_puts("a");
	


// 	lcd_gotoxy(11, 1);
// 	lcd_puts("c");
	
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	
	// Configure 8-bit Timer/Counter1 for Stopwatch
	// Set prescaler and enable overflow interrupt every 1 s
	
	TIM1_overflow_1s();
	TIM1_overflow_interrupt_enable();
	
	// Configure 8-bit Timer/Counter2 for Stopwatch
	// Set prescaler and enable overflow interrupt every 16 ms
	
	TIM0_overflow_16ms();
	TIM0_overflow_interrupt_enable();
	

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
	static uint8_t tens = 0;        // Tenths of a second
	static uint8_t secs = 0;        // Seconds
	static uint8_t tensofsecs = 0;		// Tenths of a second
	static uint8_t minutes =0;		// minutes
	static uint8_t tensofmins =0;		// t of a minute
	char lcd_string[2] = "  ";      // String for converting numbers by itoa()

    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;

        // WRITE YOUR CODE HERE
		tens++;
		if (tens> 9)
		{
			tens=0;
			secs++;
			if (secs>9)
			{
				secs=0;
				tensofsecs++;
				if (tensofsecs>6)
				{	
					tensofsecs=0;
					minutes++;
					if (minutes>9)
					{
						minutes=0;
						tensofmins++;
						if (tensofmins > 6)
						{
							tensofmins=0;
						}
					}
				}
				
			}
				
		}
		
		itoa(tens, lcd_string,10);
		lcd_gotoxy(7,0);
		lcd_puts(lcd_string);
		
		itoa(secs, lcd_string, 10);
		lcd_gotoxy(5,0);
		lcd_puts(lcd_string);
		
		itoa(tensofsecs, lcd_string, 10);
		lcd_gotoxy(4,0);
		lcd_puts(lcd_string);
		
		itoa(minutes, lcd_string, 10);
		lcd_gotoxy(2,0);
		lcd_puts(lcd_string);
		
		itoa(tensofmins, lcd_string, 10);
		lcd_gotoxy(1,0);
		lcd_puts(lcd_string);
	

    }
}

/*--------------------------------------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows. Move one letter left every
 * 1 s.
 */
ISR(TIMER1_OVF_vect)
{
	static uint8_t i=0;
	char lcd_string[10]= "TEST TEXT ";
	char lcd_shown[5]= "     ";
	lcd_gotoxy(11,1);
	
	if(i< (sizeof(lcd_string)-4))
	{
		lcd_shown[0] = lcd_string[i];
		lcd_shown[1] = lcd_string[i+1];
		lcd_shown[2] = lcd_string[i+2];
		lcd_shown[3] = lcd_string[i+3];
		lcd_shown[4] = lcd_string[i+4];
		lcd_puts(lcd_shown);
		i++;
	}
	if(i==(sizeof(lcd_string)-4))
	{
		lcd_shown[0] = lcd_string[i];
		lcd_shown[1] = lcd_string[i+1];
		lcd_shown[2] = lcd_string[i+2];
		lcd_shown[3] = lcd_string[i+3];
		lcd_shown[4] = lcd_string[0];
		lcd_puts(lcd_shown);
		i++;
	}
	if(i==(sizeof(lcd_string)-3))
	{
		lcd_shown[0] = lcd_string[i];
		lcd_shown[1] = lcd_string[i+1];
		lcd_shown[2] = lcd_string[i+2];
		lcd_shown[3] = lcd_string[0];
		lcd_shown[4] = lcd_string[1];
		lcd_puts(lcd_shown);
		i++;
	}
	if(i==(sizeof(lcd_string)-2))
	{
		lcd_shown[0] = lcd_string[i];
		lcd_shown[1] = lcd_string[i+1];
		lcd_shown[2] = lcd_string[0];
		lcd_shown[3] = lcd_string[1];
		lcd_shown[4] = lcd_string[2];
		lcd_puts(lcd_shown);
		i++;
	}
	if(i==(sizeof(lcd_string)-1))
	{
		lcd_shown[0] = lcd_string[i];
		lcd_shown[1] = lcd_string[0];
		lcd_shown[2] = lcd_string[1];
		lcd_shown[3] = lcd_string[2];
		lcd_shown[4] = lcd_string[3];
		lcd_puts(lcd_shown);
		i=0;
	}
	

}

/**
 * ISR starts when Timer/Counter0 overflows. Move every 16ms
 * one user-defined character. Resets the bar when
 * when lcd_gotoxy(7,1) & symbol 0x04 is reached
 */

ISR(TIMER0_OVF_vect)
{
	static uint8_t symbol = 0;
	static uint8_t position = 0;

	lcd_gotoxy(1 + position, 1);
	lcd_putc(symbol);
	
	symbol++;
	if(symbol>4)
	{
		position++;
		symbol=0;
		if (position>7)
		{
			lcd_gotoxy(1,1);
			lcd_puts("        ");			// 8 spaces for reset
			position=0;
		}
	}
}
