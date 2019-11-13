/* NODE 2 - ATMEGA 2560 */

#define F_CPU 16000000UL

#include "inc/Main.h"
#include "inc/ADC.h"
#include "inc/CAN.h"
#include "inc/GPIO_Defines.h"
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
    while (true) {
		Global_Interrupt_Enable();

        // Read IR diode value
        const uint16_t ir_diode = ADC_Read();

        // Print IR value to PC for Debug
        printf("ADC: %d\n", ir_diode);

        // Delay for debugging
        _delay_ms(200);

        // TODO - Implement ADC Interrupt for IR diode
        // Check if ball fell out
        if (Ball_Detected()) {
            printf("RIP! Ball detected!\n");
        }
    }
}