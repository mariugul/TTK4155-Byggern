#include "gpio.h"


void gpio_init()                // Initialize gpio pins
{
	DDRB  &= ~(0 << PB1) | (0 << PB2) | (0 << PB3);		// Set Port B 1,2,3 to input
		
}

bool gpio_read_button(uint8_t button)
{
	bool read_but1 = 
	
	return (1 << PB3) & PINB;
}



