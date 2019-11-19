/*********************************************************
 *               Timers and Interrupts                   *
 *                                                       *
 * This file sets up the timer counters and the timer    *
 * interrupts.                                           *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __TIMER_H__ 
#define __TIMER_H__

// Includes
//---------------------------------------------------
#include <avr/io.h> // Include AVR library

// Function Prototypes
//---------------------------------------------------
void timer_init(); // Initialize timer

#endif