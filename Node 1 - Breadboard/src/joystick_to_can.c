
#include "../inc/joystick.h"
#include "../inc/adc.h"
#include "../inc/gpio.h"
#include "../inc/can.h"
#include "../inc/joystick_to_can.h"

void send_joystick_to_can()
{
    can_message msg = {
        .id = 10,
        .length = 7,
        .data[0] = ADC_Read(JOY_X), // Joystick X direction
        .data[1] = ADC_Read(JOY_Y), // Joystick Y direction
        .data[2] = !gpio_read_button(jstick), // Joystick push button
        .data[3] = ADC_Read(SLIDER_L), // Slider left
        .data[4] = ADC_Read(SLIDER_R), // Slider right
        .data[5] = gpio_read_button(push_l),// Push button left
        .data[6] = gpio_read_button(push_r)// Push button right
    };
    can_send(&msg);
}