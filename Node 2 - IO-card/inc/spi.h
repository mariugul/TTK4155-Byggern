/*********************************************************
 *              SPI Communication Driver                 *
 *                                                       *
 * The SPI driver is used to communicate from the Atmega *
 * to the CAN Controller "MCP2515".         			 *
 *                                                       *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __SPI_H_
#define __SPI_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdio.h>

// Function Prototypes
//---------------------------------------------------
void SPI_Init();             // Enable SPI communication
char SPI_Read();             // Read from the SPI
void SPI_Write(uint8_t cmd); // Write to the SPI

#endif