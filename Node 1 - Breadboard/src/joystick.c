/* * joystick.c
 *
 *  Created: 08.10.2019
 *  Author: Daniel Rahme
 */
#include "joystick.h"
#include "adc.h"
#include "gpio.h"

int pos_to_percent(int pos)
{
    return (float)pos / 128 * 100 - 100;
}

joy_t joystick_read_direction()
{
    const int threshold = 97; // the tolerable difference from 0

    const int joy_x = pos_to_percent(adc_read(JOY_X));
    const int joy_y = pos_to_percent(adc_read(JOY_Y));

    joy_t pos = { 0 };

    if (joy_x >= threshold)         pos.dir_x = RIGHT;
    else if (joy_x <= -threshold)   pos.dir_x = LEFT;
    else                            pos.dir_x = NEUTRAL;

    if (joy_y >= threshold)         pos.dir_y = UP;
    else if (joy_y <= -threshold)   pos.dir_y = DOWN;
    else                            pos.dir_y = NEUTRAL;

    return pos;
}

joy_t get_joystick()
{
    joy_t joy = joystick_read_direction();
    joy.button_pressed = !gpio_read_button(3);
    return joy;
}