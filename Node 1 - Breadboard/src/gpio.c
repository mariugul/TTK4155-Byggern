#include "../inc/gpio.h"
#include "../inc/gpio_defines.h"

/** Set up gpio pins */
void gpio_init()
{
    SET_PORT(DDRB, OUTPUT, PORTB, PIN_LED, HIGH); // Turn status LED on
    SET_PORT(DDRB, INPUT, PORTB, PIN_LBUT, LOW); // Set left button to input
    SET_PORT(DDRB, INPUT, PORTB, PIN_RBUT, LOW); // Set right button to input
    SET_PORT(DDRB, INPUT, PORTB, PIN_RBUT, LOW); // Set joystick button to input
    SET_PORT(DDRB, OUTPUT, PORTB, PIN_MCP_CS, HIGH); // Set joystick button to input
}

/** Read button values */
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
