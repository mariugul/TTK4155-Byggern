/*
 * SRAM_test
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 */

#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include <stdlib.h>
#include "uart.h"
#include "xmem.h"
#include "led.h"
#include "sram.h"



int main(void)
{
    // Initialize
    led_init();
    xmem_init();
	uart_init();

    // Run test
	sram_test();
	
    // Main program loop
    while (1) 
	{
		// main body
    }
}
