#include "../inc/mcp2515.h"
#include "../inc/mcp_defines.h"
#include "../inc/spi.h"


uint8_t mcp_init(uint8_t mode)
{
    uint8_t value;

    spi_init();
    mcp_reset();

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
    mcp_write(MCP_CANCTRL, mode);

     // Self test
    value = mcp_read(MCP_CANSTAT);
    if ((value & MODE_MASK) != mode) {
        printf("<MCP2515 is NOT in the selected mode!>\n");
        return 1; // Exit
    }


    // Print which mode was selected
    if (mode == MODE_NORMAL)
        printf("<MCP2515 is in   normal   mode.>\n");

    if (mode == MODE_SLEEP)
        printf("<MCP2515 is in   sleep   mode.>\n");

    if (mode == MODE_LOOPBACK)
        printf("<MCP2515 is in   loopback   mode.>\n");

    if (mode == MODE_LISTENONLY)
        printf("<MCP2515 is in   listen only   mode.>\n");

    if (mode == MODE_CONFIG)
        printf("MCP2515 is in   config   mode.\n");

    if (mode == MODE_POWERUP)
        printf("MCP2515 is in   power up   mode.\n");

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
    uint8_t read;
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