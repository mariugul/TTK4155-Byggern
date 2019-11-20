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
#include "inc/pid.h"
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
	Solenoid_Init();
	CAN_Init(MODE_NORMAL);
    Servo_Init();
    Timers_Init();
    Motor_Init(); // Motor needs to be after Timers_Init
	
    printf("\n****Finished setting up Atmega2560!****\n\n");
	
    // Development of PID - regulator
    //PID_Update_Target_Pos(120);
    //PID_Calc();

    // Loop
    //-----------------------------------------------
    while (true) {
        // run the Finite State Machine
        fsm();

        // Calibrate the IR diode
        //printf("IR: %d", ADC_Read());

        

    }
}



// Finite State Machine
void fsm()
{
    static state_t current_state = IDLE;
	const can_message node1 = CAN_Receive();
	
    //--------------------------//
    //---------- IDLE ----------//
    //--------------------------//
    if (current_state == IDLE) {
        printf("Node 2: IDLE state\n");
        // Disable stuff
		
        // Go to init state when Node1 sends init msg
		if (node1.id == NODE1_INIT_ID && node1.data[0] == 'I') {
            current_state = INIT;
        }
        _delay_ms(50); // Debug

    //--------------------------//
    //---------- INIT ----------//
    //--------------------------//
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


    //-----------------------------//
    //---------- RUNNING ----------//
    //-----------------------------//
    } else if (current_state == RUNNING) {
        printf("Node 2: RUNNING state\n");

        // Joystick and sliders
		if (node1.id == JSTICK_CAN_ID) {
			// Move servo
            Servo_Set_Pos(node1.data[JSTICK_X]);
			
			// Poll if motor values are updated
			if(IRQ_Motor_Flag()){
				// Get direction and speed
				uint8_t speed = PID_Get_Speed();
				direction_t dir = PID_Get_Direction();
				
				// Move motor and clear flag
				Motor_Move(dir, speed);
				IRQ_Clear_Motor_Flag();
			}

            // Solenoid shoot
            if (node1.data[PUSH_BUT_R] == PUSHED) {
				printf("Making a Solenoid Pulse!\n");
				Solenoid_Activate();
				_delay_ms(50);
				Solenoid_Deactivate();
            }
        }

        // TODO: Implement read slider and PID control

        // Ball detection
        if (ADC_Ball_Detected()) { 
            printf("Ball detected! RIP!\n");
            current_state = GAME_OVER;
        }


    //-------------------------------//
    //---------- GAME OVER ----------//
    //-------------------------------//
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


    //-------------------------------//
    //---------- OTHERS -------------//
    //-------------------------------//
    } else {
        printf("State: OTHERS\n");
        current_state = IDLE;
    }
}