/*********************************************************
 *             Send joystick values to CAN               *
 *                                                       *
 *  This sends the joystick values to Node 2 over CAN.   *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/joystick_to_can.h"
#include "../inc/adc.h"
#include "../inc/can.h"
#include "../inc/gpio.h"
#include "../inc/joystick.h"


// Function Definitions
//---------------------------------------------------

void send_joystick_to_can()
{
    can_message msg = {
        .id = 10,
        .length = 7,
        .data[0] = adc_read(JOY_X), // Joystick X direction
        .data[1] = adc_read(JOY_Y), // Joystick Y direction
        .data[2] = !gpio_read_button(jstick), // Joystick push button
        .data[3] = adc_read(SLIDER_L), // Slider left
        .data[4] = adc_read(SLIDER_R), // Slider right
        .data[5] = gpio_read_button(push_l), // Push button left
        .data[6] = gpio_read_button(push_r) // Push button right
    };
    can_send(&msg);
}