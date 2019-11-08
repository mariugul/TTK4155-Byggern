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
#include "inc/joystick_to_can.h"


int main()
{
    // Initialize
    gpio_init();
    xmem_init();
    uart_init();
    oled_init();
    menu_init();
    can_init(MODE_NORMAL);

    // Try to send a message
    can_message message = {0};
    message.id = 27;
    message.length = 5;
    message.data[0] = (uint8_t)'N';
    message.data[1] = (uint8_t)'o';
    message.data[2] = (uint8_t)'d';
    message.data[3] = (uint8_t)'e';
    message.data[4] = (uint8_t)'1';
    can_send(&message);

    const int can_stat = mcp_read(MCP_CANSTAT);
    printf("CAN status: %d\n", can_stat);

    // Main program loop
    while (1) {
        // Send joystick position to Node2 every 100ms
        _delay_ms(100);
        send_joystick_to_can();
        can_clear_errors();
        //can_send(&message);

    
        printf("CAN status: %d\n", mcp_read(MCP_CANSTAT));
        printf("CAN int flag: %d\n", mcp_read(MCP_CANINTF));
    }
}
