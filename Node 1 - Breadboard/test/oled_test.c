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
#include "uart.h"
#include "adc.h"
#include "oled.h"
#include "oled_menu.h"
#include "led.h"
#include "xmem.h"
#include "gpio.h"
#include "menu.h"

//unsigned char A [8] = {0b01111100,0b01111110,0b00010011,0b00010011,0b01111110,0b01111100,0b00000000,0b00000000};    // A


int main(void)
{
	
	// Initialize
	led_init();
    gpio_init();
	xmem_init();
	uart_init();
	oled_init();
	//oled_menu_init();
    DDRB  &= ~(1 << PB3);              // Port B3 is an input
    int read_pin = PORTB & (1 << 3);              // Port B0 is HIGH: Turn on LED
		
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
        do_menu_selection(current_state);
    }

    // Main program loop
    while (1) 
	{
        // TODO: Read joystick pos

        // Button press not working
        volatile const int button_press = PORTB & (1 << 3); // Port B0 is HIGH: Turn on LED
        if (button_press) {
            const menu_state current_state = menu_highlight_handler(NOTHING);
            do_menu_selection(current_state);
        }
    }
}

