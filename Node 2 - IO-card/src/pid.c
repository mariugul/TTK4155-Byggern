/*********************************************************
 *               PID - Controller                        *
 * Used for calculating the motor speed and direction.   *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/PID.h"

// Definitions 
//---------------------------------------------------
#define ERROR_MAX  (50 / ki) // Limit the integral size

// Variables
//---------------------------------------------------

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

// Speed and Directions
uint8_t speed = 0;
direction_t direction;

// Function Definitions                               
//---------------------------------------------------
void PID_Init()
{
    printf("<PID Initialized>\n");
    // TODO - Initialize the motor to starting position
    // TODO - Create motor "calibrate" function to do this
}

// Gets the current position of the motor
void PID_Get_Motor_Pos()
{
    // TODO - Recalculate this to ADC values. Right now it's motor rotations
    //int16_t motor_rotations = Motor_Read();
    //current_pos = "some math with motor_rotations"
}

// Calculates current error
void PID_Error_Calc()
{
    // Calculate current error
    error = target_pos - current_pos;

    // Limit the error size
    if(error > ERROR_MAX)
        error = ERROR_MAX;
}

// Updates the last error
void PID_Update_Last_Error()
{  
    last_error = error;
}

// Calculates the proportional part
void PID_Proportional_Calc()
{
    // Calculate proportional gain
    proportion = kp * error;
}

// Calculates the integral part
void PID_Integral_Calc()
{
    // When the error is close to zero, set integral part to 0
    if (error < 1)
        integral = 0;

    // Increase integral term when in "integral active zone"
    else if (error < ERROR_MAX && error > 1)
        integral += ki * error;
}

// Calculates the derivative part
void PID_Derivative_Calc()
{
    // When error is close to zero, set derivative to zero
    if (error < 1)
        derivative = 0;

    // Calculate derivative
    else
        derivative = kd * (error - last_error);
}

// Calculates the whole PID speed and direction
void PID_Calc()
{   
    // Calculate the speed 
    uint8_t speed_ctrl = proportion + integral + derivative;

    // Control Values
    uint8_t max_speed =  150;
    int16_t min_speed = -150;
    uint8_t stop_speed = 0;

    // If control variable negative, run counter clockwise
    if (speed_ctrl < 0) {
        // Set direction left
        direction = left;

        // Check for values outside minimum and set speed to positive corresponding value
        if (speed_ctrl < min_speed)
            speed = abs(min_speed);
        else
            speed = abs(speed_ctrl);
    }

    else if (speed_ctrl > 0) {
        // Set direction right
        direction = right;

        // Check for values outside maximum and set speed to corresponding value
        if (speed_ctrl > max_speed)
            speed = max_speed;
        else
            speed = speed_ctrl;
    }

    // If control variable zero, stop motor
    else
        speed = stop_speed;
}


// Updates the target position from joystick (Used in CAN interrupt)
void PID_Update_Pos(uint8_t joystick_pos)
{
    target_pos = joystick_pos;
}

// Used for returning the speed to the main loop
uint8_t PID_Get_Speed() 
{
    return speed;
}

// Used for returning the direction to the main loop
direction_t PID_Get_Direction()
{
    return direction;
}