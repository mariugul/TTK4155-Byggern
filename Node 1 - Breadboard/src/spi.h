/*SPI communication driver*/

#ifndef __SPI_H_              // HEADER GUARD
#define __SPI_H__

#include <avr/io.h>


void spi_init();
char spi_read();
void spi_write(char c);

#endif 