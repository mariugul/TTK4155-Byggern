/* NODE 2 - ATMEGA 2560 */

#include "inc/can.h"
#include "inc/servo.h"
#include "inc/usart.h"
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
    servo_init();
    
    bool joystick_receive = false;

    // Loop
    while (true) {
        // Poll joystick-data from Node 1
        can_message receive = can_receive();

        // Check for received data
        if(receive.id == JSTICK_CAN_ID)
        {
            // Sets servo to received joystick position
            servo_set_pos(receive.data[0]);

            // Sets motor to received joystick position
          //motor_set_pos(receive.data[1]);
        }
    }

}