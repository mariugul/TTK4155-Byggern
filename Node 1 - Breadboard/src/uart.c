#include "../inc/uart.h"                     // Include header file
#include <avr/io.h>                   // Include AVR library

// UART macros
#define FOSC   4915200                  // Clock speed
#define BAUD   9600                     // Baud rate for uart
#define MYUBRR FOSC / 16 / BAUD - 1     // Calculate the uart init 

/*_________________________________
  \     Function definitions      /
   \____________________________*/

// Check if transmitt buffer is ready
bool uart_is_ready()
{
    return ((UCSR0A & (1 << UDRE0)));
}

// Send data
void uart_send(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!uart_is_ready());

    UDR0 = data; //put data on buffer
}

// Return received data
unsigned char uart_receive()
{
    return UDR0;
}

// initialize the uart
void uart_init()
{
    // Set baud rate
    UBRR0H = (unsigned char)(MYUBRR >> 8);
    UBRR0L = (unsigned char)(MYUBRR);

    // Enable receive and transmitt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);

    // Assign printf to UART
    fdevopen(uart_send, uart_receive);

    printf("<UART is ready>\n");
}

// Check for data in the HW buffer
bool uart_has_data()
{
    return (UCSR0A & (1 << RXC0));
}