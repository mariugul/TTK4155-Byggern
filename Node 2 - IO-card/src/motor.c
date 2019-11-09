#include "../inc/motor.h"


void motor_init()
{
    // ? PID INIT HERE

    // Start in the middle
    float start_pos = 127.5;
    motor_set_pos(start_pos);
}

void motor_set_pos(uint8_t pos)
{
    // ! Joystick_pos has to be ADC values (0-255)
    // ! and not percentage values (-100 to 100).

    // Joystick max and min values
    uint8_t max = 255;
    uint8_t min = 0;

    // Error check and set the joystick position value 
    if (joystick_pos > max)
        ;

    else if (joystick_pos < min)
        ;

    else
        ;
}