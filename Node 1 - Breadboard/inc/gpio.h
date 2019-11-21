/*********************************************************
 *                         GPIO                          *
 *                                                       *
 *  These are the functions for setting up GPIO and      *
 *  reading the buttons.                                 *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __GPIO_H_              
#define __GPIO_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdbool.h>

// Typedefs
//---------------------------------------------------
typedef enum {
    push_l,
    push_r,
    jstick
} button_t;

// Function Prototypes
//---------------------------------------------------
void gpio_init();                        // Initialize gpio pins
bool gpio_read_button(button_t button);  // Read button values

#endif 