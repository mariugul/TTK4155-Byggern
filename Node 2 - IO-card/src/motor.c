/*********************************************************
 *                   Motor Controller                    *
 *                                                       *
 * This is the controller for the motor. It will control *
 * the arm moving in left and right direction. The motor *
 * controller has to be viewed in accordance with the PID*
 * -controller as they work together.                    *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Definition of clock (has to come before delay library)
//---------------------------------------------------
#define F_CPU 16000000UL

// Includes
//---------------------------------------------------
#include "../inc/Motor.h"
#include "../inc/DAC.h"
#include <util/delay.h>

// Funtion Definitions
//---------------------------------------------------
void Motor_Init()
{
    printf("<Motor Initialized>\n");
	
	// Set up DAC with I2C
    DAC_Init();
    
	// Set ports to output
    SET_OUTPUT(MJ1_REG, MJ1_DIR);
    SET_OUTPUT(MJ1_REG, MJ1_OE);
    SET_OUTPUT(MJ1_REG, MJ1_SEL);
    SET_OUTPUT(MJ1_REG, MJ1_RST);
    SET_OUTPUT(MJ1_REG, MJ1_DIR);

    SET_PIN(MJ1, MJ1_DIR);
    SET_PIN(MJ1, MJ1_RST);
    SET_PIN(MJ1, MJ1_OE);
    // Set ports to input
    DDRK = 0;
}

void Motor_Move(direction_t dir, uint8_t speed)
{
	
    // Set direction of the motor
    switch (dir) {
        case left:  Motor_Set_Dir(left);  break;

        case right: Motor_Set_Dir(right); break;

        case stop:  Motor_Set_Dir(stop);  break;
    }
 
    // Set speed
    Motor_Set_Speed(speed);
}

int16_t Motor_Read()
{
    // Set nRST to high  
    SET_PIN(MJ1, MJ1_RST);
    // Set !OE low to enable output of encoder
    CLEAR_PIN(MJ1, MJ1_OE);

    // Set SEL low to get high byte
    CLEAR_PIN(MJ1, MJ1_SEL);

    // Wait about 20 microseconds
    _delay_us(50);

    // Read upper 8-bits
    uint8_t msb = MJ2_DOUT;
	//printf("msb: %d\n", msb);

    // Set SEL high to get low byte
    SET_PIN(MJ1, MJ1_SEL);

    // Wait about 20 microseconds
    _delay_us(50);

    // Read lower 8-bits
    uint8_t lsb = MJ2_DOUT;
	//printf("lsb: %d\n", lsb);

    // Toggle !RST to reset encoder
    //Motor_Encoder_Reset();

    // Set !OE high to disable output of encoder
    SET_PIN(MJ1, MJ1_OE);

    return (int16_t)(msb << 8) | lsb;
}

void Motor_Encoder_Reset()
{
    CLEAR_PIN(MJ1, MJ1_RST);
    _delay_us(250);
    SET_PIN(MJ1, MJ1_RST);
}

void Motor_Set_Dir(direction_t dir)
{
	
    switch (dir) {
    case left: // Set left direction
        CLEAR_PIN(MJ1, MJ1_DIR);
        break;

    case right: // Set right direction
        SET_PIN(MJ1, MJ1_DIR);
        break;

    case stop: // If passing stop direction, set left (because it doesn't matter)
        CLEAR_PIN(MJ1, MJ1_DIR);

    default: 
        break;
    }
}

void Motor_Set_Speed(uint8_t speed)
{
    // Speed should be 0 - 255
    DAC_Send(speed);
}