#include "../inc/spi.h"


void spi_init()                             /* Enable SPI */
{
    DDRB   |= (1<<PB7)  |(1<<PB0) | (1<<PB2) | (1<<PB1);  // Set SS, MOSI and SCK output, all others input */
    DDRB   &= ~(1 << PB3);  // MISO as input. 
    SPCR    = (1 <<SPE) | (1<<MSTR)|( 1<<SPR0); // Enable SPI, Master, set clock rate fck/16 */
    // Have this in mcp2515 instead??
    PORTB  |= (1 << PB0);                       // Set Slave Select to HIGH
    PORTB  |= (1 << PB7);                       // Set Slave Select to HIGH
}

char spi_read()                              /* Read from the SPI */
{   
    spi_write(0x00);                        // Delay one clk
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