#ifndef __UART_H__                              // HEADER GUARD
#define __UART_H__

#include <stdbool.h>                            // for bool keyword
#include <stdio.h>

// function declarations
void	      uart_init(unsigned int ubrr);              // initialize the uart
void		  uart_send(unsigned char data);             // send data over uart
unsigned char uart_receive();                            // receive data from uart
bool		  uart_is_ready();                            // check if uart is ready for transmitt
bool          uart_has_data();							 // check is there is data on HW buffer
int           uart_printf(char c, FILE *stream);		 // stream handler for printf

#endif 


