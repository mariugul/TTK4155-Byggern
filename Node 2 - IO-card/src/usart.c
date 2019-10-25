#include "../inc/usart.h" // Include header file
#include <avr/io.h> // Include AVR library

// USART macros
#define FOSC 4915200 // Clock speed
#define BAUD 9600 // Baud rate for USART
#define MYUBRR FOSC / 16 / BAUD - 1 // Calculate the USART init

/*_________________________________
  \     Function definitions      /
   \____________________________*/

// initialize the USART
void usart_init()
{
    /* Set baud rate */
    UBRR0H = (unsigned char)((MYUBRR) >> 8);
    UBRR0L = (unsigned char)(MYUBRR);

    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);

    // Assign printf to USART
    fdevopen(usart_send, usart_receive);
    printf("<USART is ready>\n");
}

// Check if transmit buffer is ready
bool usart_is_ready()
{
    return ((UCSR0A & (1 << UDRE0)));
}

// Send data
void usart_send(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!usart_is_ready())
        ;

    UDR0 = data; //put data on buffer
}

// Return received data
unsigned char usart_receive()
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;

    /* Get and return received data from buffer */
    return UDR0;
}

// Check for data in the HW buffer
bool usart_has_data()
{
    return (UCSR0A & (1 << RXC0));
}