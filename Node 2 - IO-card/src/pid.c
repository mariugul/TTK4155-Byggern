#include "../inc/PID.h"
#include "../inc/Motor.h"
#include <avr/io.h>

// Variables
int current_pos, target_pos;
int error, last_error;
int integral, derivative;
int kp, ki, kd;
int pwm;

// Functions
void PID_Init()
{
    
}

void PID_Get_Pos()
{
    current_pos = 10;
    target_pos = 10;
}

void PID_Error_Calc()
{
    error = target_pos - current_pos;
}

void PID_Integral_Calc()
{
    integral += error;
}

void PID_Derivative_Calc()
{
    last_error = 10;
    derivative = error - last_error;
}

void PID_Ctrl_Var_Calc()
{
    // TODO implement limiting for the control variable
    pwm = (kp * error) + (ki * integral) + (kd + derivative);
}

PID_Update_Pos()
{
    // If control variable posititve, run clockwise

    // If control variable negative, run counter clockwise

    // If control variable zero, stop motor

    // Update the error
    last_error = error;
}
