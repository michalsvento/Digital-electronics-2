/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC

/* Variables ---------------------------------------------------------*/
	static uint8_t  led=0;
	static uint8_t pos=0;



/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */
int main(void)
{
    // Configure SSD signals
    SEG_init();
	
	/* Configure 16-bit Timer/Counter1
    * Set prescaler and enable overflow interrupt */
	TIM1_overflow_33ms();
	TIM1_overflow_interrupt_enable();
	
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


ISR(TIMER1_OVF_vect)
{	
	SEG_update_shift_regs(led,pos);

	static uint8_t Ndisplays=4;		//Number of displays
	++led;
	
	if(led<=4)
	{
		if(led==4)			// last segment position 0
		{
			if(pos<(Ndisplays-1))		
			{
				pos++;		// move to position 3(last)
				led--;		//	SegmentD doesn't move
			}
		}
	}
	
	if( (led<=7)  && (led>4 ))
	{
		
		if(led==7)
		{
			if(pos>0)
			{
				pos--;
				led--;
			}
			else
			{
				led=1;
			}
		}
	}

		
}
