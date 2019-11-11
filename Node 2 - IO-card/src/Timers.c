#include "../inc/PID.h"
#include "../inc/GPIO_Defines.h"
#include <avr/io.h>



void Timers_Init()
{
    Timer0_Init();
    Timer1_Init();
    Timer2_Init();
}

/* * * * * * * * * * * * * *
 * Initialize 8-bit Timers *
/* * * * * * * * * * * * * */
void Timer0_Init(){

}

// Used for the PID-controller 
void Timer2_Init(){

    // Set clock source and 1024 prescaler
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

    // Overflow Interrupt Enable
    TIMSK2 = (1 << TOIE2);

    // Enable global interrupts
    Global_Interrupt_Enable();
}

/* * * * * * * * * * * * * * *
 * Initialize 16-bit Timers  *
/* * * * * * * * * * * * * * */

// Used for PWM generation for the servo
void Timer1_Init(){

}

void Global_Interrupt_Enable()
{
    __enable_interrupt();
}

