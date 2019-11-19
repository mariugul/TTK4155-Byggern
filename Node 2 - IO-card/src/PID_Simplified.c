/*********************************************************
 *               P - Controller                        *
 * Used for calculating the motor speed and direction.   *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/PID.h"

// Definitions
//---------------------------------------------------
#define MAX_ERROR 250 // Limit the error size
#define MIN_ERROR -250
#define MAX_SPEED 200
#define MIN_SPEED 100
#define dt 0.01
#define epsilon 0.01

// Variables
//---------------------------------------------------

// Position and Error
int16_t error = 0; // Current error (-250 : 250)
int16_t prev_error = 0; // The error from previous calculation
int16_t current_pos = 0; // The current position (0-250)
int16_t target_pos = 0; // The wanted position (from joystick) (0-255)

// Speed and Directions
uint8_t speed = 0;
direction_t direction;

// Factors
float proportion = 0; // Proportional factor
float integral   = 0; // Integral factor
float derivative = 0; // Derivative factor

// Gain
float kp = 2; // Proportional gain
float ki = 3.5; // Integral gain
float kd = 1.2; // Derivative gain



// Function Definitions
//---------------------------------------------------

// Initialize the controller
void PID_Init(){}

// Gets the current position of the motor
void PID_Update_Current_Pos()
{
    // Calculate the motor rotations
    int16_t rotations = Motor_Read(); // 0 - 8000 value
    int16_t max_rotations = 8000;
    uint8_t adc_max_value = 255;
    int16_t scaled_rotations = (max_rotations / adc_max_value) + 1; // The +1 is because the result is floating point and we need to round up

    // Calculate the current position
    current_pos = (rotations / scaled_rotations);
    printf("Current position: %d\n", current_pos);
}

void PID_Update_Target_Pos(uint8_t joystick_pos)
{
    target_pos = joystick_pos;
    printf("Target position: %d\n", current_pos);
}

void PID_Calc()
{
    PID_Update_Current_Pos();
    //PID_Update_Target_Pos(); --> Happens in CAN interrupt

    // Calculate current error
    error = target_pos - current_pos;

    // Calculate integral term
    if (abs(error) > MAX_ERROR)
        integral += error * dt;

    // Calculate differential term
    derivative = (error - prev_error) / dt;

    // Calculate the speed
    speed = kp * error + ki * integral + kd * derivative;
    printf("   Speed: %d\n", speed);
    //-----------------------------

    // Filter for speed safety
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;

    else if (speed < MIN_SPEED)
        speed = MIN_SPEED;

    // Set the correct direction from the error values
    if (error > 0)
        direction = left;
    else if (error < 0)
        direction = right;
    
    // Update error
    prev_error = error;
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
