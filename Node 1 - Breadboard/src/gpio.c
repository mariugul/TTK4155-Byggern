/*********************************************************
 *                         GPIO                          *
 *                                                       *
 *  These are the functions for setting up GPIO and      *
 *  reading the buttons.                                 *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/gpio.h"
#include "../inc/gpio_defines.h"

// Function Definitions
//---------------------------------------------------

void gpio_init()
{
    SET_PORT(DDRB, OUTPUT, PORTB, PIN_LED, HIGH); // Turn status LED on
    SET_PORT(DDRB, INPUT, PORTB, PIN_LBUT, LOW); // Set left button to input
    SET_PORT(DDRB, INPUT, PORTB, PIN_RBUT, LOW); // Set right button to input
    SET_PORT(DDRB, INPUT, PORTB, PIN_RBUT, LOW); // Set joystick button to input
    SET_PORT(DDRB, OUTPUT, PORTB, PIN_MCP_CS, HIGH); // Set joystick button to input
}

bool gpio_read_button(button_t button)
{
    bool read_button = 0;

    if (button == push_l)
        read_button = (1 << PB1) & PINB;

    else if (button == push_r)
        read_button = (1 << PB2) & PINB;

    else if (button == jstick)
        read_button = (1 << PB3) & PINB;

    return read_button;
}
