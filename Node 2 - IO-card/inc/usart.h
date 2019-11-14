/*********************************************************
 *             USART Communication Driver                *
 *                                                       *
 * The USART driver is used for easy debugging by using  *
 * "printf" in the code. It works over the USB provided  *
 * with the Arduino Mega.                                *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __USART_H__ // HEADER GUARD
#define __USART_H__

// Includes
//---------------------------------------------------
#include <stdbool.h> // For bool keyword
#include <stdio.h>   // Standard library

// Function Prototypes
//---------------------------------------------------
void USART_Init();                   // Initialize the USART
void USART_Send(unsigned char data); // Send data over USART
unsigned char USART_Receive();       // Receive data from USART
bool USART_Is_Ready();               // Check if USART is ready for transmit
bool USART_Has_Data();               // Check is there is data on HW buffer

#endif