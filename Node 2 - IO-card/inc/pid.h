/*********************************************************
 *                 PID - Controller                      *
 *                                                       *
 * Used for calculating the motor speed and direction.   *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __PID_H__
#define __PID_H__

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
void PID_Get_Motor_Pos(); // Gets the amount of motor rotations
void PID_Error_Calc();
void PID_Update_Last_Error();
void PID_Proportional_Calc();
void PID_Integral_Calc();
void PID_Derivative_Calc();
void PID_Calc(); // Calculates the speed
void PID_Update_Pos(uint8_t joystick_pos);
direction_t PID_Get_Direction(); // Returns the direction that was calculated
uint8_t PID_Get_Speed();         // Returns the speed that was calculated

#endif