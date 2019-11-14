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

        // Read IR diode value
        const uint16_t ir_diode = ADC_Read();
        printf("ADC: %d\n", ir_diode);

        // Check if ball fell out
        if (Ball_Detected()) {
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