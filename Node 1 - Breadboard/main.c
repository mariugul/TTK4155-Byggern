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
    can_message message = {0};
    message.id = 27;
    message.length = 4;
    message.data[0] = (uint8_t)'J';
    message.data[1] = (uint8_t)'A';
    message.data[2] = (uint8_t)'A';
    message.data[3] = (uint8_t)'A';
    can_send(&message);

    const int can_stat = mcp_read(MCP_CANSTAT);
    printf("CAN status: %d\n", can_stat);

    // Main program loop
    while (1) {
        const can_message rx = can_receive();
        if (rx.length > 0) {
            printf("--- ID: %d\tLength: %d ---\n", rx.id, rx.length);
            printf("Message: ");
            for (int i = 0; i < rx.length; i++) {
                printf("%c", rx.data[i]);
            }
            printf("\n\n");
        }
		const int can_flag = mcp_read(MCP_CANINTF);
        _delay_ms(1000);
        can_send(&message);
    }
}
