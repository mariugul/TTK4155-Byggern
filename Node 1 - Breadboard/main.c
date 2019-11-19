/*********************************************************
 *             NODE 1 - Ping Pong Game                   *
 *     This is the main file for controlling Node 2.     *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "inc/adc.h"
#include "inc/can.h"
#include "inc/gpio.h"
#include "inc/joystick.h"
#include "inc/joystick_to_can.h"
#include "inc/mcp_defines.h"
#include "inc/menu.h"
#include "inc/uart.h"
#include "inc/xmem.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

// Main
//---------------------------------------------------
int main()
{
    // Initializers
    gpio_init();
    xmem_init();
    uart_init();
    oled_init();
    menu_init();
    can_init(MODE_NORMAL);

    // CAN status
    const int can_stat = mcp_read(MCP_CANSTAT);
    printf("CAN status: %d\n", can_stat);

    // Loop
    //-----------------------------------------------
    while (true) {

        // Send joystick position to Node2 every 100ms
        _delay_ms(100);
        send_joystick_to_can();
        can_clear_errors();

        printf("CAN status: %d\n", mcp_read(MCP_CANSTAT));
        printf("CAN int flag: %d\n", mcp_read(MCP_CANINTF));
    }
}
