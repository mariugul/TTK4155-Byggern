/*
 * uart_test.c
 *
 * Created: 10.09.2019 21:04:55
 * Author : Marius C. K. Gulbrandsen
 */

#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include "decoder.h"                     // Address decoder

// UART macros
#define FOSC   4915200                  // Clock speed


int main(void)
{
    // Setup pins
    DDRB    |= (1 << PB0);              // Port B0 is an output
    PORTB   |= (1 << PB0);              // Port B0 is HIGH: Turn on LED


    // Main program loop
    while (true) {

    }
}
