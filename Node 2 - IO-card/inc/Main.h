/*********************************************************
 *             NODE 2 - Ping Pong Game                   *
 *  This is the main header file for controlling Node 2. *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __MAIN_H_
#define __MAIN_H_

// Definitions
//---------------------------------------------------

// This is the oscillator speed. It needs to be defined first because of util/delay library.
#define F_CPU 16000000UL

// The ID for receiving joystick data
#define JSTICK_CAN_ID 10

// Joystick value index in array
#define JSTICK_X   0
#define JSTICK_Y   1
#define JSTICK_BUT 2
#define SLIDER_L   3
#define SLIDER_R   4
#define PUSH_BUT_L 
#define PUSH_BUT_R

// Button push
#define PUSHED HIGH
#define NOT_PUSHED LOW

#endif
//---------------------------------------------------
// End Main.h
//---------------------------------------------------