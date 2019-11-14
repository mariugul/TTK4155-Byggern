/*********************************************************
 *               Servo Motor Controller                  *
 *                                                       *
 * The servo motor controls the x/y direction of the     *
 * solenoid that will eventually be used to hit the      *
 * ping pong ball.                                       *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __SERVO_H__
#define __SERVO_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

// Function Prototypes
//---------------------------------------------------
void Servo_Init();                      // Initialize the servo
void Servo_Set_Pos(float joystick_pos); // Set the servo position

#endif