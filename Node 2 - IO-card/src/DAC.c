/*********************************************************
 *             Digital to Analog Converter               *
 *                                                       *
 *  The DAC is used for generating an analog signal      * 
 *  for the servo motor. The DAC uses I2C to do so.      *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/DAC.h"
#include "../inc/GPIO_Defines.h"
#include "../inc/TWI_Master.h"
#include <avr/interrupt.h>

// Function Definitions
//---------------------------------------------------
void DAC_Init()
{
	//SET_OUTPUT(PORTD, PD0);
    TWI_Master_Init();
}

void DAC_Send(uint8_t data)
{	
    // Variables for the message
    uint8_t addr   = 0x50; 
    uint8_t cmd    = 0x00;
    uint8_t length = 0x03;

    // Message to be sent
    uint8_t message[] = {addr, cmd, data}; 

    // Send data over I2C 
    TWI_Start_Transceiver_With_Data(message, length);
}
