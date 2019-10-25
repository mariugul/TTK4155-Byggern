#ifndef __USART_H__                              // HEADER GUARD
#define __USART_H__

#include <stdbool.h>                            // For bool keyword
#include <stdio.h>                              // Standard library

// Function declarations
void	      usart_init();						// Initialize the USART
void		  usart_send(unsigned char data);   // Send data over USART
unsigned char usart_receive();                  // Receive data from USART
bool		  usart_is_ready();                 // Check if USART is ready for transmit
bool          usart_has_data();					// Check is there is data on HW buffer

#endif 