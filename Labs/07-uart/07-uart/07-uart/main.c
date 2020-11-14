/***********************************************************************
 * 
 * Analog-to-digital conversion with displaying result on LCD and 
 * transmitting via UART.
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
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library

#ifndef F_CPU
#define F_CPU 16000000
#endif



/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Use Timer/Counter1
 * and start ADC conversion four times per second. Send value to LCD
 * and UART.
 */
int main(void)
{
	//
	
	
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0);
    lcd_puts("value:");
    lcd_gotoxy(3, 1);
    lcd_puts("key:");

    // Configure ADC to convert PC0[A0] analog value
    // Set ADC reference to AVcc
	
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);

    // Set input channel to ADC0
	
	ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));
	
    // Enable ADC module
	
	ADCSRA |= (1<<ADEN);
	
    // Enable conversion complete interrupt
	
	ADCSRA |= (1<<ADIE);
    // Set clock prescaler to 128
	
	ADCSRA |= ((1<ADPS2)|(1<ADPS1)|(1<ADPS0));

	

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Enable interrupt and set the overflow prescaler to 262 ms
	
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();

    // Initialize UART to asynchronous, 8N1, 9600
	
	uart_init(UART_BAUD_SELECT(9600,F_CPU));

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
 * ISR starts when Timer/Counter1 overflows. Use single conversion mode
 * and start conversion four times per second.
 */
ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
	
	ADCSRA |= (1<< ADSC);

	

}

/* -------------------------------------------------------------------*/
/**
 * ISR starts when ADC completes the conversion. Display value on LCD
 * and send it to UART.
 */
ISR(ADC_vect)
{  
	uint16_t  value=0;
	static uint16_t  compare=0;	
	uint8_t parity=0;
	char lcd_string[4];
	
	value=ADC;

	if(compare!=value)			//makes this process when ADC changes value
	{
		
		//Show value in decimal
		itoa(value,lcd_string,10);
		lcd_gotoxy(8,0);
		lcd_puts("     ");
		lcd_gotoxy(8,0);
		lcd_puts(lcd_string);
		
		//  Display parity bit and send UART only for Buttons
		
		//uart DECIMAL
		uart_puts("ADC decimal ");
		uart_puts(lcd_string);
		
		// odd parity 
		char lcd_binary [10];
		for (uint8_t i=0; value !=0; i++)
		{
			lcd_binary[i]= value %2;
			if(lcd_binary[i] == 1)
			{
				parity++;
			}
			value= value / 2;
		}
				
				
		lcd_gotoxy(15,1);
				
		if (parity % 2)
		{
			uart_puts(" PARITY 1 ");
			lcd_puts("1");
		}
		else
		{
			uart_puts(" PARITY 0 ");
			lcd_puts("0");
		}
				
		value=ADC;	// return orig. value, which was changed in cycle
		
		
		
	

		// show value in hex
		itoa(value,lcd_string,16);
		lcd_gotoxy(13,0);
		lcd_puts("     ");
		lcd_gotoxy(13,0);
		lcd_puts(lcd_string);
		
		
			
		// Display the name of key on LCD & UART
		
		lcd_gotoxy(8,1);
		lcd_puts("      ");
		// none
		if(value >= 1016)
		{
			lcd_gotoxy(8,1);
			lcd_puts("none");
			uart_puts("\n");
		}
		
		// RIGHT
		if(value <=2 )
		{
			lcd_gotoxy(8,1);
			lcd_puts("RIGHT");
			uart_puts("RIGHT");
			uart_puts("\n");
		}
		
		// UP
		if(value >= 99 && value <=103 )
		{
			lcd_gotoxy(8,1);
			lcd_puts("UP");
			uart_puts("UP");
			uart_puts("\n");
		}
		
		// DOWN
		if(value >= 244 && value <=248 )
		{
			lcd_gotoxy(8,1);
			lcd_puts("DOWN");
			uart_puts("DOWN");
			uart_puts("\n");
		}
		
		// LEFT
		if(value >= 401 && value <=405 )
		{
			lcd_gotoxy(8,1);
			lcd_puts("LEFT");
			uart_puts("LEFT");
			uart_puts("\n");
		}
		
		//SELECT
		if (value >= 648 && value<=655)
		{
			lcd_gotoxy(8,1);
			lcd_puts("SELECT");
			uart_puts("SELECT");
			uart_puts("\n");
		}	
		
		
		compare=value;		//
		
	}



}
	