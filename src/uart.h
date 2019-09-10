#ifndef __UART_H__                              // HEADER GUARD
#define __UART_H__

#include <stdbool.h>                            // For bool keyword
#include <stdio.h>                              // Standard library

// Function declarations
void	      uart_init(unsigned int ubrr);              // Initialize the uart
void		  uart_send(unsigned char data);             // Send data over uart
unsigned char uart_receive();                            // Receive data from uart
bool		  uart_is_ready();                           // Check if uart is ready for transmitt
bool          uart_has_data();							 // Check is there is data on HW buffer

#endif 