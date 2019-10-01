/*
 * timer.c
 *
 * Created: 01.10.2019 18:56:57
 *  Author: Marius
 */ 
#include "timer.h"

int overflow_count = 0;

void timer_init() 							// Initialize timer
{
	TCNT1  = 63974;							// Start the timer
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);			// Timer mode with 1024 prescaler
	TIMSK = (1 << TOIE1) ;					// Enable timer1 overflow interrupt(TOIE1)
	sei();									// Enable global interrupts by setting global interrupt enable bit in SREG
	
	
}

void timer_counter(int overflow)
{
	int overflow_count = overflow;
}


ISR (TIMER1_OVF_vect) // timer0 overflow interrupt
{
	static int count = 0;
	TCNT1 = 0;
	TIFR=0x01;		  //clear timer1 overflow flag	
	oled_print(++count);	         
}