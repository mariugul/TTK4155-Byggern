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
    message.length = 1;
    message.data[0] = (uint8_t)'U';
    
	

    // Main program loop
    while (1) {
        //can_send(&message);
        //_delay_ms(100);
        //printf("CAN receive: %c\n", can_receive(3));
    }
}
