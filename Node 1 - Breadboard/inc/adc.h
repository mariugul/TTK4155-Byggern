/*********************************************************
 *             Analog to Digital Converter               *
 *                                                       *
 *  The ADC will read the IR diode values for detecting  *
 *  the ball.                                            *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __ADC_H__                             
#define __ADC_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>	

// Typedefs
//---------------------------------------------------

// joystick and slider values
typedef struct {
	int joy_x;
	int joy_y;
	int slider_l;
	int slider_r;
	uint8_t button;
	
} pos_t;


enum ADC_Channels {
	JOY_X = 0,
	JOY_Y = 1,
	SLIDER_R = 2,
	SLIDER_L = 3
};

// Function Prototypes
//---------------------------------------------------
void  ADC_Test();
void  ADC_Init();
int   ADC_Read(uint8_t channel);
pos_t Pos_Read();
int   Pos_To_Percent(int pos);
enum direction J_pos(int joy_x, int joy_y);

#endif