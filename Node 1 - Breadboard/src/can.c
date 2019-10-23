#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh // Remove this probably (100%)

void can_init()
{
    // -Initialize loop back mode
    mcp_init(MODE_LOOPBACK); // Set MCP2515 mode
    mcp_write(MCP_CANINTE, MCP_RX_INT); // Set interrupt enable
    mcp_write(MCP_CANINTE, MCP_TX_INT); // Set interrupt enable

    printf("<CAN is ready>");
}

void can_send(can_message* message)
{
    // Check that we can send
    if (!(mcp_read(MCP_TXB0CTRL) & MCP_TXREQ_MASK)) {
        //printf("Transmitt not ready\n");
        return;
    }

    // Set ID and data-length
    mcp_bit_mod(MCP_TXB0SIDL, 0b11100000, message->id << 5); // Set the ID (high)
    mcp_write(MCP_TXB0DLC, message->length); // Set the length

    // Clear bits ATBF, MLOA, TXERR in TXB0CTRL register
    //mcp_bit_mod(MCP_TXB0CTRL, MCP_ATBF_MASK, 0);
    //mcp_bit_mod(MCP_TXB0CTRL, MCP_MLOA_MASK, 0);
    //mcp_bit_mod(MCP_TXB0CTRL, MCP_TXERR_MASK, 0);

    const uint8_t buffer_addr[8] = { 0x36, 0x37, 0x38, 0x39,
        0x3A, 0x3B, 0x3C, 0x3D };

    // Load the transmitt data buffer with data
    for (int i = 0; i < message->length; i++) {
        mcp_write(buffer_addr[i], message->data[i]);
    }

    // Set bit to start transmission, may be removed?
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 1);

    while (!(!(mcp_read(MCP_TXB0CTRL) & MCP_TXREQ_MASK) && (mcp_read(MCP_CANINTF) & MCP_RX0IF)))
        ;

    printf("Message has been transmitted!\n");

    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 1);
    //mcp_rts(); // Request to send
    //can_transmit_complete(); // Sets transmit as complete
}

can_message can_receive()
{
    // Proceed only if RXB0 or RX1 interrupt
    if (!(mcp_read(MCP_CANINTF) & MCP_RX0IF))
        return (can_message) { 0 };
    //else if (!(mcp_read(MCP_CANINTF) & MCP_RX1IF))  return {0};

    can_message rx_msg = { 0 };
    rx_msg.id = mcp_read(MCP_RXB0SIDL) >> 5;
    rx_msg.length = mcp_read(MCP_RXB0DLC) & 0x0f;

    // Addresses of data receive buffer. Where the rx data is stored
    const uint8_t rx_data_buff_addr[8] = { 0x66, 0x67, 0x68, 0x69,
        0x6A, 0x6B, 0x6C, 0x6D };

    // Protect against extended length and out of array index
    const int length = (rx_msg.length > 8 ? 8 : rx_msg.length);
    for (int i = 0; i < length; i++) {
        rx_msg.data[i] = mcp_read(rx_data_buff_addr[i]);
    }

    return rx_msg;
}

// In development
void can_error() {}
void can_transmit_complete() {}
void can_int_vect() {}
