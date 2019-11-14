/*********************************************************
 *                   Motor Controller                    *
 *                                                       *
 * This is the controller for the motor. It will control *
 * the arm moving in left and right direction. The motor *
 * controller has to be viewed in accordance with the PID*
 * -controller as they work together.                    *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __MOTOR_H__
#define __MOTOR_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include "../inc/GPIO_Defines.h"
#include <stdio.h>

// Typedefs
//---------------------------------------------------
typedef enum {left, right, stop} direction_t;

// Funtion Prototypes
//---------------------------------------------------
int16_t Motor_Read();
void Motor_Init();
void Motor_Encoder_Reset();
void Motor_Set_Dir(direction_t dir);
void Motor_Set_Speed(uint8_t speed);
void Motor_Move(uint8_t dir, uint8_t speed);

#endif