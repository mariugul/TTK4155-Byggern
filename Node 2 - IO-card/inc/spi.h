/*SPI communication driver*/

#ifndef __SPI_H_				// HEADER GUARD
#define __SPI_H__

#include <avr/io.h>


void SPI_Init();				// Enable SPI communication
char SPI_Read();				// Read from the SPI
void SPI_Write(uint8_t cmd);	// Write to the SPI

#endif 