/*********************************************************
 *                    CAN Bus                            *
 *                                                       *
 *  The CAN bus sends and receives messages between the  *
 *  two nodes (Atmega162 and Atmega2560)                 *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/CAN.h"
#include "../inc/MCP2515.h"
#include "../inc/MCP_Defines.h"
#include "../inc/GPIO_Defines.h"
#include "../inc/USART.h"

// Definitions
//---------------------------------------------------

// Receive buffers in MCP2515
#define RX0B 0
#define RX1B 1

// ID for joystick data
#define JSTICK_CAN_ID 10

// Functions
//---------------------------------------------------
void CAN_Init(const uint8_t mode)
{
    printf("<CAN is ready>");
    
    // -Initialize loop back mode
    MCP_Init(mode); // Set MCP2515 mode
    MCP_Bit_Mod(MCP_CANINTE, MCP_RX_INT, 0xff); // Set interrupt enable

    MCP_Write(MCP_CANINTF, 0); // Clear flags
    MCP_Bit_Mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xff); // Enable txreq

    
}

void CAN_Send(can_message* message)
{
    // Set TX req enable for transmission
    MCP_Bit_Mod(MCP_TXB0CTRL, MCP_TXREQ_MASK, 0xff);

    MCP_Bit_Mod(MCP_CANINTF, MCP_TX_INT, 0); // Clear tx int flag

    // Set ID and data-length
    MCP_Bit_Mod(MCP_TXB0SIDL, 0b11100000, (message->id) << 5); // Set the ID (high)
    MCP_Write(MCP_TXB0SIDH, (message->id) >> 3);
    MCP_Write(MCP_TXB0DLC, message->length); // Set the length

    const uint8_t buffer_addr[8] = { 0x36, 0x37, 0x38, 0x39,
        0x3A, 0x3B, 0x3C, 0x3D };

    // Load the transmitt data buffer with data
    for (int i = 0; i < message->length; i++) {
        MCP_Write(buffer_addr[i], message->data[i]);
    }

    MCP_Rts(MCP_RTS_TX0);
}

can_message CAN_Receive()
{
    if (!(MCP_Read(MCP_CANINTF) & MCP_RX0IF)) {
        return (can_message) { 0 }; // Early exit
    }

    can_message rx = { 0 };

    // Get ID
    const uint8_t id_high = MCP_Read(MCP_RXB0SIDH);
    const uint8_t id_low = MCP_Read(MCP_RXB0SIDL) >> 5;
    rx.id = (id_high << 3) + id_low;

    // Get code length
    const uint8_t length = MCP_Read(MCP_RXB0DLC) & 0x0f;
    rx.length = (length > 8 ? 8 : length);

    // Get data
    const uint8_t rx0_buffer_addr[8] = { 0x66, 0x67, 0x68, 0x69,
        0x6a, 0x6b, 0x6c, 0x6d };

    for (int i = 0; i < rx.length; i++) {
        rx.data[i] = MCP_Read(rx0_buffer_addr[i]);
    }

    MCP_Bit_Mod(MCP_CANINTF, MCP_RX0IF, 0); // CLEAR FLAG!
    return rx;
}

// Clear Interrupt on MCP2515
void CAN_Clear_IF()
{
    // TODO - Clear the Interrupt Flag in MCP2515
}

// Returns cause of the Interrupt
irqf_decode_t CAN_IRQ_Decode()
{
    // Hold the values of RX0B and RX1B flags
    bool irq_buf_flags[2] = {};

    // Read interrupt flag register
    uint8_t irq_source = MCP_Read(MCP_CANINTF); 

    // Save to RX buf flags
    irq_buf_flags[RX0B] = irq_source & MCP_RX0IF;
    irq_buf_flags[RX1B] = irq_source & MCP_RX1IF;

    // Decode and return the source of the interrupt
    if(irq_buf_flags[RX0B] == true)
    {
        // Both RX buffers has data
        if(irq_buf_flags[RX1B == true])
            return rxb_both_data;
        
        // Only RX0B has data
        return rxb0_data;
    }
    else // RXOB = false
    {
        // Only RX1B has data
        if(irq_buf_flags[RX1B == true])
            return rxb1_data;
        
        // None of RX buffers has data
        return rxb_empty;
    }
}

