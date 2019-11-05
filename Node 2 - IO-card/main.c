/* NODE 2 - ATMEGA 2560 */

#include "inc/can.h"
#include "inc/servo.h"
#include "inc/usart.h"
#include "inc/mcp_defines.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The ID for receiving joystick data
#define JSTICK_CAN_ID 10

int main()
{
    // Initializers
    usart_init();
	can_init(MODE_NORMAL);
    servo_init();

    // Loop
    while (true) {
        // Poll joystick-data from Node 1
        can_message receive = can_receive();

        // Check for received data
        if (receive.id == JSTICK_CAN_ID) {
            // Sets servo to received joystick position
			printf("Received %d %d %d\n", receive.data[0], receive.data[1], receive.data[2]);
            servo_set_pos(receive.data[0]);

            // Sets motor to received joystick position
            //motor_set_pos(receive.data[1]);
        }
    }
}