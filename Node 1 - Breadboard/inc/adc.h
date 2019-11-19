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
typedef struct
{
    int joy_x;
    int joy_y;
    int slider_l;
    int slider_r;
    uint8_t button;

} pos_t;

enum adc_channels
{
    JOY_X = 0,
    JOY_Y = 1,
    SLIDER_R = 2,
    SLIDER_L = 3
};

// Function Prototypes
//---------------------------------------------------
void adc_test();
void adc_init();
int adc_read(uint8_t channel);
pos_t pos_read();
//int pos_to_percent(int pos);
//enum direction j_pos(int joy_x, int joy_y);

#endif