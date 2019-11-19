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

// Typedefs
//---------------------------------------------------
typedef struct
{
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_message;

// Function Prototypes
//---------------------------------------------------
void can_init(const uint8_t mode);
void can_send(can_message *message);
can_message can_receive();
void can_clear_errors();

#endif