/*********************************************************
 *                    CAN Bus                            *
 *                                                       *
 *  The CAN bus sends and receives messages between the  *
 *  two nodes (Atmega162 and Atmega2560)                 *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __CAN_H__
#define __CAN_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

// Typedefs
//---------------------------------------------------

// Interrupt Flag States
typedef enum
{
    rxb_empty,
    rxb0_data,
    rxb1_data,
    rxb_both_data
} irqf_decode_t;

// CAN Messages
typedef struct
{
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_message;

// Function Prototypes
//---------------------------------------------------
void CAN_Init(const uint8_t mode);
void CAN_Send(can_message *message);
void CAN_Clear_IF();
can_message CAN_Receive();
irqf_decode_t CAN_IRQ_Decode();

#endif