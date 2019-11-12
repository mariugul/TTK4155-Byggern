#include "../inc/PID.h"
#include "../inc/Motor.h"
#include <avr/io.h>

// Position and Error
int16_t current_pos = 0; // The current position
int16_t target_pos  = 0; // The wanted position (from joystick)
int16_t last_error  = 0; // The error from previous calculation
int16_t error       = 0; // Current error

// Factors
float proportion = 0; // Proportional factor
float integral   = 0; // Integral factor
float derivative = 0; // Derivative factor

// Gain
float kp = 2;   // Proportional gain
float ki = 3.5; // Integral gain
float kd = 1.2; // Derivative gain

// Control 
int16_t speed; // The calculated control variable

// Limit

int error_max = (50 / ki); // Limit the integral size

// Functions
void PID_Init()
{
    // TODO - Initialize the motor to starting position
    // TODO - Create motor "calibrate" function to do this
}

void PID_Get_Pos()
{
    // TODO - Recalculate this to ADC values. Right now it's motor rotations
    int16_t motor_rotations = Motor_Read();
    current_pos = 
}

void PID_Error_Calc()
{
    // Calculate current error
    error = target_pos - current_pos;

    // Limit the error size
    if(error > error_max)
        error = error_max;
}

void PID_Update_Last_Error()
{  
    last_error = error;
}

void PID_Propotional_Calc()
{
    // Calculate proportional gain
    proportion = kp * error;
}

void PID_Integral_Calc()
{
    // When the error is close to zero, set integral part to 0
    if (error < 1)
        integral = 0;

    // Increase integral term when in "integral active zone"
    else if (error < error_max && error > 1)
        integral += ki * error;
}

void PID_Derivative_Calc()
{
    // When error is close to zero, set derivative to zero
    if (error < 1)
        derivative = 0;

    // Calculate derivative
    else
        derivative = kd * (error - last_error);
}


uint8_t PID_Speed_Calc()
{   
    // Calculate necesarry steps before speed
    PID_Get_Pos();
    PID_Error_Calc();
    PID_Propotional_Calc();
    PID_Integral_Calc();
    PID_Derivative_Calc();

    // Calculate the speed 
    speed = proportion + integral + derivative;

    // Control Values
    uint8_t max_speed =  150;
    int16_t min_speed = -150;
    uint8_t stop_speed = 0;

    // If control variable negative, run counter clockwise
    if (speed < 0) {
        if (speed < min_speed)
            return min_speed;
        else
            return speed;
    }

    // If control variable posititve, run clockwise
    else if (speed > 0) {
        if (speed > max_speed)
            return max_speed;
        else
            return speed;
    }

    // If control variable zero, stop motor
    else
        return stop_speed;
}

direction_t PID_Direction_Calc()
{
    if (speed < 0)
        return = left;

    else if (speed > 0)
        return = right;

    else 
        return stop;
}

void PID_Update_Pos(uint8_t joystick_pos)
{
    target_pos = joystick_pos;
}

