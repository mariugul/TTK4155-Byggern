#include "mcp2515.h"
#include "spi.h"


/** INSTRUCTIONS **/
#define MCP_READ        0b00000011
#define MCP_RESET       0b11000000
#define MCP_READ_STATUS 0b10100000
#define MCP_BIT_MODIFY  0b00000101
#define MCP_WRITE       0b10010010  



void mcp_init()
{
    mcp_reset();

    // More functionality coming
}

void mcp_reset()
{
    mcp_activate();
    spi_write(MCP_RESET);
    mcp_deactivate();
}

 uint8_t mcp_read(uint8_t address)
{
	uint8_t read;
    mcp_activate();                             // Set 'CS LOW 

	spi_write(MCP_READ);							// Write READ command
    spi_write(address);                         // Write address

	read = spi_read();                  // Read data
    mcp_deactivate();                           // Set 'CS HIGH

	return read;
}


void mcp_write(uint8_t address, uint8_t data)
{
    mcp_activate();

    spi_write(MCP_WRITE);
    spi_write(address);
    spi_write(data);

    mcp_deactivate();

}

void mcp_rts(uint8_t transmitt_buffer)
{
    mcp_activate();
    spi_write(transmitt_buffer);
    mcp_deactivate();
}

uint8_t mcp_read_status()
{
    uint8_t read;
    mcp_activate();
    
    spi_write(MCP_READ_STATUS);
    read = spi_read();
    
    mcp_deactivate();

    return read;
}

void mcp_bit_mod(uint8_t address, uint8_t mask, uint8_t data)
{
    mcp_activate();

    spi_write(MCP_BIT_MODIFY);
    spi_write(address);
    spi_write(mask);
    spi_write(data);

    mcp_deactivate();
}

// PROTOTYPE
void mcp_activate()
{
    PORTB  &= ~(0 << PB4);                       // Lower 'CS
}

void mcp_deactivate()
{
    PORTB  |= (1 << PB4);                       // Higher 'CS
}
