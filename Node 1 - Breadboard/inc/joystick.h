/*********************************************************
 *                     Joystick                          *
 *                                                       *
 *  These are the functions to get the joystick                           *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>

// Typedefs
//---------------------------------------------------
typedef enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} direction_t;

typedef struct
{
    direction_t dir_x;
    direction_t dir_y;
    uint8_t button_pressed;
} joy_t;

// Function Prototypes
//---------------------------------------------------
int pos_to_percent(int pos);
joy_t joystick_read_direction();
joy_t get_joystick();

#endif