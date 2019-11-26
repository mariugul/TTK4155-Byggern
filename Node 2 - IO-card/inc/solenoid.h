/*********************************************************
 *                 Solenoid Controller                   *
 *                                                       *
 * The solenoid will be hitting the ping pong ball. It's *
 * controller with pulse width modulation and thus,      *
 * includes the PWM driver.                              *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __SOLENOID_H__
#define __SOLENOID_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

// Function Prototypes
//---------------------------------------------------
void Solenoid_Init();
bool Solenoid_Pulse();
void Solenoid_Activate();
void Solenoid_Deactivate();

#endif