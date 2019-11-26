/*********************************************************
 *             Digital to Analog Converter               *
 *                                                       *
 *  The DAC is used for generating an analog signal      * 
 *  for the servo motor. The DAC uses I2C to do so.      *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __DAC_H__
#define __DAC_H__

// Includes
//---------------------------------------------------
#include <stdint.h>
#include <stdio.h>

// Function Prototypes
//---------------------------------------------------
void DAC_Init();
void DAC_Send(uint8_t data);

#endif