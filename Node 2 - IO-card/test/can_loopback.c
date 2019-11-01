#include <avr/io.h> // AVR library for IO
#include <stdio.h> // Standard library
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include "inc/can.h"
#include "inc/mcp_defines.h"
#include "inc/usart.h"


int main()
{
    // Initializers
	usart_init();
    can_init(); // Try to send a message

    can_message message = {0};
    message.id = 69;
    message.length = 5;
    message.data[0] = (uint8_t)'N';
    message.data[1] = (uint8_t)'o';
    message.data[2] = (uint8_t)'d';
    message.data[3] = (uint8_t)'e';
    message.data[4] = (uint8_t)'2';
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