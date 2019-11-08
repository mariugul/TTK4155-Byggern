#ifndef __ADC_H_
#define __ADC_H_

#include <avr/io.h>

void adc_init();
uint16_t adc_read();
int ball_detected();

#endif