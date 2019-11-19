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
#define NODE1_INIT_ID 1
#define NODE2_READY_ID 2
#define NODE2_GAME_OVER_ID 3
#define NODE1_QUIT_ID 4

// Joystick value index in array
#define JSTICK_X   0
#define JSTICK_Y   1
#define JSTICK_BUT 2
#define SLIDER_L   3
#define SLIDER_R   4
#define PUSH_BUT_L 5
#define PUSH_BUT_R 6

// Button push
#define PUSHED HIGH
#define NOT_PUSHED LOW

#endif
//---------------------------------------------------
// End Main.h
//---------------------------------------------------