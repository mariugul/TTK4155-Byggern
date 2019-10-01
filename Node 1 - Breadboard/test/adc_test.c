/*
 * ADC
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 */

#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include <stdlib.h>
#include "uart.h"
#include "adc.h"
#include "xmem.h"
#include "led.h"
#include "sram.h"


void buttons_init()
{
	int mask = 0b11100111;
	DDRD    &= mask;			// PD4 and PD5 are inputs
	
	// want this: 11100111
	// got this:  11111111
}


int main(void)
{
	
	// Initialize
	led_init();
	buttons_init();
	xmem_init();
	uart_init();
		
	
    // Main program loop
    while (1) 
	{
		int but1, but2;
		but1 = PIND & ~0b11110111;
		but2 = PIND & ~0b11111011;
		pos_t pos = pos_read();
		
		enum direction x = j_pos(pos.joy_x, pos.joy_y);
		char dir;
		switch (x)
		{
			case 1: dir = 'L'; break;
			case 2: dir = 'R'; break;
			case 3: dir = 'U'; break;
			case 4: dir = 'D'; break;
			default: dir = 'N'; break;
		}
		
		printf("JX: %d%%,    JY: %d%%,    SL: %d%%,    SR: %d%%    ,Dir: %d    but1: %d,    but2: %d\n", pos.joy_x, pos.joy_y, pos.slider_l, pos.slider_r, x, but1, but2);
		
		//printf("But1: %d     But2: %d\n", but1, but2);
	}
}

