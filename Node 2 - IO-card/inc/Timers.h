/*********************************************************
 *               Timers and Interrupts                   *
 *                                                       *
 * This file sets up the timer counters and the timer    *
 * interrupts. It should be viewed in accordance with    *
 * "IRQ_Handlers", as they describe the interrupt handler*
 * functionality.                                        *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __TIMERS_H__
#define __TIMERS_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdio.h>

// Function Prototypes
//---------------------------------------------------
void Timers_Init(); // Set up the timers
void Timer0_Init(); // Not in used
void Timer1_Init(); // Used for PWM
void Timer2_Init(); // Used for the PID-controller
void Global_Interrupt_Enable();
void Global_Interrupt_Disable();

#endif