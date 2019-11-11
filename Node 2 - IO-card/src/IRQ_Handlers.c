#include "../inc/PID.h"
#include "../inc/Motor.h"
#include "../inc/Timers.h"
#include "../inc/CAN.h"
#include "../inc/ADC.h"
#include "../inc/GPIO_Defines.h"
#include <avr/io.h>


// Solenoid Control - Timer0 Interrupt Handler
ISR(TIMER0_OVF_vect)
{

}

// Servo Control - Timer1 Interrupt Handler
ISR(TIMER1_OVF_vect){} // Not needed in fast PWM mode

// Motor/PID Control - Timer2 Interrupt Handler
ISR(TIMER2_OVF_vect)
{
    PID_Ctrl_Var_calc();
    PID_Speed_calc();
    
    // If control variable negative, run counter clockwise
    if (ctrl < 0){
        if (ctrl )
        speed = -ctrl;
    }

    // If control variable posititve, run clockwise
    else if (ctrl > 0)
        Motor_Move();

    // If control variable zero, stop motor
    else 
        Motor_Move();
    
}

// CAN Message Receive - External Interrupt Handler
ISR(INT2_vect)// !PB0 is external interrupt pin
{   
    // Save the received message
    can_message message = CAN_Receive();
    
    // Clear Interrupt Flag
    CAN_Clear_IF();

    // Decode the Interrupt Source
    irq_decode_t irq_source = CAN_IRQ_Decode(); //? May not be important (remove?)

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
    }
    else 
        printf("<ERROR> No message was received <SOURCE> CAN IRQ Handler\n")
    
}