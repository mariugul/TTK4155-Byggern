/*********************************************************
 *             USART Communication Driver                *
 *                                                       *
 * The USART driver is used for easy debugging by using  *
 * "printf" in the code. It works over the USB provided  *
 * with the Arduino Mega.                                *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/USART.h" // Include header file
#include <avr/io.h> // Include AVR library
#include "../inc/Timers.h"

// Definitions
//---------------------------------------------------
#define FOSC (16000000) // Clock speed
#define BAUD (1000000) // Baud rate for USAR
#define MYUBRR FOSC / 16 / BAUD - 1 // Calculate the USART init

// Function Definitions
//---------------------------------------------------

// initialize the USART
void USART_Init()
{
    /* Set baud rate */
    UBRR0H = (unsigned char)((MYUBRR) >> 8);
    UBRR0L = (unsigned char)(MYUBRR);

    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);

    // Assign printf to USART
    fdevopen(USART_Send, USART_Receive);
    printf("<USART is ready>\n");
}

// Check if transmit buffer is ready
bool USART_Is_Ready()
{
    return ((UCSR0A & (1 << UDRE0)));
}

// Send data
void USART_Send(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!USART_Is_Ready())
        ;

    UDR0 = data; //put data on buffer

}

// Return received data
unsigned char USART_Receive()
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;

    /* Get and return received data from buffer */
    return UDR0;

}

// Check for data in the HW buffer
bool USART_Has_Data()
{
    return (UCSR0A & (1 << RXC0));
}

