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

void xmem_init(void)
{
	MCUCR =  (1 << SRE);	     	  // Activate external memory
	SFIOR =  (1 << XMM2);			  // Mask JTAG pins
}

void sram_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,
			retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed); // reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",
			i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", 
			write_errors, retrieval_errors);
}

void led_init()
{
	DDRB  |= (1 << PB0); // Port B0 is an output
	PORTB |= (1 << PB0); // Port B0 is HIGH: Turn on LED
}

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

