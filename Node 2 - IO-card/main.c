/*********************************************************
 *             NODE 2 - Ping Pong Game                   *
 *     This is the main file for controlling Node 2.     *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "inc/Main.h"
#include "inc/ADC.h"
#include "inc/CAN.h"
#include "inc/GPIO_Defines.h"
#include "inc/IRQ_Handlers.h"
#include "inc/MCP_Defines.h"
#include "inc/Motor.h"
#include "inc/PID.h"
#include "inc/Servo.h"
#include "inc/Solenoid.h"
#include "inc/Timers.h"
#include "inc/USART.h"
#include "inc/DAC.h"
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
    USART_Init();
    ADC_Init();
    Servo_Init();
    Motor_Init();
    PID_Init();
    Solenoid_Init();
    CAN_Init(MODE_NORMAL);
    Timers_Init();

    printf("\n****Finished setting up Atmega2560!****\n\n");

    // Loop
    //-----------------------------------------------
    while (true) {
		

		// Save the received message
		can_message receive = CAN_Receive();

		// Check for received data
		if (receive.id == JSTICK_CAN_ID) {

			// *Printf for debug
			printf("Received %d %d %d\n", receive.data[JSTICK_X], receive.data[JSTICK_Y], receive.data[JSTICK_BUT]);

			// Sets servo to received joystick position
			Servo_Set_Pos(receive.data[JSTICK_Y]);

			// TODO - Solenoid activate
			if (receive.data[JSTICK_BUT] == PUSHED) {
				printf("Making a Solenoid Pulse!\n");
				
				// Solenoid pulse
				Solenoid_Activate();
				_delay_ms(50);
				Solenoid_Deactivate();
				
				// Reset joystick push variable
				receive.data[JSTICK_BUT] = NOT_PUSHED;
			}
		} 
		
		// Move motor TEST
		Motor_Move(right, 0);

        // Check if ball fell out
        if (ADC_Ball_Detected()) {
            printf("RIP! Ball detected!\n");
        }

        // Move motor when flag is set
        if (IRQ_Motor_Flag()) {

            // Move the motor to updated value
            Motor_Move(PID_Get_Direction(), PID_Get_Speed());

            // Clear the Motor flag
            IRQ_Clear_Motor_Flag();
        }
    }
}