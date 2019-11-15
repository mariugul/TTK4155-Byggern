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


    const int can_stat = mcp_read(MCP_CANSTAT);
    printf("CAN status: %d\n", can_stat);

    // Main program loop
    while (1) {
        // Send joystick position to Node2 every 100ms
        _delay_ms(100);
        send_joystick_to_can();
        can_clear_errors();
    
        printf("CAN status: %d\n", mcp_read(MCP_CANSTAT));
        printf("CAN int flag: %d\n", mcp_read(MCP_CANINTF));
    }
}
