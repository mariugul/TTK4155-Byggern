#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh // Remove this probably (100%)

void can_init()
{
    // -Initialize loop back mode
    mcp_init(MODE_LOOPBACK);            // Set MCP2515 mode
    //mcp_bit_mod(MCP_CANINTE, MCP_RX_INT, MCP_RX_INT);  // Set interrupt enable
    //mcp_bit_mod(MCP_CANINTE, MCP_TX_INT, MCP_TX_INT);  // Set interrupt enable
    mcp_write(MCP_CANINTE, MCP_RX_INT);
    mcp_write(MCP_CANINTE, MCP_TX_INT);
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 1);
    printf("<CAN is ready>");
}

void can_send(can_message* message)
{
    mcp_write(MCP_CANINTE, MCP_TX_INT);
    //mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 1);

    // Check that we can send
    if (!(mcp_read(MCP_TXB0CTRL) & MCP_TXREQ_MASK)) {
        //printf("Transmitt not ready\n");
        return;
    }

    // Set ID and data-length
    mcp_bit_mod(MCP_TXB0SIDL, 0b11100000, (message->id) << 5);    // Set the ID (high)
    mcp_write(MCP_TXB0SIDH, (message->id) >> 3);
    mcp_write(MCP_TXB0DLC, message->length); // Set the length

    // Set priority TXP, Highest=3
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXERR_MASK, 3);
    
    const uint8_t buffer_addr[8] = {0x36, 0x37, 0x38, 0x39, 
                                    0x3A, 0x3B, 0x3C, 0x3D};

    // Load the transmitt data buffer with data
    for (int i = 0; i < message->length; i++) {
        mcp_write(buffer_addr[i], message->data[i]);
    }

    // Set bit to start transmission, may be removed?
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 1);
    
    
    mcp_rts(1);
    printf("Message has been transmitted (maybe)\n");
    //can_transmit_complete(); // Sets transmit as complete
}

can_message can_receive()
{
    mcp_write(MCP_CANINTE, MCP_RX_INT);
    // Read from rx intrerrupt FLAG register
    if (mcp_read(MCP_CANINTF) == 0x00) {
    //if (!(mcp_read(MCP_CANINTF) & MCP_RX0IF)) {
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

    // CLEAR FLAG!
    mcp_bit_mod(MCP_CANINTF, MCP_RX0IF, 0);

    return rx;
}

// In development
void can_error() {}
void can_transmit_complete(){}
void can_int_vect() {}
