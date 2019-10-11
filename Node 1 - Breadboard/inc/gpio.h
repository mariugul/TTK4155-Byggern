#ifndef __GPIO_H_              // HEADER GUARD
#define __GPIO_H__

#include <avr/io.h>
#include <stdbool.h>

void gpio_init();                       // Initialize gpio pins
bool gpio_read_button(uint8_t button);  // Read button values

#endif 