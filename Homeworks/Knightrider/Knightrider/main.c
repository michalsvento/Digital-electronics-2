/***********************************************************************
 * 
 * Knightrider leds
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_1   PB1    // AVR pin where green LED is connected
#define LED_2   PB2 
#define LED_3   PB3 
#define LED_4   PB4 
#define LED_5   PB5 
#define BLINK_DELAY 250
#define BTN		PD0


#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"
/*
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
    /* GREEN LED */
    // Set pin as output in Data Direction Register...
    //DDRB = DDRB | (1<<LED_1) | (1<<LED_2)| (1<<LED_3) | (1<<LED_4) | (1<<LED_5) ;
	GPIO_config_output(&DDRB,LED_1);
	GPIO_config_output(&DDRB,LED_2);
	GPIO_config_output(&DDRB,LED_3);
	GPIO_config_output(&DDRB,LED_4);
	GPIO_config_output(&DDRB,LED_5);
	
    // ...and turn LED off in Data Register
    //PORTB = PORTB & ~(1<<LED_1) ;
	
	GPIO_write_low(&PORTB,LED_1);
	
	GPIO_config_input_pullup(&DDRD,BTN);
	
	
	
    // Infinite loop
    while (1)
    {	
		//uint8_t i;
        // Pause several milliseconds
		
		/*PORTB = PORTB ^ (1<<LED_1);

		for (i=1; i<=4 ; i++)
		{
			PORTB=(PORTB<<1);
			_delay_ms(BLINK_DELAY);
			}
		for (i=4;i>=1;i--)
		{
			PORTB=(PORTB>>LED_1);
			_delay_ms(BLINK_DELAY);
		}
		
    PORTB = PORTB & ~(1<<LED_1) ;
	*/
		if(!GPIO_read(&PIND,BTN))
		{
		
			GPIO_toggle(&PORTB,LED_1);
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_1);
			GPIO_toggle(&PORTB,LED_2);	
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_2);
			GPIO_toggle(&PORTB,LED_3);
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_3);
			GPIO_toggle(&PORTB,LED_4);
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_4);
			GPIO_toggle(&PORTB,LED_5);
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_5);
			GPIO_toggle(&PORTB,LED_4);
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_4);
			GPIO_toggle(&PORTB,LED_3);
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_3);
			GPIO_toggle(&PORTB,LED_2);
		
			_delay_ms(BLINK_DELAY);
			GPIO_toggle(&PORTB,LED_2);
		}
    }
	return 0;

    // Will never reach this
    
}

