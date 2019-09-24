/*
 * joystick.h
 *
 * Created: 17.09.2019 10:48:51
 *  Author: Marius
 */ 

#ifndef __ADC_H__                              // HEADER GUARD
#define __ADC_H__

#include <avr/io.h>									// Include AVR library

// 
typedef struct {
	int x;
	int y;
	uint8_t button;
} pos_t;

// 
enum adc_channels {
	JOY_X = 0,
	JOY_Y = 1,
	SLIDER_L = 2,
	SLIDER_R = 3
};

void  adc_test();
void  adc_init();
int   adc_read(uint8_t channel);
pos_t pos_read();


#endif