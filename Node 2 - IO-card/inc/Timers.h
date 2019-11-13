#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <avr/io.h>
#include <stdio.h>

void Timers_Init(); // Set up the timers
void Timer0_Init(); // Not in used
void Timer1_Init(); // Used for PWM
void Timer2_Init(); // Used for the PID-controller 
void Global_Interrupt_Enable();
void Global_Interrupt_Disable();

#endif