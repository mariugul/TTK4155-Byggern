#ifndef __PWM_H__
#define __PWM_H__

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

void PWM_Init(); // Enable Pulse Width Modulation
void PWM_Set_Period(float period);             // Set the PWM period
void PWM_Set_Pulse_Width(float joystick_pos);  // Set the pulse width

#endif