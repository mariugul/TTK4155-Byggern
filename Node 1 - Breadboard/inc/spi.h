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

// Function Prototypes
//---------------------------------------------------
void spi_init();             // Enable SPI communication
char spi_read();             // Read from the SPI
void spi_write(uint8_t cmd); // Write to the SPI

#endif