#include "../inc/pid.h"
#include <avr/io.h>

// Variables
int current_pos, target_pos;
int error, last_error;
int integral, derivative;
int kp, ki, kd;
int pwm;


// Functions 
void pid_init()
{
    
}

void pid_get_pos()
{
    current_pos = 10;
    target_pos = 10;
}

void pid_error_calc()
{
    error = target_pos -current_pos;
}

void pid_integral_calc()
{
    integral += error;
}

void pid_derivative_calc()
{
    last_error = 10;
    derivative = error - last_error;
}

void pid_ctrl_var_calc()
{
    // TODO implement limiting for the control variable 
    pwm = (kp * error) + (ki * integral) + (kd + derivative);
}

pid_update_pos()
{
    // If control variable posititve, run clockwise

    // If control variable negative, run counter clockwise

    // If control variable zero, stop motor

    // Update the error
    last_error = error;
}




