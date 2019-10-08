/*SPI communication driver*/

#ifndef __SPI_H_				// HEADER GUARD
#define __SPI_H__

#include <avr/io.h>


void spi_init();				// Enable SPI communication
char spi_read();				// Read from the SPI
void spi_write(uint8_t cmd);	// Write to the SPI

#endif 