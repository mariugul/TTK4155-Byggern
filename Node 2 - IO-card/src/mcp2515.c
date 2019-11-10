#include "../inc/MCP2515.h"
#include "../inc/MCP_Defines.h"
#include "../inc/SPI.h"


uint8_t MCP_Init(uint8_t mode)
{
    uint8_t value;

    SPI_Init();
	for (volatile unsigned int i; i < 1000; i++);
    mcp_Reset();
	for (volatile unsigned int i; i < 1000; i++);

    // Self test
    value = MCP_Read(MCP_CANSTAT);
	for (volatile unsigned int i; i < 1000; i++);
    printf("CANSTAT: %d\n", value);

    if ((value & MODE_MASK) != MODE_CONFIG) {
        printf("<MCP2515 is NOT in configuration mode after reset!>\n");
        return 1; // Exit
    }

    // ************************************
    // INITIALIZE STUFF HERE IN CONFIG MODE
    // ************************************

    // Set mode
    /*
    char mcp_canctrl = mcp_read(MCP_CANCTRL);
    mcp_canctrl &= ~(0b11100000);
    mcp_canctrl |= mode;
    MCP_Write(MCP_CANCTRL, mcp_canctrl);
    */
    MCP_Write(MCP_CANCTRL, mode);
    //for (volatile unsigned int i = 0; i < 1000; i++);

     // Self test
    value = MCP_Read(MCP_CANSTAT);
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

void MCP_Reset()
{
    MCP_Activate();
    SPI_Write(MCP_RESET);
    MCP_Deactivate();
}

uint8_t MCP_Read(uint8_t address)
{
    uint8_t read = 0;
    MCP_Activate(); // Set 'CS LOW

    SPI_Write(MCP_READ); // Write READ command
    SPI_Write(address); // Write address

    read = SPI_Read(); // Read data
    MCP_Deactivate(); // Set 'CS HIGH

    return read;
}

void MCP_Write(uint8_t address, uint8_t data)
{
    MCP_Activate();

    SPI_Write(MCP_WRITE);
    SPI_Write(address);
    SPI_Write(data);

    MCP_Deactivate();
}

void MCP_Rts(uint8_t transmitt)
{
    MCP_Activate();
    SPI_Write(transmitt);
    MCP_Deactivate();
}

uint8_t MCP_Read_Status()
{
    MCP_Activate();

    SPI_Write(MCP_READ_STATUS);
    uint8_t read = SPI_read();

    MCP_Deactivate();
    return read;
}

void MCP_Bit_Mod(uint8_t address, uint8_t mask, uint8_t data)
{
    MCP_Activate();

    SPI_Write(MCP_BITMOD);
    SPI_Write(address);
    SPI_Write(mask);
    SPI_Write(data);

    MCP_Deactivate();
}

// PROTOTYPE
void MCP_Activate()
{
    PORTB &= ~(1 << PB7); // Lower 'CS
}

void MCP_Deactivate()
{
    PORTB |= (1 << PB7); // Higher 'CS
}