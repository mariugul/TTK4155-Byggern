#include "../inc/DAC.h"
#include "../inc/GPIO_Defines.h"
#include "../inc/TWI_Master.h"
#include <avr/interrupt.h>

void DAC_Init()
{
    sei(); // Enable global interrupts
    TWI_Master_Init();
}

void DAC_Send(uint8_t data)
{
    // Variables for the message
    uint8_t addr = 10; // TODO Find correct address
    uint8_t cmd  = 0x0;
    uint8_t length = 3;

    // Message to be sent
    uint8_t message[] = {addr, cmd, data}; // ! Does this compile? Check it out!

    // Send data over I2C 
    TWI_Start_Transceiver_With_Data(message, length);
}
