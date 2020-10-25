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

/* Defines -----------------------------------------------------------*/

#define  BTN PB1

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC
#include "gpio.h"


static uint8_t position = 0;
static uint8_t units = 0;
static uint8_t decimals = 0;
static uint8_t seconds	=0;
static uint8_t tens = 0;

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
	
	// Configure PB0 as input pull up & for Pin interrupt 
	GPIO_config_input_pullup(&DDRB,BTN);
	PCICR = PCICR | (1 << PCIE0);		
	PCMSK0 = PCMSK0 |(1 << PCINT1);
	
    /* Configure 8-bit Timer/Counter0
     * Set prescaler and enable overflow interrupt */
	TIM0_overflow_16ms();
	TIM0_overflow_interrupt_enable();
    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
	TIM1_overflow_262ms();
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
/**
 * ISR starts when is change on PB1
 */

ISR(PCINT0_vect)
{
	if(!GPIO_read(&PINB,BTN)){
		units = 0;
		decimals = 0;
		seconds	=0;
		tens = 0;
	}

}


/**
 * ISR starts when Timer/Counter0 overflows.  Display value on SSD
 */

ISR(TIMER0_OVF_vect)
{
	

	switch(position){
		case 0:
			SEG_update_shift_regs(units,0,1);
			position=1;
			break;
		case 1:
			SEG_update_shift_regs(decimals,1,1);
			position=2;
			break;
		case 2:
			SEG_update_shift_regs(seconds,2,0);
			position=3;
			break;
		case 3:
			SEG_update_shift_regs(tens,3,1);
			position=0;
			break;
		default:
			SEG_update_shift_regs(units,0,1);
			position=1;
			break;
	}
			
}

/* ISR starts when Timer/Counter1 overflows.Increment decimal counter value 
 */
ISR(TIMER1_OVF_vect)
{
	units++;
	if(units>9)
	{
		units=0;
		decimals++;
			if(decimals>5)
			{
				decimals=0;
				seconds++;
					if(seconds> 9)
					{
						seconds=0;
						tens++;
							if(tens>5)
							{
								tens=0;
							}
					}
			}
	}
}



