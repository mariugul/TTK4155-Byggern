#ifndef __SERVO_H__
#define __SERVO_H__

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

void Servo_Init();                      // Initialize the servo
void Servo_Set_Pos(float joystick_pos); // Set the servo position

#endif