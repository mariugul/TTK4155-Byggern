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
#ifndef __ADC_H_
#define __ADC_H_

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdio.h>

// Function Prototypes
//---------------------------------------------------
void ADC_Init();
uint16_t ADC_Read();
int Ball_Detected();

#endif