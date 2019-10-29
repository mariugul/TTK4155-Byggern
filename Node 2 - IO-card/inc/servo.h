#ifndef __SERVO_H__
#define __SERVO_H__

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

void servo_init();                      // Initialize the servo
void servo_set_pos(float joystick_pos); // Set the servo position

#endif