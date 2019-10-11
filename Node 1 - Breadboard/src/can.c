#include "../inc/can.h"
#include "../inc/mcp_defines.h"

#define CANCTRL_REG XFh

void can_init()
{
    mcp_init();
    // -Initialize loop back mode
    mcp_write(MCP_CANCTRL ,MODE_LOOPBACK);

    // -Enable interrupts

}

void can_send(can_message* message)
{
    // -Send a message with ID and Data
    mcp_rts(message);
}

char can_receive()
{
    // -Receive a message
}
