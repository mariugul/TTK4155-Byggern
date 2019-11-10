#include "../inc/Motor.h"
#include "../inc/DAC.h"
#include "../inc/GPIO_Defines.h"
#include <util/delay.h>
#include "../inc/PID.h"


void Motor_Init()
{
    // ? PID INIT HERE

    // Set ports to output
    SET_OUTPUT(MJ1, MJ1_EN);
    SET_OUTPUT(MJ1, MJ1_OE);
    SET_OUTPUT(MJ1, MJ1_SEL);
    SET_OUTPUT(MJ1, MJ1_RST);
    SET_OUTPUT(MJ1, MJ1_DIR);
    
    // Set ports to input
    SET_INPUT(MJ2, MJ2_DOUT);
    

    
}

void Motor_Move(uint8_t joystick_pos, uint8_t dir, uint_8t speed)
{
    // Set direction
    Motor_Set_Dir(dir);

    // TODO - Calculate speed with PID from Joystick input

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
    SET_PIN(MJ1, MJ1_OE)

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

void Motor_Set_Dir(uint8_t dir) // TODO Make this parameter an enumeration
{
    if (dir = LEFT) {
        // Set "left" direction
        CLEAR_PIN(MJ1, MJ1_DIR);
    } else if (dir = RIGHT) {
        // Set "right" direction
        SET_PIN(MJ1, MJ1_DIR);
    } else {
        // Set left as default if the value is different from 1 and 0
        CLEAR_PIN(MJ1, MJ1_DIR);
    }
}

void Motor_Set_Speed(uint8_t speed)
{   
    // Speed should be 0 - 255
    DAC_Send(speed);
}