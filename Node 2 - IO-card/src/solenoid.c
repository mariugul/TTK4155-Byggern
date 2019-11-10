#include "../inc/Solenoid.h"
#include "../inc/GPIO_Defines.h"

// Variables
bool solenoid_pulse = false; // TODO Make extern


/***************/
/*  Functions  */
/***************/

void Solenoid_Init()
{
    // Set pin for activating solenoid
    SET_PORT(SOL_REG, OUTPUT, SOL_PORT, SOL_PIN, LOW);
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

void Solenoid_Activate()
{
    // Activate solenoid
    SET_PIN(SOL_PORT, SOL_PIN);
}

void Solenoid_Deactivate(uint8_t push)
{
    // Deactivate solenoid
    CLEAR_PIN(SOL_PORT, SOL_PIN);
}

/*********************/
/* Interrupt Handler */
/*********************/
void Solenoid_IRQ_Handler() // TODO - Make this a real Interrupt handler OR software timer run
{
    //This will run twice before stopping the timer
    if(Solenoid_Pulse() == false)
        ;// TODO - Timer stop

    // TODO - Clear interrupt flag
}


