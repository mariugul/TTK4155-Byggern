#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh // Remove this probably (100%)

void can_init()
{
    // -Initialize loop back mode
    mcp_init (MODE_LOOPBACK);            // Set MCP2515 mode
    mcp_write(MCP_CANINTE, MCP_RX_INT);  // Set interrupt enable
    mcp_write(MCP_CANINTE, MCP_TX_INT);  // Set interrupt enable


    printf("<CAN is ready>");
}

void can_send(can_message* message)
{
    mcp_prepare_message(message->id, message->length);

    // Check that we can send
    if (!(mcp_read(MCP_TXB0CTRL) & MCP_TXREQ_MASK)) {
        printf("Transmitt not ready\n");
        return;
    }

    // Clear bits ATBF, MLOA, TXERR in TXB0CTRL register
    mcp_bit_mod(MCP_TXB0CTRL, MCP_ATBF_MASK, 0);
    mcp_bit_mod(MCP_TXB0CTRL, MCP_MLOA_MASK, 0);
    mcp_bit_mod(MCP_TXB0CTRL, MCP_TXERR_MASK, 0);
    
    const uint8_t buffer_addr[8] = {0x36, 0x37, 0x38, 0x39, 
                                    0x3A, 0x3B, 0x3C, 0x3D};

    // Load the transmitt data buffer with data
    for (int i = 0; i < message->length; i++) {
        mcp_write(buffer_addr[i], message->data[i]);
    }

    printf("Message has been transmitted\n");
}

char can_receive(uint8_t id)
{
    // Read from rx intrerrupt FLAG register
    // if (!rx_interrupt_occured) return 0; // Early exit

    // Check from which register and return value
    // if (int_from_rx0) return rxb0;
    // else if (int_from_rx1) return rxb1;
    // else return 0;    // no interrupt from rx


    // -Receive a message
    if(mcp_read(id) == MCP_RX0IF)
        printf("Message received!\n");
    
    return mcp_read(id);
}

// In development
void can_error() {}
void can_transmit_complete(){}
void can_int_vect() {}
