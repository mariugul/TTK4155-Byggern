#ifndef __PWM_H__
#define __PWM_H__

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

void pwm_init(); // Enable Pulse Width Modulation
void pwm_set_period(float period);             // Set the PWM period
void pwm_set_pulse_width(float joystick_pos);  // Set the pulse width

#endif