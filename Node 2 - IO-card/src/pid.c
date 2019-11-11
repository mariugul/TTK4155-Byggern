#include "../inc/PID.h"
#include "../inc/Motor.h"
#include <avr/io.h>

// Position and Error
int16_t current_pos = 0; // The current position
int16_t target_pos  = 0; // The wanted position (from joystick)
int16_t last_error  = 0; // The error from previous calculation
int16_t error       = 0; // Current error

// Don't know yet
float integral   = 0; // Integral factor
float derivative = 0; // Derivative factor

// Gain
float kp = 2;   // Proportional gain
float ki = 4;   // Integral gain
float kd = 0.1; // Derivative gain

// Control and direction 
int16_t ctrl; // The calculated control variable
uint8_t dir;  // Direction of the motor

// Functions
void PID_Init()
{
    
}

void PID_Get_Pos()
{
    current_pos = Motor_Read();
}

void PID_Error_Calc()
{
    error = target_pos - current_pos;
}

void PID_Integral_Calc()
{
    if (error < 1)
        integral = 0;
    else
        integral += error;
}

void PID_Derivative_Calc()
{
    derivative = error - last_error;
}

void PID_Ctrl_Var_Calc()
{
    // TODO implement limiting for the control variable
    ctrl = (kp * error) + (ki * integral) + (kd + derivative);
}

uint8_t PID_Speed_Calc()
{
    // Control Values
    uint8_t max_ctrl =  150;
    int16_t min_ctrl = -150;
    uint8_t stop_ctrl = 0;

    // If control variable negative, run counter clockwise
    if (ctrl < 0) {
        if (ctrl < min_ctrl)
            return min_ctrl;
        else
            return ctrl;
    }

    // If control variable posititve, run clockwise
    else if (ctrl > 0) {
        if (ctrl > max_ctrl)
            return max_ctrl;
        else
            return ctrl;
    }

    // If control variable zero, stop motor
    else
        return stop_ctrl;
}

void PID_Update_Pos(uint8_t joystick_pos)
{
    target_pos = joystick_pos;
}

// Updates the value of the motor
void PID_Update(direction_t dir, uint8_t speed)
{

    // Update the error
    last_error = error;
}
