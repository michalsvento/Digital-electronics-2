/*
 * PWM.c
 *
 * Created: 18. 10. 2020 21:40:52
 * Author : Michal
 */ 

#define LED_D1	PB2

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "gpio.h"



int main(void)
{
	GPIO_config_output(&DDRB,LED_D1);
	GPIO_write_low(&PORTB,	LED_D1);
	
	TCCR1A |= (1<<COM1B1); TCCR1A &= !(1<<COM1B0);  //noniverting mode
	
	TCCR1A |= (1<<WGM12	| 1<<WGM11 | 1<<WGM10);  TCCR1A &= !(1 << WGM13);
	TCCR1B |= (1<<WGM12	| 1<<WGM11 | 1<<WGM10);  TCCR1B &= !(1 << WGM13);
	TIM1_overflow_33ms();
	OCR1B = 0x01FF;
	TIMSK1 |= (1 << OCIE1B);
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR(TIMER1_COMPB_vect){
	GPIO_toggle(&PORTB,LED_D1);
	if(OCR1B <= 0x3FF){
		OCR1B = OCR1B + 1;
	}
	OCR1B = 0x01FF;
	
}

