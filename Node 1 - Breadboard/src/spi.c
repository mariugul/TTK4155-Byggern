/*********************************************************
 *              SPI Communication Driver                 *
 *                                                       *
 * The SPI driver is used to communicate from the Atmega *
 * to the CAN Controller "MCP2515".         			 *
 *                                                       *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/spi.h"

// Function Definitions
//---------------------------------------------------
void spi_init()
{
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7); // Set SS, MOSI and SCK output, all others input */
    DDRB &= ~(1 << PB6); // MISO as input.
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI, Master, set clock rate fck/16 */
    // Have this in mcp2515 instead??
    PORTB |= (1 << PB4); // Set Slave Select to HIGH
}

char spi_read()
{
    spi_write(0x00); // Delay one clk
    while (!(SPSR & (1 << SPIF))) // Wait for reception complete
        ;

    return SPDR; // Return data register
}

void spi_write(uint8_t cmd)
{
    SPDR = cmd; // Start transmission
    while (!(SPSR & (1 << SPIF))) // Wait for transmission complete
        ;
}