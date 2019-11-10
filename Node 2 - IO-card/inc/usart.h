#ifndef __USART_H__                              // HEADER GUARD
#define __USART_H__

#include <stdbool.h>                            // For bool keyword
#include <stdio.h>                              // Standard library

// Function declarations
void	      USART_Init();						// Initialize the USART
void		  USART_Send(unsigned char data);   // Send data over USART
unsigned char USART_Receive();                  // Receive data from USART
bool		  USART_Is_Ready();                 // Check if USART is ready for transmit
bool          USART_Has_Data();					// Check is there is data on HW buffer

#endif 