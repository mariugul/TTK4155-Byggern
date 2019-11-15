#ifndef __GPIO_H_              // HEADER GUARD
#define __GPIO_H__

#include <avr/io.h>
#include <stdbool.h>

typedef enum {
    push_l,
    push_r,
    jstick
} button_t;

void gpio_init();                       // Initialize gpio pins
bool gpio_read_button(button_t button);  // Read button values

#endif 