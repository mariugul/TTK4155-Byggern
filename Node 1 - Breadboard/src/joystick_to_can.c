
#include "../inc/joystick.h"
#include "../inc/adc.h"
#include "../inc/gpio.h"
#include "../inc/can.h"
#include "../inc/joystick_to_can.h"

void send_joystick_to_can()
{
    can_message msg = {
        .id = 10,
        .length = 3,
        .data[0] = adc_read(JOY_X), // X
        .data[1] = adc_read(JOY_Y), // Y
        .data[2] = !gpio_read_button(3) // Button
    };
    can_send(&msg);
}