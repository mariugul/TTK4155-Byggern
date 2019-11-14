/*********************************************************
 *               Interrupt Handlers                      *
 *                                                       *
 *  These are the Interrupt Handlers for CAN Bus,        *
 *  motor/PID control and Solenoid. They also have a few *
 *  functions for updating "interrupt flags" that are our*
 *  own flags, used mainly for motor control.            *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __IRQ_HANDLERS_H__
#define __IRQ_HANDLERS_H__

// Includes
//---------------------------------------------------
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>

// Function Prototypes
//---------------------------------------------------
void IRQ_Set_Motor_Flag();   // Updates local motor flag to true
void IRQ_Clear_Motor_Flag(); // Updates motor flag to false
bool IRQ_Motor_Flag();       // Returns the motor flag, so it can be used in main.c

#endif