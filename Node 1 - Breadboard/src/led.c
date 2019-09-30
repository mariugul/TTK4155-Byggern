#include "blank.h"


void led_init()                       // Initialize LED
{
    DDRB  |= (1 << PB0);              // Port B0 is an output
    PORTB |= (1 << PB0);              // Port B0 is HIGH: Turn on LED
}
