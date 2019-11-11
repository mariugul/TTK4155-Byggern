/*High level sending and receiving CAN messages*/

#ifndef __CAN_H_ // HEADER GUARD
#define __CAN_H__

#include <avr/io.h>

// Interrupt Flag States
typedef enum {
    rxb_empty,
    rxb0_data,
    rxb1_data,
    rxb_both_data
} irqf_decode_t;

// CAN Messages
typedef struct {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_message;

// Function prototypes
void CAN_Init(const uint8_t mode);
void CAN_Send(can_message *message);
void CAN_Clear_IF();
can_message CAN_Receive();
irqf_decode_t CAN_IRQ_Decode();

#endif