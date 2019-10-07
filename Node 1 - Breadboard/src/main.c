/*
 * OLED
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 */

#include <util/delay.h>
#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include <stdlib.h>
#include <stdbool.h>
#include "uart.h"
#include "adc.h"
#include "oled.h"
#include "menu.h"
#include "xmem.h"
#include "gpio.h"

//unsigned char A [8] = {0b01111100,0b01111110,0b00010011,0b00010011,0b01111110,0b01111100,0b00000000,0b00000000};    // A


int main(void)
{
	
	// Initialize
    gpio_init();
	xmem_init();
	uart_init();
	oled_init();
	menu_init();
	//menu_print();
    
	
	/*
	menu_print();
    menu_highlight(PLAY);

    for (int i = 0; i < 5; i++) {
        _delay_ms(1000);
        menu_highlight_handler(DOWN);
    }

    for (int i = 0; i < 5; i++) {
        _delay_ms(1000);
        menu_highlight_handler(UP);
    }
    
    const int fake_button_pressed = 1;
    if (fake_button_pressed) {
        const menu_state current_state = menu_highlight_handler(NOTHING);
        menu_selection(current_state);
    }
	*/

    // Main program loop
    while (1) 
	{	
		 
		 printf("B1: %d,   B2: %d   B3: %d\n", gpio_read_button(1), gpio_read_button(2), gpio_read_button(3));
		
        
        /*
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
		*/
    }
}

