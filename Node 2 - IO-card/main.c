/* NODE 2 - ATMEGA 2560 */

#include "inc/Adc.h"
#include "inc/CAN.h"
#include "inc/MCP_Defines.h"
#include "inc/Motor.h"
#include "inc/Servo.h"
#include "inc/Solenoid.h"
#include "inc/USART.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "inc/GPIO_Defines.h"

// The ID for receiving joystick data
#define JSTICK_CAN_ID 10
// Joystick value index in array
#define JSTICK_X   0
#define JSTICK_Y   1
#define JSTICK_BUT 2
#define PUSHED HIGH

// Global variables 
bool jstick_pushed = false;

int main()
{
    // Initializers
    USART_Init();
    CAN_Init(MODE_NORMAL);
    Servo_Init();
    Motor_Init();
    ADC_Init();

    // Loop
    while (true) {

        // Read IR diode value
        const uint16_t ir_diode = ADC_Read();

        // Print IR value to PC for Debug
        printf("ADC: %d\n", ir_diode);

        // Check for received data
        if (receive.id == JSTICK_CAN_ID) {

            // Sets servo to received joystick position
            printf("Received %d %d %d\n", receive.data[JSTICK_X], receive.data[JSTICK_Y], receive.data[JSTICK_BUT]);
            Servo_Set_Pos(receive.data[JSTICK_Y]);

            // Sets motor to received joystick position
            Motor_Set_Pos(receive.data[JSTICK_X]);

            // Shoots the ball with solenoid
            if(JSTICK_BUT == PUSHED){
                // TODO - Start timer-interrupt
            }

            // Delay for debugging
            _delay_ms(200);
        }

        // Check if ball fell out
        if (Ball_Detected()) {
            printf("RIP! Ball detected!\n");
        }
    }