/*
 * OLED
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 */

#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include <stdlib.h>
#include "uart.h"
#include "adc.h"
#include "oled.h"
#include "oled_menu.h"
#include "led.h"
#include "xmem.h"



void buttons_init()
{
	int mask = 0b11100111;
	DDRD    &= mask;			// PD4 and PD5 are inputs
	
	// want this: 11100111
	// got this:  11111111
}

//unsigned char A [8] = {0b01111100,0b01111110,0b00010011,0b00010011,0b01111110,0b01111100,0b00000000,0b00000000};    // A


int main(void)
{
	
	// Initialize
	led_init();
	xmem_init();
	uart_init();
	oled_init();
	//oled_menu_init();
		
	// Write to OLED	
	
	oled_print("Home");
	
	oled_goto_line(2);
	oled_print("Play");
	
	oled_goto_line(4);
	oled_print("Highscore");
	
	oled_goto_line(6);	
	oled_print_inv("About");
	
	
    // Main program loop
    while (1) 
	{

	}
}

