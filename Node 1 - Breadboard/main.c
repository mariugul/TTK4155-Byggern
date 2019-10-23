/*
 * MAIN
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 *          Daniel Rahme
 */

#include "inc/adc.h"
#include "inc/can.h"
#include "inc/gpio.h"
#include "inc/joystick.h"
#include "inc/mcp_defines.h"
#include "inc/menu.h"
#include "inc/uart.h"
#include "inc/xmem.h"
#include <avr/io.h> // AVR library for IO
#include <stdio.h> // Standard library
#include <stdlib.h>
#include <util/delay.h>
#include <stdbool.h>


int main()
{
    // Initialize
    gpio_init();
    xmem_init();
    uart_init();
    oled_init();
    menu_init();
    can_init();

    // Try to send a message
    can_message message;
    message.id = 3;
    message.length = 2;
    message.data[0] = 'U';
    message.data[1] = 'X';

    // Main program loop
    while (true) {
        // Send message
        can_send(&message);

        // Received message
        const can_message can_msg = can_receive();

        // Print received message
        if (can_msg.length > 0) {
            printf("--- Message Received ---\n");
            printf("ID: %d   -   Length: %d\n", can_msg.id, can_msg.length);
            for (int i = 0; i < can_msg.length; i++) {
                printf("D%d: %c\n", i, can_msg.data[i]);
            }
            printf("\n");
        }

        _delay_ms(500); 
    }
}
