#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh

void can_init()
{
    // -Initialize loop back mode
    mcp_init(MODE_LOOPBACK);
    printf("<CAN is ready>");
}

void can_send(can_message* message)
{
    // -Send a message with ID and Data
    uint8_t i;
    for (i = 0; i < message->length; i++)
        mcp_rts(message->data[i]);
}

char can_receive()
{
    // -Receive a message
}

// In development
void can_error() {}
void can_transmit_complete(){}
void can_int_vect() {}