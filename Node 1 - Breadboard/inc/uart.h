/*********************************************************
 *             UART Communication Driver                 *
 *                                                       *
 * The UART driver is used for easy debugging by using   *
 * "printf" in the code.                                 *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __UART_H__
#define __UART_H__

// Includes
//---------------------------------------------------
#include <stdbool.h> // For bool keyword
#include <stdio.h>   // Standard library
#include <avr/io.h>  // Include AVR library

// Function Prototypes
//---------------------------------------------------
void uart_init();                   // Initialize the uart
void uart_send(unsigned char data); // Send data over uart
unsigned char uart_receive();       // Receive data from uart
bool uart_is_ready();               // Check if uart is ready for transmitt
bool uart_has_data();               // Check is there is data on HW buffer

#endif