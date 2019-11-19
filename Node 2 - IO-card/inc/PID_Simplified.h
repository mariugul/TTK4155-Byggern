/*********************************************************
 *                 PID - Controller                      *
 *                                                       *
 * Used for calculating the motor speed and direction.   *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __PID_SIMPLIFIED_H__
#define __PID_SIMPLIFIED_H__

// Includes
//---------------------------------------------------
#include "../inc/Motor.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

// Function Prototypes
//---------------------------------------------------
void PID_Init();
void PID_Update_Current_Pos(); // Gets the amount of motor rotations
void PID_Update_Target_Pos(uint8_t joystick_pos);
void PID_Calc(); // Calculates the speed
uint8_t PID_Get_Speed();         // Returns the speed that was calculated
direction_t PID_Get_Direction(); // Returns the direction that was calculated

#endif