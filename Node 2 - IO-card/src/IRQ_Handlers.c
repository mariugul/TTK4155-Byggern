/*********************************************************
 *               Interrupt Handlers                      *
 *                                                       *
 *  These are the Interrupt Handlers for CAN Bus,        *
 *  motor/PID control and Solenoid. They also have a few *
 *  functions for updating "interrupt flags" that are our*
 *  own flags, used mainly for motor control.            *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Define the clock before delay library
//---------------------------------------------------
#define F_CPU 16000000UL

// Includes
//---------------------------------------------------
#include "../inc/ADC.h"
#include "../inc/CAN.h"
#include "../inc/GPIO_Defines.h"
#include "../inc/Main.h"
#include "../inc/Motor.h"
#include "../inc/PID_Simplified.h"
#include "../inc/Timers.h"
#include "../inc/USART.h"
#include "../inc/Servo.h"
#include "../inc/IRQ_Handlers.h"
#include <util/delay.h>



// Flags                                             
//---------------------------------------------------
bool motor_flag = false;


// Function Definitions                                       
//---------------------------------------------------
void IRQ_Set_Motor_Flag()
{
	motor_flag = true;
}

void IRQ_Clear_Motor_Flag()
{
	motor_flag = false;
}

bool IRQ_Motor_Flag()
{
	return motor_flag;
}

// Interrupt Handlers                                
//---------------------------------------------------

// NB!!! I think that we can maybe use a software timer instead of this function to generate
// a Solenoid pulse. What do you think Daniel?
// Solenoid Control - Timer0 Interrupt Handler
ISR(TIMER0_OVF_vect)
{
  printf("<Solenoid IRQH\n");
}

// Servo Control - Timer1 Interrupt Handler
ISR(TIMER1_OVF_vect){} // Not needed in fast PWM mode

// Motor/PID Control - Timer2 Interrupt Handler
ISR(TIMER2_OVF_vect)
{
	//printf("<Motor IRQH>\n");
	
    // Get the target position from joystick --> happens in CAN interrupt handler

    // Calculate the new speed and direction
    PID_Calc();
	
	// Set flag so the main loop can move motor.
    // The reason for this is that the DAC is controlled by
    // I2C, and this is run on interrupt. Calling Motor_Move 
    // here would result in nested interrupts.
	IRQ_Set_Motor_Flag(); 	
}

// CAN Message Receive - External Interrupt Handler
ISR(INT2_vect) // !PB0 is external interrupt pin
{
    printf("<CAN IRQH>\n");

    // Save the received message
    can_message receive = CAN_Receive();

    // Clear Interrupt Flag
    CAN_Clear_IF();

    // Decode the Interrupt Source of the MCP2515
    //irqf_decode_t irq_source = CAN_IRQ_Decode();  
	
	// Check for received data
    if (receive.id == JSTICK_CAN_ID) {

        // *Printf for debug
        printf("Received %d %d %d\n", receive.data[JSTICK_X], receive.data[JSTICK_Y], receive.data[JSTICK_BUT]);

        // Sets servo to received joystick position
        Servo_Set_Pos(receive.data[JSTICK_Y]);

        // Update the PID with Joystick position
        PID_Update_Target_Pos(receive.data[JSTICK_X]);

        // Solenoid shoot
        if (receive.data[PUSH_BUT_R] == PUSHED) {
            
            // Solenoid pulse
				Solenoid_Activate();
				_delay_ms(50);
				Solenoid_Deactivate();
            
            // Reset joystick push variable
            receive.data[PUSH_BUT_R] = NOT_PUSHED;
        }
    } else
        printf("<ERROR> No message was received <SOURCE> CAN IRQ Handler\n");
}