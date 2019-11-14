#include "../inc/PID.h"
#include "../inc/Timers.h"
#include "../inc/GPIO_Defines.h"
#include <avr/interrupt.h>


void Timers_Init()
{
	printf("<Timers Initialized!>\n");
    Timer0_Init();
    Timer1_Init();
    Timer2_Init();
	Global_Interrupt_Enable();
}

/* * * * * * * * * * * * * *
 * Initialize 8-bit Timers *
 * * * * * * * * * * * * * */
void Timer0_Init(){

}

// Used for the PID-controller 
void Timer2_Init(){

    // Set clock source and 1024 prescaler
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

    // Overflow Interrupt Enable
    TIMSK2 = (1 << TOIE2);
}

/* * * * * * * * * * * * * * *
 * Initialize 16-bit Timers  *
 * * * * * * * * * * * * * * */

// Used for PWM generation for the servo
void Timer1_Init(){

}

void Global_Interrupt_Enable()
{
    sei();
}

void Global_Interrupt_Disable()
{
	cli();
}

