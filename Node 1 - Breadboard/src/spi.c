#include "spi.h"


void spi_init()                         // Setup SPI
{       
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);     // Set MOSI and SCK output, all others input */
    SPCR    = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // Enable SPI, Master, set clock rate fck/16 */
}

char spi_read()                         // Read from the SPI
{
    
    while(!(SPSR & (1<<SPIF)))              // Wait for reception complete 
        ;

     
    return SPDR;                            // Return data register
}

void spi_write(char c)                 // Write to the SPI
{
    SPDR = c;                              // Start transmission                        
    while(!(SPSR & (1<<SPIF)) )            // Wait for transmission complete  
        ;
}