/*********************************************************
 *               Timers and Interrupts                   *
 *                                                       *
 * This file sets up the timer counters and the timer    *
 * interrupts.                                           *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/timer.h"
#include <avr/interrupt.h>

// Variables
//---------------------------------------------------
int overflow_count = 0;

// Function Definitions
//---------------------------------------------------

void timer_init() // Initialize timer
{
    TCNT1 = 63974; // Start the timer
    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12); // Timer mode with 1024 prescaler
    TIMSK = (1 << TOIE1); // Enable timer1 overflow interrupt(TOIE1)
    sei(); // Enable global interrupts by setting global interrupt enable bit in SREG
}

void timer_counter(int overflow)
{
    int overflow_count = overflow;
}

ISR(TIMER1_OVF_vect)
{
    // Code here
}