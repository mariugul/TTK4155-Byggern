#ifndef __JOYSTICK_H_              // HEADER GUARD
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
    direction_t direction;
    uint8_t button_pressed;
} joy_t;


joy_t get_joystick();

#endif 