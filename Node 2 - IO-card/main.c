/* NODE 2 - ATMEGA 2560 */

#include "inc/can.h"
#include "inc/adc.h"
#include "inc/servo.h"
#include "inc/usart.h"
#include "inc/mcp_defines.h"
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
	//can_init(MODE_NORMAL);
    //servo_init();
    adc_init();

    // Loop
    while (true) {
        const uint16_t ir_diode = adc_read();
        printf("ADC: %d\n", ir_diode);

        if (ball_detected()) {
            printf("RIP! Ball detected!\n");
        }

        _delay_ms(200);
    }
}