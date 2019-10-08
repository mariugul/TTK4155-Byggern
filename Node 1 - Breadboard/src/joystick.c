#include "joystick.h"
#include "adc.h"

int pos_to_percent(int pos)
{
    return (float)pos / 128 * 100 - 100;
}

direction_t joystick_read()
{
    const int threshold = 10; // the tolerable difference from 0
    const int angle = 50; // the sideways angle

    const int joy_x = pos_to_percent(adc_read(JOY_X));
    const int joy_y = pos_to_percent(adc_read(JOY_Y));

    // left
    if (joy_x < -threshold && joy_y > joy_x && joy_y < -joy_x)
        return LEFT;

    // right
    else if (joy_x > threshold && joy_y < joy_x && joy_y > -joy_x)
        return RIGHT;

    // down
    else if (joy_y < -threshold && joy_x < -joy_y && joy_x > joy_y)
        return DOWN;

    // up
    else if (joy_y > threshold && joy_x < joy_y && joy_x > -joy_y)
        return UP;

    else
        return NEUTRAL;
}


joy_t get_joystick()
{
    return (joy_t){
        .direction = joystick_read(), // change with read function
        .button_pressed = !gpio_read_button(3)
    };
}