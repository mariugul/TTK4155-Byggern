#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh // Remove this probably (100%)

void can_init()
{
    // -Initialize loop back mode
    mcp_init(MODE_LOOPBACK);            // Set MCP2515 mode
    mcp_bit_mod(MCP_CANINTE, MCP_RX_INT, 0xffff);  // Set interrupt enable
    mcp_bit_mod(MCP_CANINTE, MCP_TX_INT, 0xffff);  // Set interrupt enable

    mcp_write(MCP_CANINTF, 0);  // Clear flags
    //mcp_write(MCP_CANINTE, MCP_RX_INT);
    //mcp_write(MCP_CANINTE, MCP_TX_INT);

    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xffff);

    const uint8_t can_int_ef = mcp_read(MCP_CANINTE);
    printf("CAN int enable flags: %d\n", can_int_ef);
    
    printf("<CAN is ready>");
}

void can_send(can_message* message)
{
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xffff);
    //const int mcp_tx_control = mcp_read(MCP_TXB0CTRL);
    //printf("MCP tx control: %d\n", mcp_tx_control);

    // Check that we can send
    //if (!(mcp_read(MCP_TXB0CTRL) & MCP_TXREQ_MASK)) {
        //printf("Transmitt not ready\n");
        //return;
    //}

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
    
    //mcp_rts(1);
    mcp_rts(MCP_RTS_TX0);
    //printf("Message has been transmitted (maybe)\n");
}

can_message can_receive()
{
    //mcp_write(MCP_CANINTE, MCP_RX_INT);
    // Read from rx intrerrupt FLAG register

    const int mcp_canintf = mcp_read(MCP_CANINTF);
    printf("Can int flag rec: %d\n", mcp_canintf);
    //if (mcp_read(MCP_CANINTF) == 0x00) {
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

    // CLEAR FLAG!
    mcp_bit_mod(MCP_CANINTF, MCP_RX0IF, 0);
    //mcp_write(MCP_CANINTF, 0); // To be removed later

    return rx;
}

// In development
void can_error() {}
void can_transmit_complete(){}
void can_int_vect() {}
