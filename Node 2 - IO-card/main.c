/* NODE 2 - ATMEGA 2560 */

#include "inc/can.h"
#include "inc/mcp_defines.h"
#include "inc/motor.h"
#include "inc/adc.h"
#include "inc/servo.h"
#include "inc/usart.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>

// The ID for receiving joystick data
#define JSTICK_CAN_ID 10

int main()
{
    // Initializers
    usart_init();
    can_init(MODE_NORMAL);
    servo_init();
    motor_init();
    adc_init();

    // Loop
    while (true) {
        const uint16_t ir_diode = adc_read();
        printf("ADC: %d\n", ir_diode);

        // Check for received data
        if (receive.id == JSTICK_CAN_ID) {

            // Sets servo to received joystick position
            printf("Received %d %d %d\n", receive.data[0], receive.data[1], receive.data[2]);
            servo_set_pos(receive.data[0]);

            // Sets motor to received joystick position
            motor_set_pos(receive.data[1]);
        if (ball_detected()) {
            printf("RIP! Ball detected!\n");
        }

        _delay_ms(200);
    }
}