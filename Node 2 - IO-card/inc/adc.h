#ifndef __ADC_H_
#define __ADC_H_

#include <avr/io.h>
#include <stdio.h>

void ADC_Init();
uint16_t ADC_Read();
int Ball_Detected();

#endif