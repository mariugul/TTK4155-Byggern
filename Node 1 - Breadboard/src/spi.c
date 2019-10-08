#include "spi.h"


void spi_init()                             /* Enable SPI */
{
    DDRB   |= (1<<PB4)  | (1<<PB5) | (1<<PB7);  // Set SS, MOSI and SCK output, all others input */
    SPCR    = (1 <<SPE) | (1<<MSTR)|( 1<<SPR0); // Enable SPI, Master, set clock rate fck/16 */
    // Have this in mcp2515 instead??
    PORTB  |= (1 << PB4);                       // Set Slave Select to HIGH
}

char spi_read()                              /* Read from the SPI */
{
    while(!(SPSR & (1<<SPIF)))              // Wait for reception complete 
        ;

    return SPDR;                            // Return data register
}

void spi_write(uint8_t cmd)                      /* Write to the SPI */
{
    SPDR = cmd;                            // Start transmission                        
    while(!(SPSR & (1<<SPIF)) )            // Wait for transmission complete  
        ;
}