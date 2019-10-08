#include "gpio.h"


void gpio_init()                                        /** Initialize gpio pins */
{
    DDRB  |= (1 << PB0);                                // Port B0 is an output
    DDRB  &= ~(0 << PB1) | (0 << PB2) | (0 << PB3);		// Set Port B1, B2, B3 to input
    PORTB |= (1 << PB0);                                // Port B0 is HIGH: Turn on status LED		
}

bool gpio_read_button(uint8_t button)                   /** Read button values */
{
    bool read_button;

    if (button == 1)
	    read_button = (1 << PB1) & PINB;

    else if (button == 2)
	    read_button = (1 << PB2) & PINB;

    else if (button == 3)
	    read_button = (1 << PB3) & PINB;
    else
        return 0;
        
	return read_button;
}