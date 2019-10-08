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
#include "uart.h"
//#include "adc.h"
#include "xmem.h"
#include "gpio.h"
#include "spi.h"
#include "joystick.h"
#include "menu.h"


int main(void)
{
	// Initialize
    gpio_init();
	xmem_init();
	uart_init();
	oled_init();
	menu_init();
	//menu_print();
	spi_init();
    
	
    // Main program loop
    while (1) 
	{	
		 
		printf("B1: %d,   B2: %d   B3: %d\n", gpio_read_button(1), gpio_read_button(2), gpio_read_button(3));
		
    }
}

