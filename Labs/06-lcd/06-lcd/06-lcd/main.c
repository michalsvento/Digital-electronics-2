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


uint8_t customChar[48] = {	

	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
			
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
	0b11111
	
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
	for (uint8_t i = 0; i < 48; i++)
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
	
	
		



 	
	
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	
	// Configure 8-bit Timer/Counter1 for Stopwatch
	// Set prescaler and enable overflow interrupt every 1 s
	
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();
	
	// Configure 8-bit Timer/Counter0 for Stopwatch
	// Set prescaler and enable overflow interrupt every 16 ms
	
	TIM0_overflow_4ms();
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
	static uint8_t minutes = 0;		// minutes  
	static uint16_t secsqr = 0;		// variable for square of seconds
	char lcd_string[2] = "  ";      // String for converting numbers by itoa()
	char lcd_square[4]= "    ";

    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;
		
		tens++;
		if (tens> 9)
		{
			tens=0;
			secs++;
			if (secs>59)
			{
				secs=0;
				minutes++;
				if (minutes>59)
				{
					minutes=0;
				}
			}
		}
				
			

		itoa(tens, lcd_string,10);
		lcd_gotoxy(7,0);
		lcd_puts(lcd_string);
		
		
		itoa(secs, lcd_string,10);
		if(secs<10)					//single digit or two digits
		{
			lcd_gotoxy(5,0);		
		}
		else
		{
			lcd_gotoxy(4,0);	
		}
		lcd_puts(lcd_string);
		
		
		itoa(minutes, lcd_string,10);
		if(minutes<10)
		{
			lcd_gotoxy(2,0);
		}
		else
		{
			lcd_gotoxy(1,0);
		}
		lcd_puts(lcd_string);
			
		// counts the square of secs and show from pos 11,0
		secsqr = secs*secs;
		if (secs==0)				// for reset on the positions 12-14
		{
			lcd_gotoxy(11,0);	
			lcd_puts("0   ");
		}
		else
		{
			itoa(secsqr,lcd_square,10);
			lcd_gotoxy(11,0);
			lcd_puts(lcd_square);
		}

		

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
	uint8_t running_text[32]= "    I like Digital electronics! ";
	char lcd_shown[5]= "     ";
	lcd_gotoxy(11,1);
	
	if(i< (sizeof(running_text)-4))
	{
		lcd_shown[0] = running_text[i];
		lcd_shown[1] = running_text[i+1];
		lcd_shown[2] = running_text[i+2];
		lcd_shown[3] = running_text[i+3];
		lcd_shown[4] = running_text[i+4];
		lcd_puts(lcd_shown);
		i++;
	}

	if(i==(sizeof(running_text)-1))
	{
		lcd_shown[0] = running_text[i];
		lcd_shown[1] = running_text[0];
		lcd_shown[2] = running_text[1];
		lcd_shown[3] = running_text[2];
		lcd_shown[4] = running_text[3];
		lcd_puts(lcd_shown);
		i=0;
	}

	if(i==(sizeof(running_text)-2))
	{
		lcd_shown[0] = running_text[i];
		lcd_shown[1] = running_text[i+1];
		lcd_shown[2] = running_text[0];
		lcd_shown[3] = running_text[1];
		lcd_shown[4] = running_text[2];
		lcd_puts(lcd_shown);
		i++;
		}
	if(i==(sizeof(running_text)-3))
	{
		lcd_shown[0] = running_text[i];
		lcd_shown[1] = running_text[i+1];
		lcd_shown[2] = running_text[i+2];
		lcd_shown[3] = running_text[0];
		lcd_shown[4] = running_text[1];
		lcd_puts(lcd_shown);
		i++;
	}
	if(i==(sizeof(running_text)-4))
	{
		lcd_shown[0] = running_text[i];
		lcd_shown[1] = running_text[i+1];
		lcd_shown[2] = running_text[i+2];
		lcd_shown[3] = running_text[i+3];
		lcd_shown[4] = running_text[0];
		lcd_puts(lcd_shown);
		i++;
		}
	

}

/**
 * ISR starts when Timer/Counter0 overflows. Move every 16ms
 * one user-defined character. Resets the bar when
 * when lcd_gotoxy(10,1) & symbol 0x05 is reached
 * user-defined character from 0 - 5
 * "     "|    " "||   " "|||  " "|||| " "|||||"
 */


ISR(TIMER0_OVF_vect)
{	
	static uint8_t symbol = 0;
	static uint8_t position = 0;
	
	
	lcd_gotoxy(1 + position, 1);
	lcd_putc(symbol);

	symbol++;
	if(symbol>5)
	{
		symbol=0;
		position++;
		
		if (position>9)
		{
			lcd_gotoxy(1,1);
			lcd_puts("          ");			// 10 spaces for reset
			position=0;
		}
	}
	
}
