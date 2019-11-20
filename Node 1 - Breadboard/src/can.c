/*******************
 * 
 * CAN Status messages:
 * I - Init
 * R - Ready
 * S - Start
 * G - Game over
 * Q - Quit / Reset
 * 
 *******************/
#include "../inc/can.h"
#include "../inc/mcp_defines.h"
#include "../inc/mcp2515.h"
#include "../inc/uart.h"

#define CANCTRL_REG XFh // Remove this probably (100%)


void can_send_init()
{
    can_message msg = {
        .id = NODE1_INIT_ID,
        .length = 1,
        .data[0] = 'I'
    };
    can_send(&msg);
}


void can_send_start()
{
    can_message msg = {
        .id = NODE1_START_ID,
        .length = 1,
        .data[0] = 'S'
    };
    can_send(&msg);
}

void can_send_reset()
{
    can_message msg = {
        .id = NODE1_RESET_ID,
        .length = 1,
        .data[0] = 'Q'
    };
}

void can_init(const uint8_t mode)
{
    // -Initialize loop back mode
    mcp_init(mode);            // Set MCP2515 mode
    for (volatile int i = 0; i < 1000; i++);
    mcp_bit_mod(MCP_CANINTE, MCP_RX_INT, 0xffff);  // Set interrupt enable
    for (volatile int i = 0; i < 1000; i++);
    //mcp_bit_mod(MCP_CANINTE, MCP_TX_INT, 0xffff);  // Set interrupt enable
    //for (volatile int i = 0; i < 1000; i++);

    mcp_write(MCP_CANINTF, 0);  // Clear flags
    for (volatile int i = 0; i < 1000; i++);
    //mcp_bit_mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xffff);  // Enable txreq
    //for (volatile int i = 0; i < 1000; i++);

    printf("<CAN is ready>");
}

void can_send(can_message* message)
{

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

void can_clear_errors()
{
    const uint8_t int_flags = mcp_read(MCP_CANINTF);
    printf("can error flags: %d\n", int_flags);

    // See if any error flag is high and clear
    if (int_flags > 0x1f) {
        printf("Clearing time!\n");
        mcp_bit_mod(MCP_CANINTF, 0b11100000, 0x00);
    }
}