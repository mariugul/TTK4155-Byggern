#include "../inc/servo.h"
#include "../inc/pwm.h"

#define PERIOD 0.02 // 20ms period for PWM

// Initialize servo
void servo_init()
{
    // Start in the middle
    float start_pos = 0.0015;

    // Initialize servo
    pwm_init(PERIOD, start_pos);
}

// Returns servo position from joystick values (pulse width in seconds)
void servo_set_pos(float joystick_pos)
{
    /* 
     * NB! Joystick_pos has to be ADC values (0-255) 
     * and not percentage values (-100 to 100).
     */
    
    // Joystick max and min values
    uint8_t max = 255;
    uint8_t min = 0;

    // Error check the joystick position value
    if (joystick_pos > max)
        pwm_set_pulse_width(max);

    else if(joystick_pos < min)
        pwm_set_pulse_width(min);

    else
        pwm_set_pulse_width(joystick_pos);
}
