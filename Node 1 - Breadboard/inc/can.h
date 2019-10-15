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

void can_init();
void can_send(can_message *message);
char can_receive(uint8_t id);
void can_error();
void can_transmit_complete();
void can_int_vect();



#endif