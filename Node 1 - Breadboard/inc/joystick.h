/* * joystick.h
 *
 *  Created: 08.10.2019
 *  Author: Daniel Rahme
 */ 
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <avr/io.h>

typedef enum  {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} direction_t;

typedef struct {
    direction_t dir_x;
    direction_t dir_y;
    uint8_t button_pressed;
} joy_t;


joy_t get_joystick();

#endif 