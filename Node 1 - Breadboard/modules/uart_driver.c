/*
 * uart_test.c
 *
 * Created: 06.09.2019 13:49:13
 * Author : Marius C. K. Gulbrandsen
 */

#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include "uart.h"                       // UART driver

// UART macros
#define FOSC   4915200                  // Clock speed
#define BAUD   9600                     // Baud rate for uart
#define MYUBRR FOSC / 16 / BAUD - 1     // Calculate the uart init 


int main(void)
{
    // Setup pins
    DDRB    |= (1 << PB0);              // Port B0 is an output
    PORTB   |= (1 << PB0);              // Port B0 is HIGH: Turn on LED

    // Initialize UART
    uart_init(MYUBRR);

    // Send UART test
    uart_send('a');
    uart_send('b');
    uart_send('c');

    // Test printf function
    printf("Heisann");

    // Main program loop
    while (true) {
        
        // UART echoing
        if (uart_has_data()) {
            unsigned char rx_char = uart_receive();
            uart_send(rx_char);     
        }
    }
}
