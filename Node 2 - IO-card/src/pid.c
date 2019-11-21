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
#define MAX_ERROR 255 // Limit the error size
#define MIN_ERROR -255
#define MAX_SPEED 200
#define MIN_SPEED 50
#define dt 0.02
#define epsilon 0.01

// Variables
//---------------------------------------------------

// Position and Error
int16_t error = 0; // Current error (-250 : 250)
int16_t prev_error = 0; // The error from previous calculation
uint8_t current_pos = 0; // The current position (0-250)
int16_t target_pos = 0; // The wanted position (from joystick) (-128: 128)

// Speed and Directions
uint8_t speed = 0;
int16_t ctrl = 0; // Control variable for speed calculations
direction_t direction;

// Factors
float proportion = 0; // Proportional factor
float integral   = 0; // Integral factor
float derivative = 0; // Derivative factor

// Gain
float kp = 3.5; // Proportional gain
float ki = 0; // Integral gain
float kd = 0; // Derivative gain



// Function Definitions
//---------------------------------------------------

// Initialize the controller
void PID_Init(){
    // Forever alone :'(
	
}

// Gets the current position of the motor
void PID_Update_Current_Pos()
{
    // Calculate the motor rotations
    int16_t rotations = Motor_Read(); // 0 - 8000 value
    int16_t max_rotations = 8000;
    uint8_t adc_max_value = 255;
    int16_t scaled_rotations = (max_rotations / adc_max_value) + 1; // The +1 is because the result is floating point and we need to round up
	
	// Make sure current pos is never negative
	if ((rotations / scaled_rotations) < 0)
		current_pos = 0;
	else 
		current_pos = (rotations / scaled_rotations);
		
    printf("Current position: %d\n", current_pos);
}

// Takes a number between 0 - 255
void PID_Update_Target_Pos(uint8_t joystick_pos)
{
    target_pos = joystick_pos;
    printf("Target position: %d\n", target_pos);
}

void PID_Calc()
{
    PID_Update_Current_Pos();
    //PID_Update_Target_Pos(); --> Happens in CAN interrupt

    // Calculate current error
    error = (target_pos - current_pos); 
	//*DEBUG
	printf("Error: %d\n", error);

    // Calculate integral term
    if(abs(error) < 10)
        integral = 0;
    else
        integral += error * dt;

    //*DEBUG
    //printf("Integral: %d\n", (int)integral);

    // Calculate differential term
    derivative = (error - prev_error) / dt;
    //*DEBUG
    //printf("Derivative: %d\n", (int)derivative);

    // Calculate the speed
    ctrl = (kp * error) + (ki * integral) + (kd * derivative);
	//*DEBUG
	//printf("kp*error: %d,  ki*integal: %d,  kd*derivative: %d\n", (int)(kp * error), (int)(ki * integral), (int)(kd * derivative));
    //-----------------------------

    //*DEBUG
    //printf("speed: %d\n", speed);
    
	/*
    // Filter for speed safety
    if (ctrl > MAX_ERROR)
        speed = MAX_SPEED;
	
	else if (ctrl < MIN_ERROR)
		speed = MIN_SPEED;
	*/
	
    // Set the correct direction from the error values
	if (ctrl < 0){
		direction = right;
		if (ctrl > -MAX_SPEED){
			speed = abs(ctrl);
		}
		else {
			speed = MAX_SPEED;
		}
	}
	else
	{
		direction = left;
		if (ctrl < MAX_SPEED){
			speed = ctrl;
		}
		else {
			speed = MAX_SPEED;
		}
	}
	
	if (ctrl < MIN_SPEED)
		speed = MIN_SPEED;
	else if (error < 1)
		speed = 0;
		
    // Update error
    prev_error = error;

    //* Debug
    printf("Speed: %d\n", speed);
	printf("Ctrl: %d\n", ctrl);
    printf("Previous Error: %d\n", prev_error);    
	printf("Direction: %d\n\n", direction);
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
