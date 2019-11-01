#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh // Remove this probably (100%)

void can_init(const uint8_t mode)
{
    // -Initialize loop back mode
    mcp_init(mode);            // Set MCP2515 mode
    mcp_bit_mod(MCP_CANINTE, MCP_RX_INT, 0xffff);  // Set interrupt enable
    mcp_bit_mod(MCP_CANINTE, MCP_TX_INT, 0xffff);  // Set interrupt enable

    mcp_write(MCP_CANINTF, 0);  // Clear flags
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xffff);  // Enable txreq

    printf("<CAN is ready>");
}

void can_send(can_message* message)
{
    // Set TX req enable for transmission
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xffff);

    mcp_bit_mod(MCP_CANINTF, MCP_TX_INT, 0); // Clear tx int flag

    // Set ID and data-length
    mcp_bit_mod(MCP_TXB0SIDL, 0b11100000, (message->id) << 5);    // Set the ID (high)
    mcp_write(MCP_TXB0SIDH, (message->id) >> 3);
    mcp_write(MCP_TXB0DLC, message->length); // Set the length

    const uint8_t buffer_addr[8] = {0x36, 0x37, 0x38, 0x39, 
                                    0x3A, 0x3B, 0x3C, 0x3D};

    // Load the transmitt data buffer with data
    for (int i = 0; i < message->length; i++) {
        mcp_write(buffer_addr[i], message->data[i]);
    }
    
    mcp_rts(MCP_RTS_TX0);
}

can_message can_receive()
{
    if (!(mcp_read(MCP_CANINTF) & MCP_RX0IF)) {
        return (can_message){0}; // Early exit
    }

    can_message rx = {0};

    // Get ID
    const uint8_t id_high = mcp_read(MCP_RXB0SIDH);
    const uint8_t id_low = mcp_read(MCP_RXB0SIDL) >> 5;
    rx.id = (id_high << 3) + id_low;

    // Get code length
    const uint8_t length = mcp_read(MCP_RXB0DLC) & 0x0f;
    rx.length = (length > 8 ? 8 : length);

    // Get data
    const uint8_t rx0_buffer_addr[8] = {0x66, 0x67, 0x68, 0x69,
                                        0x6a, 0x6b, 0x6c, 0x6d};

    for (int i = 0; i < rx.length; i++) {
        rx.data[i] = mcp_read(rx0_buffer_addr[i]);
    }

    mcp_bit_mod(MCP_CANINTF, MCP_RX0IF, 0); // CLEAR FLAG!
    return rx;
}
