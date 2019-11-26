/*********************************************************
 *               Pulse Width Modulation                  *
 *                                                       *
 * Pulse width modulation is used for controlling the    *
 * servo motor, as it needs PWM to work. This driver     *
 * is thus included in the servo controller.             *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __PWM_H__
#define __PWM_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

// Function Prototypes
//---------------------------------------------------
void PWM_Init();                              // Enable Pulse Width Modulation
void PWM_Set_Period(float period);            // Set the PWM period
void PWM_Set_Pulse_Width(float joystick_pos); // Set the pulse width

#endif