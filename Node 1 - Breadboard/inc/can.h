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

// Defines
//---------------------------------------------------
#define NODE1_INIT_ID 1
#define NODE2_READY_ID 2
#define NODE2_GAME_OVER_ID 3
#define NODE1_RESET_ID 4
#define NODE1_START_ID 5

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
void can_send_init();
void can_send_start();
void can_send_reset();
can_message can_receive();
void can_clear_errors();

#endif