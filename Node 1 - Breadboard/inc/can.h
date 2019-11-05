/*High level sending and receiving CAN messages*/

#ifndef __CAN_H_ // HEADER GUARD
#define __CAN_H__

#include <avr/io.h>

typedef struct
{
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_message;

void can_init(const uint8_t mode);
void can_send(can_message *message);
can_message can_receive();
void can_clear_errors();

#endif