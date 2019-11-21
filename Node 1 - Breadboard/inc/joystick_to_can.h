/*********************************************************
 *             Send joystick values to CAN               *
 *                                                       *
 *  This sends the joystick values to Node 2 over CAN.   *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header guard
//---------------------------------------------------
#ifndef __JOY_TO_CAN_H__
#define __JOY_TO_CAN_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>

// Function Prototypes
//---------------------------------------------------
void send_joystick_to_can();

#endif