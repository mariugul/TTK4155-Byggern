#define F_CPU 16000000UL

#include "../inc/Motor.h"
#include "../inc/DAC.h"
#include <util/delay.h>

void Motor_Init()
{
    printf("<Motor Initialized>\n");
	
	// Set up DAC with I2C
    DAC_Init();
    
    // Set ports to output
    SET_OUTPUT(MJ1, MJ1_EN);
    SET_OUTPUT(MJ1, MJ1_OE);
    SET_OUTPUT(MJ1, MJ1_SEL);
    SET_OUTPUT(MJ1, MJ1_RST);
    SET_OUTPUT(MJ1, MJ1_DIR);

    // Set ports to input
    SET_INPUT(MJ2, MJ2_DOUT);
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
    // Set !OE low to enable output of encoder
    CLEAR_PIN(MJ1, MJ1_OE);

    // Set SEL low to get high byte
    CLEAR_PIN(MJ1, MJ1_SEL);

    // Wait about 20 microseconds
    _delay_us(50);

    // TODO Check on this
    // Read MSB
    uint8_t msb = MJ2_DOUT;

    // Set SEL high to get low byte
    SET_PIN(MJ1, MJ1_SEL);

    // Wait about 20 microseconds
    _delay_us(50);

    // TODO Check on this
    // Read LSB
    uint8_t lsb = MJ2_DOUT;

    // Toggle !RST to reset encoder
    Motor_Encoder_Reset();

    // Set !OE high to disable output of encoder
    SET_PIN(MJ1, MJ1_OE);

    // Return received data
    int16_t rotation = (msb << 8) | lsb;
    return rotation;
}

void Motor_Encoder_Reset()
{
    SET_PIN(MJ1, MJ1_RST);
    _delay_us(250);
    CLEAR_PIN(MJ1, MJ1_RST);
}

void Motor_Set_Dir(direction_t dir)
{
    switch (dir) {
    case left: // Set left direction
        CLEAR_PIN(MJ1, MJ1_DIR);
        break;

    case right: // Set rigth diretion
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