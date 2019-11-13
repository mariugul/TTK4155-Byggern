#include "../inc/ADC.h"
#include "../inc/CAN.h"
#include "../inc/GPIO_Defines.h"
#include "../inc/Main.h"
#include "../inc/Motor.h"
#include "../inc/PID.h"
#include "../inc/Timers.h"
#include "../inc/USART.h"
#include "../inc/Servo.h"
#include <avr/interrupt.h>
#include <avr/io.h>

// Solenoid Control - Timer0 Interrupt Handler
ISR(TIMER0_OVF_vect)
{
    printf("<Solenoid IRQH\n");
}

// Servo Control - Timer1 Interrupt Handler
//ISR(TIMER1_OVF_vect){} // Not needed in fast PWM mode

// Motor/PID Control - Timer2 Interrupt Handler
ISR(TIMER2_OVF_vect)
{
	printf("<Motor IRQH>\n");
	
    // Variables
    direction_t direction;
    uint8_t speed;

    // Get the target position from joystick --> happens in CAN interrupt handler

    // Calculate the new position
    speed = PID_Speed_Calc();
    direction = PID_Direction_Calc();

    // Update error for next calculation
    PID_Update_Last_Error();
	
	
    // Move the motor to updated value
    switch (direction) {
    case left:
        Motor_Move(left, speed);
        break;

    case right:
        Motor_Move(right, speed);
        break;

    case stop:
        Motor_Move(stop, speed);
        break;
    }
	
}

// CAN Message Receive - External Interrupt Handler
ISR(INT2_vect) // !PB0 is external interrupt pin
{
    printf("<CAN IRQH>\n");

    // Save the received message
    can_message receive = CAN_Receive();

    // Clear Interrupt Flag
    CAN_Clear_IF();

    // Decode the Interrupt Source
    //irqf_decode_t irq_source = CAN_IRQ_Decode(); //? May not be important (remove?)

    // Check for received data
    if (receive.id == JSTICK_CAN_ID) {

        // *Printf for debug
        printf("Received %d %d %d\n", receive.data[JSTICK_X], receive.data[JSTICK_Y], receive.data[JSTICK_BUT]);

        // Sets servo to received joystick position
        Servo_Set_Pos(receive.data[JSTICK_Y]);

        // TODO - Integrate this with PID IRQ Handler
        // Update the PID with Joystick position
        PID_Update_Pos(receive.data[JSTICK_X]);

        // TODO - Solenoid activate
        if (receive.data[JSTICK_BUT] == PUSHED) {
            // TODO - Start timer-interrupt

            // Reset joystick push variable
            receive.data[JSTICK_BUT] = NOT_PUSHED;
        }
    } else
        printf("<ERROR> No message was received <SOURCE> CAN IRQ Handler\n");
}