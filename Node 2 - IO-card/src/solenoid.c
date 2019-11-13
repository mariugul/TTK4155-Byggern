#include "../inc/Solenoid.h"
#include "../inc/GPIO_Defines.h"

// Variables
bool solenoid_pulse = false; // TODO Make extern


/***************/
/*  Functions  */
/***************/

void Solenoid_Init()
{
    printf("<Solenoid Initialized>\n");
    // Set pin for activating solenoid
    SET_PORT(SOL_REG, OUTPUT, SOL_PORT, SOL_PIN, LOW);
}

void Solenoid_Activate()
{
    // Activate solenoid
    SET_PIN(SOL_PORT, SOL_PIN);
}

void Solenoid_Deactivate()
{
	// Deactivate solenoid
	CLEAR_PIN(SOL_PORT, SOL_PIN);
}

// Calling this function twice creates a pulse
bool Solenoid_Pulse()
{
    static bool pulse = false;

    if(pulse == false){
        // Send HIGH to Solenoid
        Solenoid_Activate();
        pulse = true;
    }
    else {
        // Send LOW to Solenoid
        Solenoid_Deactivate();
        pulse = false;
    }

    return pulse;
}



