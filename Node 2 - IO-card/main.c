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
#include "inc/PID_Simplified.h"
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


typedef enum {
    IDLE,
    INIT,
    RUNNING,
    GAME_OVER,
    OTHERS
} state_t;


void fsm()
{
    static state_t current_state = IDLE;
	const can_message node1 = CAN_Receive();

    if (current_state == IDLE) {
        printf("Node 2: IDLE state\n");
        // Disable stuff

        // Go to init state when Node1 sends init msg
		if (node1.id == NODE1_INIT_ID && node1.data[0] == 'I') {
            current_state = INIT;
        }
        _delay_ms(50); // Debug

    } else if (current_state == INIT) {
        printf("Node 2: INIT state\n");
        // TODO: Init motors and stuff

        // Send ready message back to Node1
        can_message msg = {
            .id = NODE2_READY_ID,
            .length = 1,
            .data[0] = 'R'
        };

        CAN_Send(&msg);
        _delay_ms(100);
        
        // Receive a start message
        if (node1.id == NODE1_START_ID && node1.data[0] == 'S') {
            current_state = RUNNING;
        }


    } else if (current_state == RUNNING) {
        printf("Node 2: RUNNING state\n");

        // Solenoid shoot
		if (node1.id == JSTICK_CAN_ID 
            && node1.data[PUSH_BUT_R] == PUSHED) {
				printf("Making a Solenoid Pulse!\n");
				Solenoid_Activate();
				_delay_ms(50);
				Solenoid_Deactivate();
        }

        // TODO: Implement read slider and PID control

        // Ball detection
        if (ADC_Ball_Detected()) { 
            printf("Ball detected! RIP!\n");
            current_state = GAME_OVER;
        }

    } else if (current_state == GAME_OVER) {
        printf("Node2 State: GAME_OVER\n");
        can_message msg = {
            .id = NODE2_GAME_OVER_ID,
            .length = 1,
            .data[0] = 'G'
        };

        for (int i = 0; i < 10; i++) {
            CAN_Send(&msg);
            _delay_ms(200);
        }

		//if (node1.id == NODE1_RESET_ID && node1.data[0] == 'Q') {
            current_state = IDLE;
        //}


    } else {
        printf("State: OTHERS\n");
        current_state = IDLE;
    }
}

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
        fsm();
    }
}

		
        /*
		// Save the received message
		const can_message receive = CAN_Receive();

		// Check for received data
		if (receive.id == JSTICK_CAN_ID) {
		    const int motor = Motor_Read();
		    //printf("Motor encoder: %d\n", motor);
			//printf("JX: %d JY: %d JB: %d SL: %d SR: %d BL: %d BR: %d\n", receive.data[JSTICK_X], receive.data[JSTICK_Y], receive.data[JSTICK_BUT], receive.data[SLIDER_L], receive.data[SLIDER_R], receive.data[PUSH_BUT_L], receive.data[PUSH_BUT_R]);

			//Servo_Set_Pos(receive.data[JSTICK_Y]);
			//PID_Update_Target_Pos(receive.data[SLIDER_R]);

			// Solenoid shoot
			if (receive.data[PUSH_BUT_R] == PUSHED) {
				printf("Making a Solenoid Pulse!\n");
				Solenoid_Activate();
				_delay_ms(50);
				Solenoid_Deactivate();
			}
		} else if (receive.id == NODE1_INIT_ID) {
            printf("Node 2: INIT state\n");
            // Send init message
            can_message msg = {
                .id = NODE2_READY_ID,
                .length = 1,
                .data[0] = 'R'
            };
            CAN_Send(&msg);

		} else if (receive.id == NODE1_QUIT_ID) {
            printf("Node 2 state: QUIT\n");
        }

        // Check if ball fell out
        if (ADC_Ball_Detected()) { 
            printf("RIP! Ball detected!\n");
            // Send init message
            can_message msg = {
                .id = NODE2_GAME_OVER_ID,
                .length = 1,
                .data[0] = 'G'
            };
            CAN_Send(&msg);
        }

        // Move motor when flag is set
        if (IRQ_Motor_Flag()) {
					
            // Move the motor to updated value
            //Motor_Move(PID_Get_Direction(), PID_Get_Speed());

            // Clear the Motor flag
            IRQ_Clear_Motor_Flag();
        }
		
		// Delay for debug
		_delay_ms(100);
    }
        */