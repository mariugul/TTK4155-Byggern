/*
 * OLED
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 *          Daniel Rahme
 */

#include <util/delay.h>
#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include <stdlib.h>
#include "inc/uart.h"
#include "inc/adc.h"
#include "inc/xmem.h"
#include "inc/gpio.h"
#include "inc/joystick.h"
#include "inc/menu.h"
#include "inc/spi.h"
#include "inc/mcp2515.h"
#include "inc/can.h"

int main()
{
	// Initialize
    gpio_init();
	xmem_init();
	uart_init();
	oled_init();
	menu_init();
	spi_init();
	mcp_init();     // Relies on spi_init() to be initialized first
	can_init();     // Relies on mcp_init() to be initialized first
    

    // Main program loop
    while (1) 
	{	
		printf("hei");
		printf("B1: %d,   B2: %d   B3: %d\n", gpio_read_button(1), gpio_read_button(2), gpio_read_button(3));
		
    }
}

