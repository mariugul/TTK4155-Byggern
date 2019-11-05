#include "../inc/mcp2515.h"
#include "../inc/mcp_defines.h"
#include "../inc/spi.h"


uint8_t mcp_init(uint8_t mode)
{
    uint8_t value;

    spi_init();
	for (volatile unsigned int i; i < 1000; i++);
    mcp_reset();
	for (volatile unsigned int i; i < 1000; i++);

    // Self test
    value = mcp_read(MCP_CANSTAT);
    if ((value & MODE_MASK) != MODE_CONFIG) {
        printf("<MCP2515 is NOT in configuration mode after reset!>\n");
        return 1; // Exit
    }

    // ************************************
    // INITIALIZE STUFF HERE IN CONFIG MODE
    // ************************************

    // Set mode
    char mcp_canctrl = mcp_read(MCP_CANCTRL);
    mcp_canctrl &= ~(0b11100000);
    mcp_canctrl |= mode;
    mcp_write(MCP_CANCTRL, mcp_canctrl);

     // Self test
    value = mcp_read(MCP_CANSTAT);
    if ((value & MODE_MASK) != mode) {
        printf("<MCP2515 is NOT in the selected mode!>\n");
        return 1; // Exit
    }


    // Print which mode was selected
    if (mode == MODE_NORMAL)
        printf("<MCP2515 is in NORMAL mode.>\n");

    else if (mode == MODE_SLEEP)
        printf("<MCP2515 is in SLEEP mode.>\n");

    else if (mode == MODE_LOOPBACK)
        printf("<MCP2515 is in LOOPBACK mode.>\n");

    else if (mode == MODE_LISTENONLY)
        printf("<MCP2515 is in LISTEN ONLY mode.>\n");

    else if (mode == MODE_CONFIG)
        printf("MCP2515 is in CONFIG mode.\n");

    else if (mode == MODE_POWERUP)
        printf("MCP2515 is in POWER UP mode.\n");
    else 
        printf("MCP2515 is in NONE DEFINED mode.\n");

    return 0;
}

void mcp_reset()
{
    mcp_activate();
    spi_write(MCP_RESET);
    mcp_deactivate();
}

uint8_t mcp_read(uint8_t address)
{
    uint8_t read = 0;
    mcp_activate(); // Set 'CS LOW

    spi_write(MCP_READ); // Write READ command
    spi_write(address); // Write address

    read = spi_read(); // Read data
    mcp_deactivate(); // Set 'CS HIGH

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

void mcp_rts(uint8_t transmitt)
{
    mcp_activate();
    spi_write(transmitt);
    mcp_deactivate();
}

uint8_t mcp_read_status()
{
    mcp_activate();

    spi_write(MCP_READ_STATUS);
    uint8_t read = spi_read();

    mcp_deactivate();
    return read;
}

void mcp_bit_mod(uint8_t address, uint8_t mask, uint8_t data)
{
    mcp_activate();

    spi_write(MCP_BITMOD);
    spi_write(address);
    spi_write(mask);
    spi_write(data);

    mcp_deactivate();
}

// PROTOTYPE
void mcp_activate()
{
    PORTB &= ~(1 << PB4); // Lower 'CS
}

void mcp_deactivate()
{
    PORTB |= (1 << PB4); // Higher 'CS
}